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
#include <list>
#include "State.h"

class Node {
public:
	explicit Node(const State& state);
	explicit Node(const State& parentState, std::shared_ptr<Node> parent,
			size_t moveIndex);
	~Node();
	std::list<std::shared_ptr<Node> > expand();
	bool isGoalState() const;
	std::list<size_t> getPathToRoot();
	std::ostream& print(std::ostream& stream) const;
private:
	// State
	State state;
	// Node recordkeeping
	std::shared_ptr<Node> parent;
	size_t action;
private: // Member functions
	bool isValidMove(size_t moveIndex) const;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);

#endif /* SRC_NODE_H_ */
