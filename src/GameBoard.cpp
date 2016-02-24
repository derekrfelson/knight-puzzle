/*
 * GameBoard.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <iostream>
#include <ostream>
#include <random>
#include "GameBoard.h"
#include "Pawn.h"
#include "Knight.h"
using namespace std;

GameBoard::GameBoard()
: size{18}, pawns{}, knight{nullptr}
{
	// Seed the random number generator with random data from the OS
	auto gen = std::mt19937{std::random_device{}()};
	auto randBoardSize = std::uniform_int_distribution<size_t>{0, size-1};
	auto randDirection = std::uniform_int_distribution<size_t>(0, 3);

	// Generate the pawns we start with, making sure each has a valid place
	for (auto i = 0; i < 8; ++i)
	{
		auto validPawn = false;

		// The loop randomly picks another spot if there is a collision
		while (!validPawn)
		{
			validPawn = true;

			// Randomly pick a spot for the pawn to start
			auto startX = randBoardSize(gen);
			auto startY = randBoardSize(gen);

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
				if (startX == size - 1)
				{
					validPawn = false;
				}
				break;
			case 2:
				d = Direction::DOWN;
				if (startY == size - 1)
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
			for (auto pawn : pawns)
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

			// Generate the pawn
			if (validPawn)
			{
				pawns.emplace_back(Pawn{startX, startY, d});
			}
		}
	}

	// Find a valid place for the knight next
	auto validKnight = false;
	while (!validKnight)
	{
		validKnight = true;

		// Randomly pick a spot for the knight to start
		auto knightX = randBoardSize(gen);
		auto knightY = randBoardSize(gen);

		// Disallow knight too close to a pawn
		for (auto pawn : pawns)
		{
			auto otherX = get<0>(pawn.position());
			auto otherY = get<1>(pawn.position());
			// Careful subtraction with unsigned numbers
			auto diffX =
					otherX < knightX ? knightX - otherX : otherX - knightX;
			auto diffY =
					otherY < knightY ? knightY - otherY : otherY - knightY;
			if (diffX <= 2 && diffY <= 2)
			{
				validKnight = false;
			}
		}

		// Make the knight
		if (validKnight)
		{
			knight = make_unique<Knight>(knightX, knightY);
		}
	}
}

ostream& GameBoard::print(ostream& stream) const
{
	// Top border
	for (auto i = 0; i < size+2; ++i)
	{
		stream << "#";
	}
	stream << endl;

	for (auto y = 0; y < size; ++y)
	{
		stream << "#"; // Left border
		for (auto x = 0; x < size; ++x)
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
	for (auto i = 0; i < size+2; ++i)
	{
		stream << "#";
	}
	stream << endl;

	for (auto pawn : pawns)
	{
		stream << pawn << endl;
	}
	stream << *knight << endl;

	return stream;
}

bool GameBoard::isPawn(size_t x, size_t y) const
{
	for (auto pawn : pawns)
	{
		if (get<0>(pawn.position()) == x
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
