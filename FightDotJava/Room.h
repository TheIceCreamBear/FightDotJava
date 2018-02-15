#pragma once

#include "Location.h"
#include "Driection.h"
#include <string>

class Room {
public:
	Room() = default;
	Room(Location loc, std::string description, bool doors[4]);
	bool canLeaveFrom(Direction d) const;
	std::string getDescription() const;
	Location getLocation() const;
private:
	Location loc;
	std::string description;
	bool up;
	bool left;
	bool right;
	bool down;
};