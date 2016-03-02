/*
 * AStarNode.h
 *
 *  Created on: Mar 2, 2016
 *      Author: derek
 */

#ifndef SRC_ASTARNODE_H_
#define SRC_ASTARNODE_H_

#include "Node.h"

class AStarNode: public Node {
public:
	explicit AStarNode(const State& state);
	explicit AStarNode(const State& parentState, std::shared_ptr<Node> parent,
			size_t moveIndex, int cost);
	int getCost() const;
	int getHeuristic() const;
	virtual ~AStarNode();
	std::list<std::shared_ptr<AStarNode> > expandAStar();
private:
	std::list<std::shared_ptr<AStarNode> > successors;
	int cost; // same as depth
	int heuristicCost;
	void changeParent(std::shared_ptr<AStarNode> parent);
};

#endif /* SRC_ASTARNODE_H_ */
