#pragma once

#include <vector>
#include "Location.h"
#include "Room.h"
#include "Item.h"

class Player {
private:
	static constexpr int BASE_HEALTH = 100; // possible idea of a limit to health restored
	static constexpr int BASE_SPECIAL_TIMER = 3; // number of tunrns the player must wait to use special again
	static constexpr float BASE_DAMAGE_MOD = 1.0f;
	enum class State {
		EXPLORING, FIGHTING
	};
public:
	Player(Room* currentRoom, int& x, int& y);
	void update();
	bool printMajorChoices();
	void printMoveChoices();
	void printRoomChoices();
	void printPlayerStats();
	bool printInventoryChoices();
	void processPlayerTrun();
	void processEnemyResponse();
	bool movedLastUpdate();
	Location getLocation() const;
	void setCurrentRoom(Room* r);
	bool shouldRun() { return this->run; }
private:
	void doCheatLoop();
	void give();
	void printInventory();
	void printItem(std::vector<Item>::iterator it);
	Location loc;
	State state;
	Room* current;
	std::vector<Item> items = std::vector<Item>();
	bool hasItemEquipped = false;
	bool moved = false;
	bool run = true;
	int equippedItemIndex = -1;
	int specialCounter = 0;
	int health = BASE_HEALTH;
	float damageMod = BASE_DAMAGE_MOD;
};