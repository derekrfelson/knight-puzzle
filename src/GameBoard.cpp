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
using namespace std;

GameBoard::GameBoard()
: size{18}, pawns{}
{
	// Seed the random number generator with random data from the OS
	auto gen = std::mt19937{std::random_device{}()};
	auto randBoardSize = std::uniform_int_distribution<size_t>{0, size};
	auto randDirection = std::uniform_int_distribution<size_t>(0, 3);

	// Generate the pawns we start with
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

			if (validPawn)
			{
				// Generate the pawn
				pawns.emplace_back(Pawn{startX, startY, d});
			}
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
	return false;
}

std::ostream& operator<< (std::ostream& stream, const GameBoard& board)
{
	return board.print(stream);
}
