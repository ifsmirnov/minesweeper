#include <iostream>

#include "header.h"
#include "minesweeper.h"

using namespace std;

int main()
{
	
	int n, m, mines;
	
	cin >> n >> m >> mines;
	//n = m = 8;
	//mines = 10;
	
	Minesweeper game;
	game.startGame(n, m, mines);
	
	game.printPicture();
	
	while (1)
	{
		int x, y, t;
		cin >> x >> y >> t;
		--x, --y;
		int res = game.makeMove(Minesweeper :: t_cell(x, y, t));
		
		if (res == cWin || res == cLose)
		{
			cout << (res == cWin ? "Congratulations, you won!" : "Motherfucker, you lose!") << endl;
			game.printPicture();
			return 0;
		}
		game.printPicture();
	}
	
	
	return 0;
}
