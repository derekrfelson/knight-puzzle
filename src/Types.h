/*
 * Types.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <tuple>
#include <array>

static constexpr auto MoveOrder = std::array<std::tuple<int, int>, 8>
{
	std::tuple<int, int>{1,-2}, // Right 1, up 2
	std::tuple<int, int>{2,-1}, // Right 2, up 1
	std::tuple<int, int>{2,1},  // Right 2, down 1
	std::tuple<int, int>{1,2},  // Right 1, down 2
	std::tuple<int, int>{-1,2}, // Left 1,  down 2
	std::tuple<int, int>{-2,1}, // Left 2,  down 1
	std::tuple<int, int>{-2,-1}, // Left 2,  up 1
	std::tuple<int, int>{-1,-2}  // Left 1,  up 2
};

static constexpr size_t NoAction = 999;

#endif /* SRC_TYPES_H_ */
