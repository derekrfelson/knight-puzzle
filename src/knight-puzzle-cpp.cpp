#include <iostream>
#include <chrono>
#include <thread>
#include "GameBoard.h"
using namespace std;

int main(void) {
	GameBoard gb;
	for (auto i = 0; i < 40; ++i)
	{
		cout.clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << gb << endl;
		gb.next();
	}
	return 0;
}
