// FightDotJava.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "Location.h"

#define GAME_WITDH 3
#define GAME_HEIGHT 3

using namespace std;

void testCode(void);

int main() {
	//testCode();
	Room rooms[GAME_HEIGHT][GAME_WITDH];



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