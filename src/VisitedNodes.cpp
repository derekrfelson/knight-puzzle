/*
 * VisitedNodes.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: derek
 */

#include <cassert>
#include <iostream>
#include "VisitedNodes.h"
#include "State.h"
#include "Node.h"

bool VisitedNodes::contains(const State& state)
{
	auto ret = get().find(state.toString()) != end(get());
	std::cout << "Is " << state.toString() << " in Visited Nodes?"
			<< (ret ? " Yes." : " No.") << std::endl;
	for(auto kv : get())
	{
		std::cout << "{" << kv.first << "," << *kv.second << "}," << std::endl;
	}
	std::cout << std::endl;
	return ret;
}

std::shared_ptr<Node> VisitedNodes::get(const State& state)
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
void VisitedNodes::setRoot(const State& state)
{
	get().clear();
	get().emplace(std::pair<std::string, std::shared_ptr<Node> >{
		state.toString(), std::make_shared<Node>(state)});
}

// Insert a child node
void VisitedNodes::addChild(const State& parentState, size_t move)
{
	State state{parentState};
	state.move(move);
	std::cerr << "VisitedNodes::insert("
			<< "state=" << state.toString() << ", "
			<< "parent=" << parentState.toString() << ", "
			<< "move=" << move << std::endl;
	assert(contains(parentState));
	get().emplace(std::pair<std::string, std::shared_ptr<Node> >{
		state.toString(), std::make_shared<Node>(
				parentState, get(parentState), move)});
}

std::unordered_map<std::string, std::shared_ptr<Node> >& VisitedNodes::get()
{
	static auto* visited =
			new std::unordered_map<std::string, std::shared_ptr<Node> >{};
	return *visited;
}
