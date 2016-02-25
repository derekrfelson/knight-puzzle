/*
 * Knight.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "Knight.h"
#include "Types.h"
#include <cstddef>
#include <ostream>

Knight::Knight(size_t startX, size_t startY)
: xpos{startX},
  ypos{startY}
{
}

std::tuple<size_t, size_t> Knight::position() const
{
	return std::tuple<size_t, size_t>{xpos, ypos};
}

void Knight::move(size_t moveIndex)
{
	xpos += std::get<0>(MoveOrder[moveIndex]);
	ypos += std::get<1>(MoveOrder[moveIndex]);
}

std::ostream& Knight::print(std::ostream& stream) const
{
	return stream << "Knight{ " << xpos << ", " << ypos << " }";
}

std::ostream& operator<<(std::ostream& stream, const Knight& knight)
{
	return knight.print(stream);
}
