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

using NodeHeuristicPair = std::pair<int, std::shared_ptr<Node> >;

static int h1(const Node& node)
{
	return 0;
}

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
		//std::cout << "Expanding front: " << *currentNode
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

std::list<size_t> getAStarMovesH1(const State& state)
{
	auto cmp = [](
			const NodeHeuristicPair& left,
			const NodeHeuristicPair& right)
			{ return left.first < right.first; };

	// Initialize OPEN to initial state
	VisitedNodes::setRoot(state);
	std::priority_queue<NodeHeuristicPair,
	    std::vector<NodeHeuristicPair>, decltype(cmp)> fringe(cmp);
	auto rootNode = VisitedNodes::get(state);
	fringe.push({h1(*rootNode), rootNode});

	// Useful for debugging
	auto expandedNodes = 0;
	auto searchedNodes = 0;

	// Until a Goal is found or no nodes left in OPEN do
	while (!fringe.empty())
	{
		++expandedNodes;

		// Pick the best node in OPEN
		std::shared_ptr<Node> currentNode = fringe.top().second;

		// Place in CLOSED
		fringe.pop();

		// Generate its successors (recording the successors in a list)
		auto successors = currentNode->expand();

		// For each successor do:
		for (auto& n : successors)
		{
			// If not previously generated (not found in OPEN or CLOSED)
			// Evaluate, add to OPEN , and record its parent
			++searchedNodes;
			if (n->isGoalState())
			{
//				std::cout << "Nodes expanded: " << expandedNodes << std::endl;
//				std::cout << "Nodes searched: " << searchedNodes << std::endl;
				return n->getPathToRoot();
			}
			else
			{
				fringe.emplace(NodeHeuristicPair{h1(*n), n});
			}

			// If previously generated (found in OPEN or CLOSED),
			// and if the new path is better than the previous one,
			// change parent pointer that was recorded in the found node

			// If parent changed
			// - Update the cost of getting to this node
			// - Update the cost of getting to the children
			// Do this by recursively “regenerating” the successors
			// using the list of successors that had been recorded
			// in the found node.
			// Make sure the priority queue is reordered accordingly
		}
	}

	return std::list<size_t>{};
}
