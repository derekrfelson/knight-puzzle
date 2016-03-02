/*
 * VisitedAStarNodes.cpp
 *
 *  Created on: Mar 2, 2016
 *      Author: derek
 */

#include <cassert>
#include <iostream>
#include "VisitedAStarNodes.h"
#include "State.h"
#include "Node.h"
#include "AStarNode.h"

bool VisitedAStarNodes::contains(const State& state)
{
	return get().find(state.toString()) != end(get());
}

std::shared_ptr<AStarNode> VisitedAStarNodes::get(const State& state)
{
	auto res = get().find(state.toString());
	if (res != end(get()))
	{
		return res->second;
	}
	else
	{
		return nullptr;
	}
}

// Insert a root node; should only be called when no nodes visited yet
void VisitedAStarNodes::setRoot(const State& state)
{
	get().clear();
	get().emplace(std::pair<std::string, std::shared_ptr<AStarNode> >{
		state.toString(), std::make_shared<AStarNode>(state)});
}

// Insert a child node
void VisitedAStarNodes::addChild(const State& parentState, size_t move)
{
	State state{parentState};
	state.move(move);
	assert(contains(parentState)); // Parent does not exist
	assert(!contains(state)); // Child already visited

	//std::cout << "Adding child " << state
	//		<< "(" << move << " from " << parentState << ")" << std::endl;
	get().emplace(std::pair<std::string, std::shared_ptr<AStarNode> >{
		state.toString(), std::make_shared<AStarNode>(
				parentState, get(parentState), move,
				get(parentState)->getCost()+1)});
}

std::unordered_map<std::string, std::shared_ptr<AStarNode> >&
VisitedAStarNodes::get()
{
	static auto* visited =
			new std::unordered_map<std::string, std::shared_ptr<AStarNode> >{};
	return *visited;
}
