// FightDotJava.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "Location.h"

using namespace std;
int main() {
	bool tmp[4] = { true, false, false, true };
	Room r({ 1, 2 }, "Main Room", tmp);

	cout << r.getLocation().x << " " << r.getLocation().y << endl;
	cout << r.getDescription() << endl;
	cout << r.canLeaveFrom(Direction::UP) << r.canLeaveFrom(Direction::LEFT) << r.canLeaveFrom(Direction::RIGHT) << r.canLeaveFrom(Direction::DOWN) << endl;

	system("pause");

	return 0;
}