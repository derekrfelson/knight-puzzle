/*
 * Node.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <cstddef>
#include <bitset>
#include <tuple>
#include <stack>
#include <list>
#include <array>

class Node {
public:
	explicit Node(bool pawnsInOnState,
			std::bitset<8> pawnsCapturedState,
			std::tuple<size_t, size_t> knightPosition);
	std::list<Node> expand();
	bool isGoalState() const;
	std::stack<size_t> getPathToRoot();
private:
	// State
	bool pawnsInOnState;
	std::bitset<8> pawnsCapturedState;
	std::tuple<size_t, size_t> knightPosition;
	// Node recordkeeping
	const Node* parent;
	size_t action;
private: // Member functions
	explicit Node(const Node& parent, size_t moveIndex);
	bool isValidMove(size_t moveIndex) const;
};

#endif /* SRC_NODE_H_ */
