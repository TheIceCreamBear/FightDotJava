#include "Room.h"

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
