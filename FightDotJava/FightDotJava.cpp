// FightDotJava.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "Location.h"
#include "Constants.h"

using namespace std;

void testCode(void);

int main() {
	//testCode();
	Room rooms[Refrence::GAME_HEIGHT][Refrence::GAME_WITDH];

	for (int y = 0; y < Refrence::GAME_HEIGHT; y++) {
		for (int x = 0; x < Refrence::GAME_WITDH; x++) {
			rooms[x][y].init({x, y}, Refrence::getDescriptionForRoom((y * Refrence::GAME_WITDH) + x), Refrence::getBoolArrayForRoom((y * Refrence::GAME_WITDH) + x));
		}
	}



	system("pause");

	return 0;
}

void testCode() {
	bool tmp[4] = { true, false, false, true };
	Room r({ 1, 2 }, "Main Room", tmp);

	cout << r.getLocation().x << " " << r.getLocation().y << endl;
	cout << r.getDescription() << endl;
	cout << r.canLeaveFrom(Direction::UP) << r.canLeaveFrom(Direction::LEFT) << r.canLeaveFrom(Direction::RIGHT) << r.canLeaveFrom(Direction::DOWN) << endl;
}