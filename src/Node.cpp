/*
 * Node.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "Node.h"
#include "GameBoard.h"
#include "Types.h"

// Create a Node based on the current state of the GameBoard
Node::Node(bool pawnsInOnState,
		std::bitset<8> pawnsCapturedState,
		std::tuple<size_t, size_t> knightPosition)
: pawnsInOnState{pawnsInOnState},
  pawnsCapturedState{pawnsCapturedState},
  knightPosition{knightPosition},
  parent{nullptr},
  action{NoAction}
{
}

// Create a child Node based on making a move from the current node
Node::Node(const Node& parentNode, size_t moveIndex)
: Node(!parentNode.pawnsInOnState,
		parentNode.pawnsCapturedState,
		std::tuple<size_t, size_t>{
		  std::get<0>(parentNode.knightPosition)
			  + std::get<0>(MoveOrder[moveIndex]),
		  std::get<1>(parentNode.knightPosition)
		  	  + std::get<1>(MoveOrder[moveIndex])})
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
	auto xDiff = std::get<0>(MoveOrder[moveIndex]);
	auto yDiff = std::get<1>(MoveOrder[moveIndex]);
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

// Returns all the nodes you can reach from this node's state
std::list<Node> Node::expand()
{
	auto successors = std::list<Node>{};

	for (size_t i = 0; i < MoveOrder.size(); ++i)
	{
		if (isValidMove(i))
		{
			successors.emplace_back(Node{*this, i});
		}
	}

	return successors;
}

// A goal state is any state in which we have captured all the pawns,
// or we have captured more pawns than before.
bool Node::isGoalState() const
{
	return pawnsCapturedState.all()
			|| (parent != nullptr
					&& parent->pawnsCapturedState.count()
					< pawnsCapturedState.count());
}

// Returns all the moves we took to get here from the root
std::stack<size_t> Node::getPathToRoot()
{
	auto moves = std::stack<size_t>{};
	const Node* currentNode = this;
	while (currentNode->action != NoAction)
	{
		moves.emplace(currentNode->action);
		currentNode = currentNode->parent;
	}
	return moves;
}
