#include <iostream>
#include "GameBoard.h"
using namespace std;

int main(void) {
	GameBoard gb;
	cout << gb << endl;
	gb.next();
	cout << gb << endl;
	gb.next();
	cout << gb << endl;
	return 0;
}
