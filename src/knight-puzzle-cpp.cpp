#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <sstream>
#include "GameBoard.h"
#include "MoveProvider.h"
#include "Settings.h"
using namespace std;

int main(int argc, char** argv) {
	auto badArgs = false;

	if (argc != 4)
	{
		badArgs = true;
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
		Settings::instance().moveProvider = getAStarMovesH1;
	}
	else if (strncmp(argv[3], "ASTAR-H2", 3) == 0)
	{
		cerr << "Not yet implemented" << endl;
		return 2;
	}
	else if (strncmp(argv[3], "ASTAR-HAVG", 3) == 0)
	{
		cerr << "Not yet implemented" << endl;
		return 2;
	}
	else
	{
		badArgs = true;
	}

	int tryBoardSize = -1;
	int tryNumPawns = -1;
	stringstream{argv[1]} >> tryBoardSize;
	stringstream{argv[2]} >> tryNumPawns;
	if (tryBoardSize < 0 || tryNumPawns < 0
			|| tryBoardSize > 254 || tryNumPawns > 40)
	{
		cerr << "Board size or number of pawns invalid or too large" << endl;
		badArgs = true;
	}
	else
	{
		Settings::instance().size = tryBoardSize;
		Settings::instance().numStartingPawns = tryNumPawns;
	}

	if (badArgs)
	{
		cerr << "Usage: knightpuzzle [boardsize] [pawns] [method]" << endl;
		cerr << "   where method = BFS | DFS | ASTAR-H1 "
				"| ASTAR-H2 | ASTAR-HAVG" << endl;
		return 1;
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
