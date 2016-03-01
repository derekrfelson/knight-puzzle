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
	std::stringstream ss;
	ss << pawnsInOnState ? "1" : "0";
	ss << pawnsCapturedState.to_string();
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

	// Update the pawn capture states
	for (auto i = 0; i < 8; ++i)
	{
		// Pawn is still free, so see if knight is on top of it now
		if (knightPosition == GameBoard::pawns()[i].position(pawnsInOnState))
		{
			pawnsCapturedState[i] = 1;
		}
	}
}
