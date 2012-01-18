#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>

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
	 
private:
	typedef std :: vector<std :: vector<int> > t_field;
	
	t_field field;	// mines/numbers field
	t_field mark; 	// marks field for graph search algorithms
	
	
};

#endif
