/*
 * VisitedNodes.h
 *
 *  Created on: Feb 28, 2016
 *      Author: derek
 */

#ifndef SRC_VISITEDNODES_H_
#define SRC_VISITEDNODES_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <cstddef>
class Node;
class State;

class VisitedNodes {
public:
	static bool contains(const State& state);
	static std::shared_ptr<Node> get(const State& state);
	static void setRoot(const State& state);
	static void addChild(const State& parentState, size_t move);
private:
	static std::unordered_map<std::string, std::shared_ptr<Node> >& get();
};

#endif /* SRC_VISITEDNODES_H_ */
