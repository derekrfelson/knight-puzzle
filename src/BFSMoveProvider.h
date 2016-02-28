/*
 * BFSMoveProvider.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_BFSMOVEPROVIDER_H_
#define SRC_BFSMOVEPROVIDER_H_

#include <cstddef>
#include <bitset>
#include <tuple>
#include <list>
class State;

std::list<size_t> getBFSMoves(const State& state);

#endif /* SRC_BFSMOVEPROVIDER_H_ */
