/*
 * Node.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "Node.h"
#include "GameBoard.h"

constexpr std::array<std::tuple<int, int>, 8> Node::MoveOrder;

Node::Node(bool pawnsInOnState,
		std::bitset<8> oldPawnsCapturedState,
		std::tuple<size_t, size_t> knightPosition)
: pawnsInOnState{pawnsInOnState},
  pawnsCapturedState{pawnsCapturedState},
  knightPosition{knightPosition},
  parent{nullptr}
{
}

Node::Node(const Node& parentNode, size_t moveIndex)
: Node(!parentNode.pawnsInOnState,
		parentNode.pawnsCapturedState,
		std::tuple<size_t, size_t>{
		  std::get<0>(parentNode.knightPosition)
			  + std::get<0>(Node::MoveOrder[moveIndex]),
		  std::get<1>(parentNode.knightPosition)
		  	  + std::get<1>(Node::MoveOrder[moveIndex])})
{
	this->parent = &parentNode;

	// Update the pawn capture states
	for (auto i = 0; i < 8; ++i)
	{
		if (!pawnsCapturedState[i])
		{
			// Pawn is still free, so see if knight is on top of it now
			if (knightPosition
					== GameBoard::pawns()[i].position(pawnsInOnState))
			{
				pawnsCapturedState[i] = 1;
			}
		}
	}
}

// Simply does bounds checking on a possible move, given the board state
bool Node::isValidMove(size_t moveIndex) const
{
	auto xDiff = std::get<0>(Node::MoveOrder[moveIndex]);
	auto yDiff = std::get<1>(Node::MoveOrder[moveIndex]);
	auto xPos = std::get<0>(Node::knightPosition);
	auto yPos = std::get<1>(Node::knightPosition);

	if (xDiff < 0)
	{
		if (xPos < -xDiff)
		{
			return false;
		}
	}
	else
	{
		if (xPos + xDiff >= 18)
		{
			return false;
		}
	}

	if (yDiff < 0)
	{
		if (yPos < -yDiff)
		{
			return false;
		}
	}
	else
	{
		if (yPos + yDiff >= 18)
		{
			return false;
		}
	}

	return true;
}

std::list<Node> Node::expand()
{
	auto successors = std::list<Node>{};

	for (size_t i = 0; i < Node::MoveOrder.size(); ++i)
	{
		if (isValidMove(i))
		{
			successors.emplace_back(Node{*this, i});
		}
	}

	return successors;
}
