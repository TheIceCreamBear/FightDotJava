#pragma once

#include <string>
#include <queue>
#include "Constants.h"
#include "Location.h"
#include "Driection.h"
#include "Item.h"

class Room {
public: // prototype innerclasses
	enum class RoomType {
		ENTRANCE, EMPTY, HALLWAY, CHEST, CENTRAL, MYSTIC
	};
	class Door {
	public:
		Door() : Door(false, false) {} // Default constructor set to false
		Door(bool exists, bool locked);
		bool doesExist() const { return exists; }
		bool isLocked() const { return locked; }
	private:
		bool exists;
		bool locked;
	};
private:
	class Chest {
	public:
		Chest(Item i) : item(i) { id = Constants::chestID; Constants::chestID++; }
		bool isLooted() { return looted; }
		Item loot() { 
			looted = true; 
			return item; 
		}
		Chest& operator=(const Chest& rhs);
		bool operator==(const Chest& rhs);
		bool operator!=(const Chest& rhs);
	private:
		int id;
		bool looted = false;
		Item item;
	};

public: // all public members
	Room() = default;
	Room(RoomType type, Location loc);
	bool canLeaveFrom(Direction d) const;
	bool isIsolatedRoom() const;
	std::string getDescription() const;
	Location getLocation() const;
	RoomType getRoomType() const;
	void initDoors(Door u, Door l, Door r, Door d);
	void initChests();
	bool hasLootableChest();
	Item lootChest();
private: // all private member variables
	Location loc;
	std::string description;
	RoomType type;
	std::queue<Chest> chests = std::queue<Chest>();
	bool initialized = false;
	bool chestInit = false;
	Door dUp;
	Door dLeft;
	Door dRight;
	Door dDown;
};