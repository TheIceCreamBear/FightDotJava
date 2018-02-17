// FightDotJava.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "Location.h"
#include "Constants.h"
#include "InitRefrence.h"
#include "Player.h"

using namespace std;

void testCode(void);

int main() {
	//testCode();

	Room rooms[Constants::GAME_HEIGHT][Constants::GAME_WITDH];

	for (int y = 0; y < Constants::GAME_HEIGHT; y++) {
		for (int x = 0; x < Constants::GAME_WITDH; x++) {
			rooms[x][y].init({x, y}, Refrence::getDescriptionForRoom((y * Constants::GAME_WITDH) + x), Refrence::getBoolArrayForRoom((y * Constants::GAME_WITDH) + x));
		}
	}

	Player p(rooms[Constants::playerStartX][Constants::playerStartY]);

	cout << "You see a castle on the horizion. Finally you made it. You enter." << endl << "Welcome to FightDotJava.cpp (A remake of the ever popular Firght.java game)." << endl;
	cout << "WARNING, THIS IS A DEVELOPMENT VERSION AND NOT ALL FEATURES ARE IMPLEMENTED!!" << endl << "Currently only the exploration works, and on a minimum level." << endl << endl;

	while (Constants::run) {
		p.update();
		if (p.movedLastUpdate()) {
			Location pLoc = p.getLocation();
			p.setCurrentRoom(rooms[pLoc.x][pLoc.y]); // FIGURE OUT WHY LOCATIONS ARE BACKWARS!!!!!
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