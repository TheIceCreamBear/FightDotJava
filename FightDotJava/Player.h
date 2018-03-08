#pragma once

#include <vector>
#include "Location.h"
#include "Room.h"
#include "Item.h"

class Player {
public:
	Player(Room& currentRoom, int& x, int& y);
	void update();
	bool printMajorChoices();
	void printMoveChoices();
	void printRoomChoices();
	void printInventoryChoices();
	bool movedLastUpdate();
	Location getLocation() const;
	void setCurrentRoom(Room& r);
private:
	void printInventory();
	Location loc;
	Room& current;
	std::vector<Item> items = std::vector<Item>();
	bool moved = false;
};