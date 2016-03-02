/*
 * MoveProvider.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_MOVEPROVIDER_H_
#define SRC_MOVEPROVIDER_H_

#include <cstddef>
#include <list>
class State;
class Node;

std::list<size_t> getBFSMoves(const State& state);
std::list<size_t> getDFSMoves(const State& state);
std::list<size_t> getAStarMoves(const State& state);
int h1compare(size_t knightX, size_t knightY, size_t pawnX, size_t pawnY);
int h2compare(size_t knightX, size_t knightY, size_t pawnX, size_t pawnY);
int havgcompare(size_t knightX, size_t knightY, size_t pawnX, size_t pawnY);
int computeHeuristic(const Node& node);

#endif /* SRC_MOVEPROVIDER_H_ */
