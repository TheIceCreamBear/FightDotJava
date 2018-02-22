#pragma once

#include "Location.h"
#include "Driection.h"
#include <string>

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
public: // all public members
	Room() = default;
	Room(RoomType type, Location loc);
	bool canLeaveFrom(Direction d) const;
	std::string getDescription() const;
	Location getLocation() const;
	RoomType getRoomType() const;
	void initDoors(Door u, Door l, Door r, Door d);

private: // all private member variables
	Location loc;
	std::string description;
	RoomType type;
	bool initialized = false;
	Door dUp;
	Door dLeft;
	Door dRight;
	Door dDown;
};