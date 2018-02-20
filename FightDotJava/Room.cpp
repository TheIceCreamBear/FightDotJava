#include "Room.h"

Room::Door::Door(bool exists, bool locked) {
	this->exists = exists;
	this->locked = locked;
}

Room::Room(RoomType type, Location loc) {
	this->loc = loc;
	this->type = type;
	switch (type) {
		case Room::RoomType::ENTRANCE:

			break;
		case Room::RoomType::CENTRAL:

			break;
		case Room::RoomType::HALLWAY:

			break;
		case Room::RoomType::CHEST:

			break;
		case Room::RoomType::MYSTIC:

			break;
		default:
			this->dUp = Door(false, false);
			this->dLeft = Door(false, false);
			this->dRight = Door(false, false);
			this->dDown = Door(false, false);
			break;
	}
}

bool Room::canLeaveFrom(Direction d) const {
	switch (d) {
		case UP:
			return dUp.doesExist() && !dUp.isLocked();
			break;
		case LEFT:
			return dLeft.doesExist() && !dLeft.isLocked();
			break;
		case RIGHT:
			return dRight.doesExist() && !dRight.isLocked();
			break;
		case DOWN:
			return dDown.doesExist() && !dDown.isLocked();
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

Room::RoomType Room::getRoomType() const {
	return type;
}

void Room::initDoors(Door u, Door l, Door r, Door d) {
	if (initialized) {
		return;
	}
	initialized = true;

	this->dUp = u;
	this->dLeft = l;
	this->dRight = r;
	this->dDown = d;
}