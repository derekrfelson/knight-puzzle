/*
 * Pawn.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_PAWN_H_
#define SRC_PAWN_H_

#include <tuple>
#include <cstddef>
#include <iosfwd>

enum class Direction : uint8_t { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

class Pawn {
public:
	explicit Pawn(size_t startX, size_t startY, Direction direction);
	std::tuple<size_t, size_t> position() const;
	std::tuple<size_t, size_t> position(bool on) const;
	void move();
	void capture();
	bool captured() const;
	std::ostream& print(std::ostream& stream) const;
private:
	std::tuple<size_t, size_t> onPosition;
	std::tuple<size_t, size_t> offPosition;
	bool on;
	bool isCaptured;
};

std::ostream& operator<< (std::ostream& stream, const Pawn& pawn);

#endif /* SRC_PAWN_H_ */
