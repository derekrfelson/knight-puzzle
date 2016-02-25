/*
 * BFSMoveProvider.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <iostream>
#include <memory>
#include <queue>
#include <list>
#include "BFSMoveProvider.h"
#include "Node.h"
#include "State.h"

std::list<size_t> getBFSMoves(State state)
{
	Node::visitedList().clear();

	// Create root node of search tree
	auto fringe = std::queue<Node*> {}; // BFS uses a queue
	fringe.emplace(Node::visitedList().find(state.toString())->second);

	auto i = 0;

	while (!fringe.empty())
	{
		++i;
		std::shared_ptr<Node> currentNode = fringe.front();
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
}
