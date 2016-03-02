/*
 * VisitedAStarNodes.h
 *
 *  Created on: Mar 2, 2016
 *      Author: derek
 */

#ifndef SRC_VISITEDASTARNODES_H_
#define SRC_VISITEDASTARNODES_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <cstddef>
class AStarNode;
class State;

class VisitedAStarNodes {
public:
	static bool contains(const State& state);
	static std::shared_ptr<AStarNode> get(const State& state);
	static void setRoot(const State& state);
	static void addChild(const State& parentState, size_t move);
private:
	static std::unordered_map<std::string, std::shared_ptr<AStarNode> >& get();
};

#endif /* SRC_VISITEDASTARNODES_H_ */
