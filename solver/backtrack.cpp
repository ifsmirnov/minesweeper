#include <algorithm>

#include "header.h"

/**
 * Given field, find out which cells can be uniquely marked mine or no-mine
 * @param paramfield - given field
 * @param rem_depth - maximum recursion depth. I.e. if rem_depth = 0, 
 * 		function will return only obvious possible moves, if rem_depth = 1,
 * 		it will try to place a mine or uncover some cell.
 * @return boolean value and two sets of pairs of ints. Bool is true
 * 		iff position is correct. Every pair corresponds to coordinates,
 * 		first set contains cells which could be marked with mines,
 * 	    second one contains knowingly empty cells.
 * 
 * @date 2012, Jan 15
 * @author Ivan Smirnov
 */ 
std :: pair<bool, std :: pair<t_cells_list, t_cells_list> > determine (t_field field, int rem_depth)
{
	/**
	 * 3) if any marks are put, return true and these marks, otherwise
	 *    if recursion depth is not to large, 
	 * 4) for each cell:
	 *    4a) put mine on it
	 * 	  4b) mark no-mine
	 * 	  call determine() with 4a and 4b. if both of them return false,
	 *    return false. if any of them return false, add other mark
	 * 	  to answer, otherwise add set_intersection to answer
	 * 5) return true and answer
	 */
	 
	size_t n = field.size();
	m_assert(n, field is empty (n));
	size_t m = field[0].size();
	m_assert(m, field is empty (m));
	for (auto i: field)
		m_assert(i.size() == m, two field lines have unequal length);

	t_cells_list mines, empty;
	
{ 	// correctness check and filling obvious cells
	bool anyChanges = true;
	while (anyChanges)
	{
		anyChanges = false;
		for (t_coord i = 0; i < n; i++)
			for (t_coord j = 0; j < n; j++)
				if (field[i][j] >= 0)
				{
					auto t = getFreeNearby(field, i, j);
					if (t.first + t.second < field[i][j] || t.first > field[i][j]) // incorrect field
						return std :: make_pair(false, std :: make_pair(t_cells_list(), t_cells_list()));
					
					bool fillMines = t.first + t.second == field[i][j] && t.second != 0;
					bool fillEmpty = t.first == field[i][j] && t.second != 0;
					if (!fillMines && !fillEmpty) continue;
					anyChanges = true;
					for (int di: {-1,0,1})
						for (int dj: {-1,0,1})
							if (i + di >= 0 && i + di < n && j + dj >= 0 && j + dj < m && (di != 0 || dj != 0) && field[i + di][j + dj] == cUnopened)
							{
								if (fillMines)
								{
									mines.insert(std :: make_pair(i + di, j + dj));
									field[i + di][j + dj] = cMine;
								}
								else
								{
									empty.insert(std :: make_pair(i + di, j + dj));
									field[i + di][j + dj] = cUnknown;
								}
							}
					
				}
	}
}
	//
	
	if (!mines.empty() || !empty.empty())
		return std :: make_pair(true, std :: make_pair(mines, empty));
	if (rem_depth == 0)
		return std :: make_pair(true, std :: make_pair(t_cells_list(), t_cells_list()));
		
	
{	// recursion		
	for (t_coord i = 0; i < n; i++)
		for (t_coord j = 0; j < m; j++)
		{
			int& cell = field[i][j];
			if (cell == cUnopened)
			{
				cell = cMine;
				auto resMine = determine(field, rem_depth - 1);
				cell = cUnknown;
				auto resEmpty = determine(field, rem_depth - 1);
				cell = cUnopened;
				
				auto &mMines = resMine.second.first,
					 &eMines = resEmpty.second.first,
					 &mEmpty = resMine.second.second,
					 &eEmpty = resEmpty.second.second;
				
				if (!resMine.first && !resEmpty.first) //no variants are possible
					return std :: make_pair(false, std :: make_pair(t_cells_list(), t_cells_list()));
				else if (resMine.first && !resEmpty.first) //knowingly to be a mine
				{
					mines.insert(std :: make_pair(i, j));
					mines.insert(mMines.begin(), mMines.end());
					empty.insert(mEmpty.begin(), mEmpty.end());
				}
				else if (!resMine.first && resEmpty.first) //knowingly to be empty
				{
					empty.insert(std :: make_pair(i, j));
					mines.insert(eMines.begin(), eMines.end());
					empty.insert(eEmpty.begin(), eEmpty.end());
				}
				else //both are possible
				{
					for (auto i: mMines)
						if (!eMines.count(i))
							mMines.erase(i);
					for (auto i: mEmpty)
						if (!eEmpty.count(i))
							mEmpty.erase(i);
					mines.insert(mMines.begin(), mMines.end());
					empty.insert(mEmpty.begin(), mEmpty.end());
				}
			}
		}
	return std :: make_pair(true, std :: make_pair(mines, empty));
}
	//
}

/**
 * Compute number of mines and unopened cells in the neighborhood of given cell
 * @param are obvious
 * @return pair<i, i>, where first is a number of mines, second is a number of unopened
 * 
 * @date 2012, Jan 15
 * @author Ivan Smirnov
 */ 
std :: pair<int, int> getFreeNearby(const t_field& field, t_coord x, t_coord y)
{
	size_t n = field.size();
	m_assert(n, field is empty (n));
	size_t m = field[0].size();
	m_assert(m, field is empty (m));
	for (auto i: field)
		m_assert(i.size() == m, two field lines have unequal length);
	
	m_assert(x < n && y < m, coordinates are out of bound);
	
	int cntMines = 0, 
		cntUnopened = 0;
	for (const auto i: {-1, 0, 1})
		for (const auto j: {-1, 0, 1})
			if (0 <= x + i && x + i < n && 0 <= y + j && y + j < m && (i != 0 || j != 0) )
			{
				cntMines += field[x+i][y+j] == cMine;
				cntUnopened += field[x+i][y+j] == cUnopened;
			}
	
	return std :: make_pair(cntMines, cntUnopened);
}
