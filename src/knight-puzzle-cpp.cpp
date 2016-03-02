#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
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
		cerr << "Not yet implemented" << endl;
		return 2;
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

	if (badArgs)
	{
		cerr << "Usage: knightpuzzle [boardsize] [pawns] [method]" << endl;
		cerr << "   where method = BFS | DFS | ASTAR-H1 "
				"| ASTAR-H2 | ASTAR-HAVG" << endl;
		return 1;
	}

	Settings::instance().size = 30;

	for (auto i = 0; i < 40; ++i)
	{
		cout.clear();
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << GameBoard::instance() << endl;
		GameBoard::instance().next();
	}
	return 0;
}
