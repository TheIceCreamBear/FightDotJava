#pragma once

#include "Location.h"
#include "Driection.h"
#include <string>

class Room {
	Room(Location loc, std::string description);
	bool canLeaveFrom(Direction d) const;
	std::string getDescription() const;
private:
	Location loc;
	std::string description;
	bool up;
	bool left;
	bool right;
	bool down;
};