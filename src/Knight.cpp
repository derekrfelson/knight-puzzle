/*
 * Knight.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "Knight.h"
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

std::ostream& Knight::print(std::ostream& stream) const
{
	return stream << "Knight{ " << xpos << ", " << ypos << " }";
}

std::ostream& operator<<(std::ostream& stream, const Knight& knight)
{
	return knight.print(stream);
}
