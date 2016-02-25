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
#include <list>
#include <array>

class Node {
public:
	explicit Node(bool pawnsInOnState,
			std::bitset<8> pawnsCapturedState,
			std::tuple<size_t, size_t> knightPosition);
	explicit Node(const Node& parent, size_t moveIndex);
	std::list<Node> expand();
private:
	// State
	bool pawnsInOnState;
	std::bitset<8> pawnsCapturedState;
	std::tuple<size_t, size_t> knightPosition;
	// Node recordkeeping
	const Node* parent;
	static constexpr auto MoveOrder = std::array<std::tuple<int, int>, 8>
	{
			std::tuple<int, int>{1,-2}, // Right 1, up 2
			std::tuple<int, int>{2,-1}, // Right 2, up 1
			std::tuple<int, int>{2,1},  // Right 2, down 1
			std::tuple<int, int>{1,2},  // Right 1, down 2
			std::tuple<int, int>{-1,2}, // Left 1,  down 2
			std::tuple<int, int>{-2,1}, // Left 2,  down 1
			std::tuple<int, int>{-2,-1}, // Left 2,  up 1
			std::tuple<int, int>{-1,-2}  // Left 1,  up 2
	};
private: // Member functions
	bool isValidMove(size_t moveIndex) const;
};

#endif /* SRC_NODE_H_ */
