#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <algorithm>
#include <vector>
#include <queue>
#include "header.h"

class Minesweeper
{
	/**
	 * What do I want from this class?
	 * It should implement one minesweeper game. So, it has to implement
	 * a field, position generator (Minesweeper :: newGame), player
	 * interface (Minesweeper :: move), counters (move #i etc), and, maybe,
	 * some other useful information. Hints should be also implemented.
	 * Of cource, this class should implement some other privaete 
	 * auxiliary functions, such as DFS.
	 */
public:

	class t_cell
	{
	public: 
		static const bool cMine = 1,
						  cEmpty = 0;
		coord x, y;
		bool type;
		t_cell(coord, coord, bool);
	};
	 
private:

	static const int cMine = -1;
	
	//state variables
	static const int stUnopened = 0;
	static const int stOpened = 1;
	static const int stMine = 2;
	static const int stInqueue = 3;
	
	
	size_t width, height, mines, turn;
	int opened;
	bool isGenerated;
	
	std :: vector<std :: vector<int> > field;
	std :: vector<std :: vector<int> > state;
	
	void generateField(coord, coord);
	
public:
	
	t_field getPicture();
	
	Minesweeper ();
	
	void startGame(size_t, size_t, size_t);
	int makeMove(t_cell);
	
	void printField();
	void printPicture(std :: ostream& = std :: cout);
	
};

#endif
