/*
 * State.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "State.h"

State::State(bool pawnsInOnState,
		std::bitset<8> pawnsCapturedState,
		std::tuple<size_t, size_t> knightPosition)
: pawnsInOnState{pawnsInOnState},
  pawnsCapturedState{pawnsCapturedState},
  knightPosition{knightPosition}
{
}

std::string State::toString() const
{
	return (pawnsInOnState ? "1" : "0")
			+ pawnsCapturedState.to_string()
			+ get<0>(knightPosition)
			+ get<1>(knightPosition);
}
