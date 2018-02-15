#include "Room.h"

Room::Room(Location loc, std::string description, bool doors[4]) {
	this->loc = loc;
	this->description = description;
	up = doors[0];
	left = doors[1];
	right = doors[2];
	down = doors[3];
}

bool Room::canLeaveFrom(Direction d) const {
	switch (d) {
		case UP:
			return up;
			break;
		case LEFT:
			return left;
			break;
		case RIGHT:
			return right;
			break;
		case DOWN:
			return down;
			break;
		default:
			break;
	}
	return false;
}

std::string Room::getDescription() const {
	return description;
}

Location Room::getLocation() const {
	return loc;
}
