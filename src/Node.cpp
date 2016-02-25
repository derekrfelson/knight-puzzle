/*
 * Node.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <cassert>
#include <iostream>
#include <unordered_map>
#include "Node.h"
#include "State.h"
#include "GameBoard.h"
#include "Types.h"

// Create a Node based on the current state of the GameBoard
Node::Node(bool pawnsInOnState,
		std::bitset<8> pawnsCapturedState,
		std::tuple<size_t, size_t> knightPosition)
: state{
	pawnsInOnState,
	pawnsCapturedState,
	knightPosition
  },
  parent{nullptr},
  action{NoAction}
{
}

// Create a child Node based on making a move from the current node
Node::Node(const Node& parentNode, size_t moveIndex)
: Node(!parentNode.state.pawnsInOnState,
		parentNode.state.pawnsCapturedState,
		std::tuple<size_t, size_t>{
		  std::get<0>(parentNode.state.knightPosition)
			  + std::get<0>(MoveOrder[moveIndex]),
		  std::get<1>(parentNode.state.knightPosition)
		  	  + std::get<1>(MoveOrder[moveIndex])})
{
	this->parent = &parentNode;
	this->action = moveIndex;

	// Update the pawn capture states
	for (auto i = 0; i < 8; ++i)
	{
		if (!state.pawnsCapturedState[i])
		{
			// Pawn is still free, so see if knight is on top of it now
			if (state.knightPosition
					== GameBoard::pawns()[i].position(state.pawnsInOnState))
			{
				state.pawnsCapturedState[i] = 1;
			}
		}
	}
}

// Can't default this because of unique_ptr
Node::~Node()
{
}

// Simply does bounds checking on a possible move, given the board state
bool Node::isValidMove(size_t moveIndex) const
{
	auto xDiff = std::get<0>(MoveOrder[moveIndex]);
	auto yDiff = std::get<1>(MoveOrder[moveIndex]);
	auto xPos = std::get<0>(state.knightPosition);
	auto yPos = std::get<1>(state.knightPosition);

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
std::list<Node*> Node::expand()
{
	auto successors = std::list<Node*>{};

	for (size_t i = 0; i < MoveOrder.size(); ++i)
	{
		if (isValidMove(i))
		{
			auto newNode = new Node{*this, i};
			auto newState = newNode->state;
			if (Node::visitedList().find(newState.toString()) == Node::visitedList().end())
			{
				Node::visitedList().insert({newState.toString(), newNode});
				auto persistentNodeRef = *(Node::visitedList().find(newState.toString()));
				//std::cout << persistentNodeRef << std::endl;
				//std::cout << "Expanding node, passing address of " << persistentNodeRef << std::endl;
				successors.push_back(persistentNodeRef.second);
			}
			else
			{
				delete newNode;
			}
		}
	}

	return successors;
}

// A goal state is any state in which we have captured all the pawns,
// or we have captured more pawns than before.
bool Node::isGoalState() const
{
	if (state.pawnsCapturedState.all())
	{
		std::cout << "Goal found: all pawns captured" << std::endl;
		return true;
	}

	if (parent != nullptr
			&& parent->state.pawnsCapturedState.count()
			< state.pawnsCapturedState.count())
	{
		std::cout << "Goal found: captured a pawn" << std::endl;
		return true;
	}

	return false;
}

// Returns all the moves we took to get here from the root
std::list<size_t> Node::getPathToRoot()
{
	std::cout << "Getting path to root" << std::endl;
	auto moves = std::list<size_t>{};
	const Node* currentNode = this;
	while (currentNode->parent != nullptr && currentNode->action != NoAction)
	{
		std::cout << *currentNode << std::endl;
		moves.push_front(currentNode->action);
		currentNode = currentNode->parent;
	}
	return moves;
}

std::unordered_map<std::string, Node*>& Node::visitedList()
{
	static auto* visited = new std::unordered_map<std::string, Node*>{};
	return *visited;
}


std::ostream& Node::print(std::ostream& stream) const
{
	stream << "Node{ Knight{ " << std::get<0>(state.knightPosition)
			<< ", " << std::get<1>(state.knightPosition) << " }, "
			<< "Captures{ " << state.pawnsCapturedState.to_string() << " }, "
			<< "PawnState = " << (state.pawnsInOnState ? "on" : "off") << " }";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Node& node)
{
	return node.print(stream);
}

