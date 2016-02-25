/*
 * Node.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <iosfwd>
#include <memory>
#include <cstddef>
#include <bitset>
#include <tuple>
#include <list>
#include <array>
#include <unordered_map>
#include <string>
#include "State.h"

class Node {
public:
	explicit Node(bool pawnsInOnState,
			std::bitset<8> pawnsCapturedState,
			std::tuple<size_t, size_t> knightPosition);
	explicit Node(const Node& parent, size_t moveIndex);
	~Node();
	std::list<Node*> expand();
	bool isGoalState() const;
	std::list<size_t> getPathToRoot();
	std::ostream& print(std::ostream& stream) const;
	static std::unordered_map<std::string, Node*>& visitedList();
private:
	// State
	State state;
	// Node recordkeeping
	const Node* parent;
	size_t action;
private: // Member functions
	bool isValidMove(size_t moveIndex) const;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);

namespace std
{
template<>
struct hash<Node> {
    size_t operator()(const Node& n) const {
        return std::hash<int>()(2) ^ std::hash<int>()(3);
    }
};
}

#endif /* SRC_NODE_H_ */
