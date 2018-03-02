#pragma once

#include "Location.h"
#include "Room.h"

class Player {
public:
	Player(Room& currentRoom, int& x, int& y);
	void update();
	bool printMajorChoices();
	void printMoveChoices();
	void printRoomChoices();
	bool movedLastUpdate();
	Location getLocation() const;
	void setCurrentRoom(Room& r);
private:
	Location loc;
	Room& current;
	bool moved = false;
};