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

std::list<size_t> getBFSMoves(const State& state);
std::list<size_t> getDFSMoves(const State& state);
std::list<size_t> getAStarMovesH1(const State& state);

#endif /* SRC_MOVEPROVIDER_H_ */
