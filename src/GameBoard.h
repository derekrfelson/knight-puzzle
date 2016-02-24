/*
 * GameBoard.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef SRC_GAMEBOARD_H_
#define SRC_GAMEBOARD_H_

#include <iosfwd>
#include <cstddef>
#include <vector>
#include "Pawn.h"

class GameBoard {
public:
	explicit GameBoard();
	std::ostream& print(std::ostream& stream) const;
private:
	size_t size;
	std::vector<Pawn> pawns;
	bool isPawn(size_t x, size_t y) const;
	bool isKnight(size_t x, size_t y) const;
};

std::ostream& operator<< (std::ostream& stream, const GameBoard& board);

#endif /* SRC_GAMEBOARD_H_ */
