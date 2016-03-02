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
#include <memory>
#include <list>
#include "Pawn.h"
class State;
class Knight;

class GameBoard {
public:
	~GameBoard();
	std::ostream& print(std::ostream& stream) const;
	void next();
	static GameBoard& instance();
	std::vector<Pawn> pawns;
private:
	bool pawnsInOnState;
	std::unique_ptr<Knight> knight;
	std::list<size_t> moves;
	explicit GameBoard();
	bool isPawn(size_t x, size_t y) const;
	bool isKnight(size_t x, size_t y) const;
};

std::ostream& operator<< (std::ostream& stream, const GameBoard& board);

#endif /* SRC_GAMEBOARD_H_ */
