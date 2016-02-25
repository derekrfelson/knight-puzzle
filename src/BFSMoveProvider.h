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

std::list<size_t> getBFSMoves(bool pawnsInOnState,
		std::bitset<8> pawnsCapturedState,
		std::tuple<size_t, size_t> knightPosition);

#endif /* SRC_BFSMOVEPROVIDER_H_ */
