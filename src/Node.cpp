/*
 * Node.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <cassert>
#include <iostream>
#include "Node.h"
#include "State.h"
#include "GameBoard.h"
#include "Types.h"
#include "VisitedNodes.h"
#include "Settings.h"

// Create a Node based on the current state of the GameBoard
Node::Node(const State& state)
: state{state},
  parent{nullptr},
  action{NoAction}
{
}

// Create a child Node based on making a move from the current node
Node::Node(const State& parentState,
		std::shared_ptr<Node> parent, size_t moveIndex)
: Node{parentState}
{
	state.move(moveIndex);
	this->parent = parent;
	this->action = moveIndex;
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
		if (xPos + xDiff >= Settings::instance().size)
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
		if (yPos + yDiff >= Settings::instance().size)
		{
			return false;
		}
	}

	return true;
}

// Returns all the nodes you can reach from this node's state
std::list<std::shared_ptr<Node> > Node::expand()
{
	auto successors = std::list<std::shared_ptr<Node> >{};

	for (size_t i = 0; i < MoveOrder.size(); ++i)
	{
		if (isValidMove(i))
		{
			auto newState = state;
			newState.move(i);
			if (!VisitedNodes::contains(newState))
			{
				VisitedNodes::addChild(state, i);
				auto persistentNodeRef = VisitedNodes::get(newState);
				successors.push_back(persistentNodeRef);
			}
		}
	}

	return successors;
}

// A goal state is any state in which we have captured all the pawns,
// or we have captured more pawns than before.
bool Node::isGoalState() const
{
	for (const auto& pawn : GameBoard::instance().pawns)
	{
		if (!pawn.captured()
				&& pawn.position(state.pawnsInOnState) == state.knightPosition)
		{
			return true;
		}
	}

	return false;
}

// Returns all the moves we took to get here from the root
std::list<size_t> Node::getPathToRoot()
{
	//std::cout << "Getting path to root" << std::endl;
	auto moves = std::list<size_t>{};
	const Node* currentNode = this;
	std::cout << "Path to root:" << std::endl;
	while (currentNode->parent != nullptr && currentNode->action != NoAction)
	{
		std::cout << *currentNode << std::endl;
		moves.push_front(currentNode->action);
		currentNode = currentNode->parent.get();
	}
	return moves;
}

std::ostream& Node::print(std::ostream& stream) const
{
	stream << "Node{ Knight{ " << std::get<0>(state.knightPosition)
			<< ", " << std::get<1>(state.knightPosition) << " }, "
			<< "PawnState = " << (state.pawnsInOnState ? "on" : "off") << " }";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Node& node)
{
	return node.print(stream);
}

