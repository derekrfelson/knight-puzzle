/*
 * BFSMoveProvider.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include <iostream>
#include <queue>
#include <stack>
#include "BFSMoveProvider.h"
#include "Node.h"

std::stack<size_t> getBFSMoves(bool pawnsInOnState,
		std::bitset<8> pawnsCapturedState,
		std::tuple<size_t, size_t> knightPosition)
{
	// Create root node of search tree
	auto fringe = std::queue<Node>{}; // BFS uses a queue
	fringe.emplace(Node{pawnsInOnState, pawnsCapturedState, knightPosition});

	auto i = 0;

	while (!fringe.empty())
	{
		std::cout << "Nodes: " << i << std::endl;
		++i;
		Node currentNode = fringe.front();
		fringe.pop();
		if (currentNode.isGoalState())
		{
			return currentNode.getPathToRoot();
		}
		for (auto n : currentNode.expand())
		{
			fringe.push(n);
		}
	}
}
