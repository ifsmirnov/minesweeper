#include <algorithm>

#include "header.h"

/**
 * Given field, find out which cells can be uniquely marked mine or no-mine
 * @param field - obvious
 * @param rem_depth - maximum recursion depth. I.e. if rem_depth = 0, 
 * 		function will return only obvious possible moves, if rem_depth = 1,
 * 		it will try to place a mine or uncover some cell.
 * @return boolean value and two vectors of pairs of ints. Bool is true
 * 		iff position is correct. Every pair corresponds to coordinates,
 * 		first vector contains cells which could be marked with mines,
 * 	    second contains knowingly empty cells.
 * 
 * @date 2012, Jan 15
 * @author Ivan Smirnov
 */ 
std :: pair<bool, std :: pair<t_cells_list, t_cells_list> > determine (const t_field &field, int rem_depth)
{
	/**
	 * 1) check correctness (for each digit there are enough free spaces
	 * 	  to place mines on and for each digit there are not more mines
	 * 	  nearby, than it means)
	 * 	  return false if failed
	 * 2) try to determine the field without recursion:
	 *    2a) if exists digit with exactly the same number of neighbors
	 * 	      as it means, fill them with mines
	 *    2b) if exists digit with exactly the same number of mines
	 * 		  nearby as it means and with at least one free neighbor,
	 * 		  mark these neighbors no-mine
	 *    TODO: repeat 2a and 2b while any changes are making
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


{ 	// 1) correctness
	for (t_coord i = 0; i < n; i++)
		for (t_coord j = 0; j < m; j++)
			if (field[i][j] >= 0)
			{
				auto t = getFreeNearby(field, i, j);
				if 
				(
					t.first + t.second < field[i][j] || // not enough place for mines
					t.first > field[i][j] // too many mines nearby
				) 
					return std :: make_pair(false, std :: make_pair(t_cells_list(0), t_cells_list(0)));
			}
} 
	// end of 1)
	///TODO: merge 1-st block with the second one to reduce number
	///of getFreeNearby calls	

	t_cells_list mines, empty;
{ 	// 2) determinition without recursion
	for (t_coord i = 0; i < n; i++)
		for (t_coord j = 0; j < n; j++)
			if (field[i][j] >= 0)
			{
				auto t = getFreeNearby(field, i, j);
				for (const auto di: {-1, 0, 1})
					for (const auto dj: {-1, 0, 1})
						if (0 <= i + di && i + di < n && 0 <= j + dj && j + dj < m &&
							(di != 0 || dj != 0) && field[i + di][j + dj] == cUnopened )
						{
							if (t.first + t.second == field[i][j])
								mines.push_back(std :: make_pair(i + di, j + dj));
							if (t.first == field[i][j])
								empty.push_back(std :: make_pair(i + di, j + dj));
						}
				
			}
	if (field[3][0] == cMine)
	{
		writeField(field);
	}
	if (!mines.empty() || !empty.empty()) // AAA
	{
		std :: sort(mines.begin(), mines.end());
		mines.resize(std :: unique(mines.begin(), mines.end()) - mines.begin());
		std :: sort(empty.begin(), empty.end());
		empty.resize(std :: unique(empty.begin(), empty.end()) - empty.begin());
		return std :: make_pair(true, std :: make_pair(mines, empty));
	}
}
//end of 2)
	
	if (rem_depth == 0)
		return std :: make_pair(true, std :: make_pair(t_cells_list(0), t_cells_list(0)));
		
{	// 3) recursion
	t_field field1 = field;
	for (t_coord i = 0; i < n; i++)
		for (t_coord j = 0; j < m; j++)
		{
			int& cell = field1[i][j];
			if (cell == cUnopened)
			{
				cell = cMine;
				auto resMine = determine(field1, rem_depth - 1);
				cell = cUnknown;
				auto resEmpty = determine(field1, rem_depth - 1);
				cell = cUnopened;
				
				if (!resMine.first && !resEmpty.first) //no variants are possible
					return std :: make_pair(false, std :: make_pair(t_cells_list(0), t_cells_list(0)));
				else if (resMine.first && !resEmpty.first) //knowingly to be a mine
				{
					mines.push_back(std :: make_pair(i, j));
					mines.insert(mines.end(), resMine.second.first.begin(), resMine.second.first.end());
					empty.insert(empty.end(), resMine.second.second.begin(), resMine.second.second.end());
				}
				else if (!resMine.first && resEmpty.first) //knowingly to be empty
				{
					empty.push_back(std :: make_pair(i, j));
					mines.insert(mines.end(), resEmpty.second.first.begin(), resEmpty.second.first.end());
					empty.insert(empty.end(), resEmpty.second.second.begin(), resEmpty.second.second.end());
				}
				else //both are possible
				{
					auto iter = mines.begin();
					mines.resize(mines.size() + resMine.second.first.size());
					mines.resize(set_intersection(resMine.second.first.begin(), resMine.second.first.end(),
												  resEmpty.second.first.begin(), resEmpty.second.first.end(),
												  iter) - iter);
					iter = empty.begin();
					empty.resize(set_intersection(resMine.second.second.begin(), resMine.second.second.end(),
												  resEmpty.second.second.begin(), resEmpty.second.second.end(),
												  iter) - iter);
				}
			}
		}
	std :: sort(mines.begin(), mines.end());
	mines.resize(std :: unique(mines.begin(), mines.end()) - mines.begin());
	std :: sort(empty.begin(), empty.end());
	empty.resize(std :: unique(empty.begin(), empty.end()) - empty.begin());
	return std :: make_pair(true, std :: make_pair(mines, empty));
}
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
