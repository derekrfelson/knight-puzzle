/*
 * State.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include <tuple>
#include <bitset>
#include <string>

struct State {
public:
	explicit State(bool pawnsInOnState,
			std::bitset<8> pawnsCapturedState,
			std::tuple<size_t, size_t> knightPosition);
	bool pawnsInOnState;
	std::bitset<8> pawnsCapturedState;
	std::tuple<size_t, size_t> knightPosition;
	std::string toString() const;
};



#endif /* SRC_STATE_H_ */
