#include <iostream>

#include "header.h"
#include "minesweeper.h"

using namespace std;

int main()
{
	
	int n, m, mines;
	
	//cin >> n >> m >> mines;
	n = m = 8;
	mines = 10;
	vector<vector<int> > a(n, vector<int> (m, cUnopened));
	
	writeField(a);
	cout << endl;
	
	Minesweeper game;
	game.startGame(n, m, mines);
	
	while (1)
	{
		int x, y, t;
		cin >> x >> y >> t;
		x--, y--;
		auto res = game.makeMove(Minesweeper::t_cell(x, y, t == 1 ? Minesweeper::t_cell::cMine : Minesweeper::t_cell::cEmpty));
		if (t == 1)
			a[x][y] != cMine ? a[x][y] = cMine : a[x][y] = cUnopened;
		else
		{
			for (auto i: res)
			{
				if (i.type == Minesweeper::t_cell::cMine)
				{
					cout << "YOU FAILED!!!" << endl;
					game.printField();
					return 0;
				}
				a[i.x][i.y] = i.type;
			}
		}
		writeField(a);
		cout << endl;
	}
	
	
	return 0;
}
