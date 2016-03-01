/*
 * State.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "State.h"
#include "Types.h"
#include "GameBoard.h"
#include <sstream>
#include <string>

State::State(bool pawnsInOnState, std::tuple<size_t, size_t> knightPosition)
: pawnsInOnState{pawnsInOnState},
  knightPosition{knightPosition}
{
}

std::string State::toString() const
{
	std::stringstream ss;
	ss << pawnsInOnState ? "1" : "0";
	ss << std::get<0>(knightPosition);
	ss << ":";
	ss << std::get<1>(knightPosition);
	return ss.str();
}

void State::move(size_t index)
{
	// Update pawn positions
	pawnsInOnState = !pawnsInOnState;

	// Update knight positions
	knightPosition = std::tuple<size_t, size_t>{
		std::get<0>(knightPosition) + std::get<0>(MoveOrder[index]),
		std::get<1>(knightPosition) + std::get<1>(MoveOrder[index])};
}
