/*
 * MoveProvider.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <list>
#include "MoveProvider.h"
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
	auto expandedNodes = 0;
	auto searchedNodes = 0;

	while (!fringe.empty())
	{
		++expandedNodes;
		std::shared_ptr<Node> currentNode = fringe.front();
		std::cout << "Expanding front: " << *currentNode
				<< std::endl << std::endl;
		fringe.pop();

		auto newNodes = currentNode->expand();

		for (auto n : newNodes)
		{
			++searchedNodes;
			if (n->isGoalState())
			{
				//std::cout << "Nodes expanded: " << expandedNodes << std::endl;
				//std::cout << "Nodes searched: " << searchedNodes << std::endl;
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

std::list<size_t> getDFSMoves(const State& state)
{
	// Create root node of search tree and clear the old tree
	VisitedNodes::setRoot(state);

	// Create fringe
	auto fringe = std::stack<std::shared_ptr<Node> > {}; // DFS uses a stack
	fringe.emplace(VisitedNodes::get(state));

	// Useful for debugging
	auto expandedNodes = 0;
	auto searchedNodes = 0;

	while (!fringe.empty())
	{
		++expandedNodes;
		std::shared_ptr<Node> currentNode = fringe.top();
		//std::cout << "Expanding top: " << *currentNode
		//		<< std::endl << std::endl;
		fringe.pop();

		auto newNodes = currentNode->expand();

		for (auto n : newNodes)
		{
			++searchedNodes;
			if (n->isGoalState())
			{
				//std::cout << "Nodes expanded: " << expandedNodes << std::endl;
				//std::cout << "Nodes searched: " << searchedNodes << std::endl;
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
