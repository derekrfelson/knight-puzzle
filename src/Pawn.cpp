/*
 * Pawn.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "Pawn.h"
#include <ostream>

Pawn::Pawn(size_t startX, size_t startY, Direction direction)
: onPosition{startX, startY},
  on{true}
{
	switch (direction)
	{
	case Direction::UP:
		offPosition = std::tuple<size_t, size_t>{std::get<0>(onPosition),
			std::get<1>(onPosition) - 1};
		break;
	case Direction::RIGHT:
		offPosition = std::tuple<size_t, size_t>{ std::get<0>(onPosition) + 1,
			std::get<1>(onPosition)};
		break;
	case Direction::DOWN:
		offPosition = std::tuple<size_t, size_t>{ std::get<0>(onPosition),
			std::get<1>(onPosition) + 1};
		break;
	case Direction::LEFT:
		offPosition = std::tuple<size_t, size_t>{ std::get<0>(onPosition) - 1,
			std::get<1>(onPosition)};
		break;
	}
}

std::tuple<size_t, size_t> Pawn::position() const
{
	return on ? onPosition : offPosition;
}

std::tuple<size_t, size_t> Pawn::position(bool on) const
{
	return on ? onPosition : offPosition;
}

void Pawn::move()
{
	on = !on;
}

std::ostream& Pawn::print(std::ostream& stream) const
{
	return stream << "Pawn{ "
			<< std::get<0>(position()) << ", "
			<< std::get<1>(position()) << " }";
}

std::ostream& operator<<(std::ostream& stream, const Pawn& pawn)
{
	return pawn.print(stream);
}

