/*
 * Settings.h
 *
 *  Created on: Mar 1, 2016
 *      Author: derek
 */

#ifndef SRC_SETTINGS_H_
#define SRC_SETTINGS_H_

#include <cstddef>
#include <list>
#include <functional>
class State;

struct Settings
{
public:
	using MoveProviderFn = std::function<std::list<size_t>(const State&)>;
	static Settings& instance();
	size_t size;
	size_t numStartingPawns;
	MoveProviderFn moveProvider;
private:
	Settings();
};

#endif /* SRC_SETTINGS_H_ */
