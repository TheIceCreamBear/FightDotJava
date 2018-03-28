#pragma once

#include <vector>
#include "Location.h"
#include "Room.h"
#include "Item.h"

class Player {
private:
	static constexpr int BASE_HEALTH = 100; // possible idea of a limit to health restored
	static constexpr float BASE_DAMAGE_MOD = 1.0f;

public:
	Player(Room* currentRoom, int& x, int& y);
	void update();
	bool printMajorChoices();
	void printMoveChoices();
	void printRoomChoices();
	void printPlayerStats();
	void printInventoryChoices();
	bool movedLastUpdate();
	Location getLocation() const;
	void setCurrentRoom(Room* r);
private:
	void doCheatLoop();
	void give();
	void printInventory();
	void printItem(std::vector<Item>::iterator it);
	Location loc;
	Room* current;
	std::vector<Item> items = std::vector<Item>();
	int equippedItemIndex = -1;
	bool hasItemEquipped = false;
	bool moved = false;
	int health = BASE_HEALTH;
	float damageMod = BASE_DAMAGE_MOD;
};