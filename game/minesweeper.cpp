#include "header.h"

/**
 * @brief Implements cell type: coordinates and whether this cell contains mine
 * 
 * @note Can be used as a move value (then type == cMine means player wants
 * to place flag on the cell x, y, otherwise player wants to open this cell)
 * and as a return value (then type == cMine iff x, y contains mine, otherwise
 * type represents the value of recovered digit).
 * 
 * @date 2011, Jan 18
 * @author Ivan Smirnov
 */
Minesweeper :: t_cell :: t_cell (coord _x, coord _y, bool _type)
{
	x = _x;
	y = _y;
	type = _type;
}


Minesweeper :: Minesweeper ()
{
}

/**
 * @brief Starts a new game. This function does not fill initial values, 
 * because this should be done after user's first move.
 * 
 * @param _width, _height: field size
 * @param _mines: initial number of mines on the field
 * 
 * @date 2012, Jan 18
 * @author Ivan Smirnov
 */
void Minesweeper :: startGame (size_t _width, size_t _height, size_t _mines)
{
	width = _width;
	height = _height;
	mines = _mines;
	opened = width * height - mines;
	turn = 0;
	isGenerated = false;
	
	m_assert(width > 0, wrong field size);
	m_assert(height > 0, wrong field size);
	m_assert(width * height > mines, field size is not enough to place all mines);
	
	field.assign(height, std :: vector<int> (width, 0));
	state.assign(height, std :: vector<int> (width, stUnopened));
}

/**
 * @brief This function is called only once a game, after first user's turn.
 * It randomly spreads mines over a field using given field size and mines number,
 * given that point moveX, moveY should not contain a mine.
 * 
 * 
 * @date 2012, Jan 18
 * @author Ivan Smirnov
 */
void Minesweeper :: generateField (coord moveX, coord moveY)
{
	srand(time(NULL));
	m_assert(!isGenerated, generateField is called more than once);
	isGenerated = true;
	
	std :: vector<std :: pair<coord, coord> > cells;
	for (coord i = 0; i < height; i++)
		for (coord j = 0; j < width; j++)
			if (i != moveX || j != moveY)
				cells.push_back(std :: make_pair(i, j));
	std :: random_shuffle(cells.begin(), cells.end());
	cells.resize(mines);
	
	for (auto i: cells)
	{
		field[i.first][i.second] = cMine;
		for (auto dx: {-1,0,1})
			for (auto dy: {-1,0,1})
				if (i.first + dx >= 0 && i.first + dx < height && i.second + dy >= 0 && i.second + dy < width &&
				    (dx != 0 || dy != 0) && field[i.first + dx][i.second + dy] != cMine)
					++field[i.first + dx][i.second + dy];
	}
}

t_field Minesweeper :: getPicture()
{
	t_field result(height, std :: vector<char> (height, 0));
	
	for (coord i = 0; i < height; i++)
		for (coord j = 0; j < width; j++)
			switch(state[i][j])
			{
				case stUnopened:
					result[i][j] = '.';
					break;
				case stMine:
					result[i][j] = '*';
					break;
				case stOpened:
					if (field[i][j] == 0)
						result[i][j] = ' ';
					else
						result[i][j] = field[i][j] + '0';
					break;
						
			}
			
	return result;
}

/**
 * @brief Given cell, performs a click at given coordinates
 * @note On first turn this function also generates the field
 * @note Incorrect moves are just ignored
 * @param cell - coordinates of cell and click type (right/left),
 * packed in t_cell type
 * @return vector of t_cell, each element represents new recovered digit
 * If a mine is recovered, vector consists of only one element (x, y, cMine).
 * 
 * @date 2012, Jan 18
 * @author Ivan Smirnov
 */
int Minesweeper :: makeMove (t_cell cell)
{
	m_assert(cell.x >= 0 && cell.x < height, x coordinate out ot bound);
	m_assert(cell.y >= 0 && cell.y < width, y coordinate out ot bound);
	
	if (cell.type == cell.cEmpty && !isGenerated)
		generateField(cell.x, cell.y);
	
	++turn;
	if (cell.type == cell.cMine)
	{
		switch (state[cell.x][cell.y])
		{
			case stUnopened: 
				state[cell.x][cell.y] = stMine;
				break;
			case stOpened:
				break;
			case stMine:
				state[cell.x][cell.y] = stUnopened;
			break;			
		}
		return cContinue;
	}
	else
	{
		switch (state[cell.x][cell.y])
		{
			case stOpened:
				break;
			case stMine:
				break;
			case stUnopened:
				if (field[cell.x][cell.y] == cMine)
				{
					for (coord i = 0; i < width; i++)
						for (coord j = 0; j < width; j++)
							state[i][j] = field[i][j] == cMine ? stMine : stOpened;
					return cLose;
				}
				else
				{
					std :: queue<std :: pair<coord, coord> > q;
					std :: vector<t_cell> result;
					q.push(std :: make_pair(cell.x, cell.y));
					while (!q.empty())
					{
						auto t = q.front();
						q.pop();
						state[t.first][t.second] = stOpened;
						opened--;
						if (field[t.first][t.second] != 0)
							continue;
						for (auto dx: {0, 0, -1, 1})
							for (auto dy: {-1, 1, 0, 0})
							{
								if (t.first + dx >= 0 && t.first + dx < height && t.second + dy >= 0 && t.second + dy < width)
								{
									coord tx = t.first + dx;
									coord ty = t.second + dy;
									if (state[tx][ty] == stUnopened)
									{
										q.push(std :: make_pair(tx, ty));
										state[tx][ty] = stInqueue;
									}
								}
							}
					}
				}
				break;
		}
		if (opened != 0)
			return cContinue;
		for (coord i = 0; i < width; i++)
			for (coord j = 0; j < width; j++)
				state[i][j] = field[i][j] == cMine ? stMine : stOpened;
		return cWin;
	}
	m_assert(0, non-reachable position);
}

void Minesweeper :: printField()
{
	writeField(field);
}
void Minesweeper :: printPicture(std :: ostream& cout)
{
	auto t = getPicture();
	for (auto i: t)
	{
		for (auto j: i)
			cout << j;
		cout << std :: endl;
	}
	cout << std :: endl;
}
