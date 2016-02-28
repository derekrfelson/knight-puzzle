/*
 * BFSMoveProvider.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <list>
#include "BFSMoveProvider.h"
#include "Node.h"
#include "State.h"
#include "VisitedNodes.h"

std::list<size_t> getBFSMoves(const State& state)
{
	// Create root node of search tree and clear the old tree
	VisitedNodes::setRoot(state);

	// Create fringe
	auto fringe = std::queue<std::shared_ptr<Node> > {}; // BFS uses a queue
	fringe.emplace(VisitedNodes::get(state));

	// Useful for debugging
	auto i = 0;

	while (!fringe.empty())
	{
		++i;
		std::shared_ptr<Node> currentNode = fringe.front();
		std::cout << "Expanding front: " << *currentNode
				<< std::endl << std::endl;
		fringe.pop();

		auto newNodes = currentNode->expand();

		for (auto n : newNodes)
		{
			if (n->isGoalState())
			{
				std::cout << "Nodes searched: " << i << std::endl;
				return n->getPathToRoot();
			}
			else
			{
				fringe.push(n);
			}
		}
	}

	return std::list<size_t>{};
}
