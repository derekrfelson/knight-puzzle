#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <sstream>
#include "GameBoard.h"
#include "MoveProvider.h"
#include "Settings.h"
using namespace std;

void usage()
{
	cerr << "Usage: knightpuzzle [boardsize] [pawns] [method]" << endl;
	cerr << "   where method = BFS | DFS | ASTAR-H1 "
			"| ASTAR-H2 | ASTAR-HAVG" << endl;
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		usage();
		return 2;
	}

	if (strncmp(argv[3], "BFS", 3) == 0)
	{
		Settings::instance().moveProvider = getBFSMoves;
	}
	else if (strncmp(argv[3], "DFS", 3) == 0)
	{
		Settings::instance().moveProvider = getDFSMoves;
	}
	else if (strncmp(argv[3], "ASTAR-H1", 3) == 0)
	{
		Settings::instance().moveProvider = getAStarMoves;
		Settings::instance().heuristic = h1compare;
	}
	else if (strncmp(argv[3], "ASTAR-H2", 3) == 0)
	{
		Settings::instance().moveProvider = getAStarMoves;
		Settings::instance().heuristic = h2compare;
	}
	else if (strncmp(argv[3], "ASTAR-HAVG", 3) == 0)
	{
		Settings::instance().moveProvider = getAStarMoves;
		Settings::instance().heuristic = havgcompare;
	}
	else
	{
		usage();
		return 2;
	}

	int tryBoardSize = -1;
	int tryNumPawns = -1;
	stringstream{argv[1]} >> tryBoardSize;
	stringstream{argv[2]} >> tryNumPawns;
	if (tryBoardSize < 0 || tryNumPawns < 0
			|| tryBoardSize > 254 || tryNumPawns > 40)
	{
		cerr << "Board size or number of pawns invalid or too large" << endl;
		return 1;
	}
	else
	{
		Settings::instance().size = tryBoardSize;
		Settings::instance().numStartingPawns = tryNumPawns;
	}

	while (!GameBoard::instance().isGameOver())
	{
		cout.clear();
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << GameBoard::instance() << endl;
		GameBoard::instance().next();
	}

	cout << GameBoard::instance() << endl;
	cout << "All pawns captured. Game over." << endl;

	return 0;
}
