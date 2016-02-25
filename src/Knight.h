/*
 * Knight.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_KNIGHT_H_
#define SRC_KNIGHT_H_

#include <cstddef>
#include <tuple>
#include <iosfwd>

class Knight {
public:
	explicit Knight(size_t startX, size_t startY);
	std::tuple<size_t, size_t> position() const;
	void move(size_t moveIndex);
	std::ostream& print(std::ostream& stream) const;
private:
	size_t xpos;
	size_t ypos;
};

std::ostream& operator<<(std::ostream& stream, const Knight& knight);

#endif /* SRC_KNIGHT_H_ */
