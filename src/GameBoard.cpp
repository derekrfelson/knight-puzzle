/*
 * GameBoard.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <MoveProvider.h>
#include <iostream>
#include <ostream>
#include <random>
#include <stack>
#include "GameBoard.h"
#include "Pawn.h"
#include "Knight.h"
#include "State.h"
#include "Settings.h"
using namespace std;

GameBoard::GameBoard()
: pawnsInOnState{true},
  knight{nullptr},
  moves{}
{
	// Seed the random number generator with random data from the OS
	auto gen = std::mt19937{std::random_device{}()};
	auto randBoardSize = std::uniform_int_distribution<size_t>
		{0, Settings::instance().size - 1};
	auto randDirection = std::uniform_int_distribution<size_t>(0, 3);

	// Find a valid place for the knight first
	auto knightX = randBoardSize(gen);
	auto knightY = randBoardSize(gen);
	knight = make_unique<Knight>(knightX, knightY);

	// Generate the pawns we start with, making sure each has a valid place
	for (auto i = 0; i < Settings::instance().numStartingPawns; ++i)
	{
		auto validPawn = false;

		// The loop randomly picks another spot if there is a collision
		while (!validPawn)
		{
			validPawn = true;

			// Randomly pick a spot for the pawn to start
			auto startX = randBoardSize(gen);
			auto startY = randBoardSize(gen);

			// It must be possible to capture all the pawns, given the starting
			// position of the knight. This is easy to check by looking at the
			// parity of the sum of the x and y positions.
			//
			// Say the knight starts at {x0,y0}. It can move 2 in 1 direction
			// and 1 in the other each turn. So the difference in x+y will
			// always be 3, which means if the knight starts with x0+y0 even
			// ("even parity"), then it can only reach other positions with
			// even parity in an even number of moves. So in that case, any
			// pawn whose "on" position parity is odd would be unreachable.
			//
			// Note that because pawn positions vary by 1, the off parity is
			// always the opposite of the on parity.
			if ((startX + startY) % 2 != (knightX + knightY) % 2)
			{
				validPawn = false;
			}

			// Randomly pick a direction for it to go
			// But try again if it would just move into a wall
			Direction d;
			switch (randDirection(gen))
			{
			case 0:
				d = Direction::UP;
				if (startY == 0)
				{
					validPawn = false;
				}
				break;
			case 1:
				d = Direction::RIGHT;
				if (startX == Settings::instance().size - 1)
				{
					validPawn = false;
				}
				break;
			case 2:
				d = Direction::DOWN;
				if (startY == Settings::instance().size - 1)
				{
					validPawn = false;
				}
				break;
			case 3:
				d = Direction::LEFT;
				if (startX == 0)
				{
					validPawn = false;
				}
				break;
			}

			// Disallow pawns too close to one another
			for (const auto& pawn : pawns)
			{
				auto otherX = get<0>(pawn.position());
				auto otherY = get<1>(pawn.position());
				// Careful subtraction with unsigned numbers
				auto diffX =
						otherX < startX ? startX - otherX : otherX - startX;
				auto diffY =
						otherY < startY ? startY - otherY : otherY - startY;
				if (diffX <= 2 && diffY <= 2)
				{
					validPawn = false;
				}
			}

			// Disallow pawns too close to the knight
			// Careful subtraction with unsigned numbers
			auto diffX = startX < knightX ? knightX - startX
					: startX - knightX;
			auto diffY = startY < knightY ? knightY - startY
					: startY - knightY;
			if (diffX <= 2 && diffY <= 2)
			{
				validPawn = false;
			}

			// Generate the pawn
			if (validPawn)
			{
				pawns.emplace_back(Pawn{startX, startY, d});
			}
		}
	}
}

GameBoard& GameBoard::instance()
{
	static GameBoard* instance = new GameBoard{};
	return *instance;
}

ostream& GameBoard::print(ostream& stream) const
{
	// Top border
	for (auto i = 0; i < Settings::instance().size+2; ++i)
	{
		stream << "#";
	}
	stream << endl;

	for (auto y = 0; y < Settings::instance().size; ++y)
	{
		stream << "#"; // Left border
		for (auto x = 0; x < Settings::instance().size; ++x)
		{
			// Print the correct character for the (x,y) position
			if (isPawn(x, y))
			{
				stream << "P";
			}
			else if (isKnight(x, y))
			{
				stream << "K";
			}
			else
			{
				stream << " ";
			}
		}
		stream << "#"; // Right border
		stream << endl;
	}

	// Bottom border
	for (auto i = 0; i < Settings::instance().size+2; ++i)
	{
		stream << "#";
	}
	stream << endl;

	// Extra debug information
	stream << "Pawns are " << (pawnsInOnState ? "on" : "off") << endl;
	for (const auto& pawn : pawns)
	{
		stream << pawn << endl;
	}
	stream << *knight << endl;

	return stream;
}

bool GameBoard::isPawn(size_t x, size_t y) const
{
	for (const auto& pawn : pawns)
	{
		if (!pawn.captured()
				&& get<0>(pawn.position()) == x
				&& get<1>(pawn.position()) == y)
		{
			return true;
		}
	}
	return false;
}

bool GameBoard::isKnight(size_t x, size_t y) const
{
	return x == get<0>(knight->position()) && y == get<1>(knight->position());
}

// Cannot default this due to use of unique_ptrs
GameBoard::~GameBoard()
{
}

std::ostream& operator<< (std::ostream& stream, const GameBoard& board)
{
	return board.print(stream);
}

void GameBoard::next()
{
	// Figure out how to move the knight
	// Must do this BEFORE moving any of the other game pieces
	if (moves.empty())
	{
		moves = Settings::instance().moveProvider(
				State {
					pawnsInOnState,
					knight->position()
				});
	}

	// If no moves found, do nothing
	if (moves.empty())
	{
		cout << "No moves found!" << endl;
		return;
	}

	// Toggle each of the pawn positions
	for (auto& pawn : pawns)
	{
		pawn.move();
	}

	// Update the pawn position toggle
	pawnsInOnState = !pawnsInOnState;

	// Move the knight
	knight->move(moves.front());

	// Update captured pawns
	for (auto& pawn : pawns)
	{
		if (pawn.position() == knight->position())
		{
			pawn.capture();
		}
	}

	// Go to the next move in the stack
	moves.pop_front();
}
