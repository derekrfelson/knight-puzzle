/*
 * State.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include <tuple>
#include <iosfwd>
#include <bitset>
#include <string>
#include <cstddef>

struct State {
public:
	explicit State(bool pawnsInOnState,
			std::tuple<size_t, size_t> knightPosition);
	void move(size_t index);
	bool pawnsInOnState;
	std::tuple<size_t, size_t> knightPosition;
	std::string toString() const;
	std::ostream& print(std::ostream& stream) const;
};

std::ostream& operator<<(std::ostream& stream, const State& state);

#endif /* SRC_STATE_H_ */
