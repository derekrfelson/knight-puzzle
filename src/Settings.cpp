/*
 * Settings.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: derek
 */

#include "Settings.h"
#include "MoveProvider.h"

Settings::Settings()
: size{18},
  numStartingPawns{8},
  moveProvider{getBFSMoves},
  heuristic{h1}
{
}

Settings& Settings::instance()
{
	static Settings* instance = new Settings{};
	return *instance;
}
