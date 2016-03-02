/*
 * AStarNode.cpp
 *
 *  Created on: Mar 2, 2016
 *      Author: derek
 */

#include "AStarNode.h"
#include "Types.h"
#include "Settings.h"
#include "VisitedAStarNodes.h"

AStarNode::AStarNode(const State& state)
: Node{state},
  cost{0},
  heuristicCost{0}
{
	heuristicCost = Settings::instance().heuristic(*this);
}

AStarNode::AStarNode(const State& parentState,
		std::shared_ptr<Node> parent,
		size_t moveIndex,
		int cost)
: Node{parentState, parent, moveIndex},
  cost{cost},
  heuristicCost{0}
{
	heuristicCost = Settings::instance().heuristic(*this);
}

AStarNode::~AStarNode()
{
}

std::list<std::shared_ptr<AStarNode> > AStarNode::expandAStar()
{
	successors.clear();

	// If previously generated (found in OPEN or CLOSED),
	// and if the new path is better than the previous one,
	// change parent pointer that was recorded in the found node

	for (size_t i = 0; i < MoveOrder.size(); ++i)
	{
		if (isValidMove(i))
		{
			auto newState = state;
			newState.move(i);

			// If not previously generated (not found in OPEN or CLOSED)
			// Evaluate, add to OPEN , and record its parent
			if (!VisitedAStarNodes::contains(newState))
			{
				VisitedAStarNodes::addChild(state, i);
				auto persistentNodeRef = VisitedAStarNodes::get(newState);
				successors.push_back(persistentNodeRef);
			}
			else
			{
				// If previously generated (found in OPEN or CLOSED),
				// and if the new path is better then the previous one
				// change parent pointer that was recorded in the found node
				auto successor = VisitedAStarNodes::get(newState);
				auto thisSPtr = VisitedAStarNodes::get(state);
				if (cost + 1 < successor->cost)
				{
					successor->changeParent(thisSPtr);
				}
			}
		}
	}

	return successors;
}

void AStarNode::changeParent(std::shared_ptr<AStarNode> parent)
{
	// If parent changed
	// - Update the cost of getting to this node
	// - Update the cost of getting to the children
	// Do this by recursively “regenerating” the successors
	// using the list of successors that had been recorded in
	// the found node
	this->parent = parent;
	cost = parent->cost + 1;
	for (auto& child : successors)
	{
		child->expand();
	}
}

int AStarNode::getHeuristic() const
{
	return heuristicCost;
}

int AStarNode::getCost() const
{
	return cost;
}
