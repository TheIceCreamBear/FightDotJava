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
	bool movedLastUpdate();
	Location getLocation() const;
private:
	Location loc;
	Room& current;
	bool moved = false;
};