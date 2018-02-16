#pragma once

#include "Location.h"
#include "Room.h"

class Player {
public:
	Player(Room& currentRoom);
	void update();
	bool printMajorChoices();
	void printMoveChoices();
	void printRoomChoices();
private:
	Location loc;
	Room& current;
};