// FightDotJava.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "Location.h"
#include "Constants.h"
#include "Player.h"

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

	Player p(rooms[Refrence::playerStartY][Refrence::playerStartX]);

	cout << "You see a castle on the horizion. Finally you made it. You enter." << endl << "Welcome to FightDotJava (A remake of the ever popular Firght.java game)." << endl;
	cout << "WARNING, THIS IS A DEVELOPMENT VERSION AND NOT ALL FEATURES ARE IMPLEMENTED!!" << endl << "Currently only the exploration works, and on a minimum level." << endl << endl;

	while (Refrence::run) {
		p.update();
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