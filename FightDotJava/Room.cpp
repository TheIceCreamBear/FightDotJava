#include "Room.h"
#include "Constants.h"
#include <random>

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
		case Room::RoomType::EMPTY:
			this->dUp = Door(false, false);
			this->dLeft = Door(false, false);
			this->dRight = Door(false, false);
			this->dDown = Door(false, false);
			this->initialized = true;
			break;
		case Room::RoomType::HALLWAY:

			break;
		case Room::RoomType::CHEST:

			break;
		case Room::RoomType::CENTRAL:

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

bool Room::isIsolatedRoom() const {
	bool isIso = false;
	for (int i = 0; i < 4; i++) {
		isIso |= this->canLeaveFrom(static_cast<Direction>(i));
	}
	return !isIso;
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

void Room::initChests() {
	if (chestInit) {
		return;
	}
	chestInit = true;

	switch (this->type) {
		case Room::RoomType::ENTRANCE:
			break;
		case Room::RoomType::EMPTY:
			break;
		case Room::RoomType::HALLWAY:
			break;
		case Room::RoomType::CHEST: {
			std::uniform_int_distribution<int> oneThree = std::uniform_int_distribution<int>(1, 3);
			int num = oneThree(Constants::rng);
			for (int i = 0; i < num; i++) {
				Item::ItemType t = static_cast<Item::ItemType>(oneThree(Constants::rng));
				std::string s = "TEMP STRING. SHOULD GET FROM A LIST OF STRINGS OF THE SAME ITEM TYPE";
				int effect = 0;
				float mult = 0.0f;
				switch (t) {
					case Item::ItemType::EMPTY:
						break;
					case Item::ItemType::HEALING: {
						std::uniform_int_distribution<int> healing = std::uniform_int_distribution<int>(1, 3);
						int heal = healing(Constants::rng);
						if (heal == 1 || heal == 2) {
							effect = 10;
						} else {
							effect = 25;
						}
						break;
					}
					case Item::ItemType::WEAPON: {
						std::uniform_real_distribution<float> f = std::uniform_real_distribution<float>(1.1f, 2.0f);
						mult = f(Constants::rng);
						break;
					}
					case Item::ItemType::INSTANT_DAMAGE: {
						std::uniform_int_distribution<int> damage = std::uniform_int_distribution<int>(1, 3);
						int dama = damage(Constants::rng);
						if (dama == 1 || dama == 2) {
							effect = 10;
						} else {
							effect = 20;
						}
						break;
					}
					default:
						break;
				}
				Item it = Item(t, s, effect, mult);
				Chest c = Chest(it);
				chests.push(c);
			}
			
			break;
		}
		case Room::RoomType::CENTRAL: {
			std::uniform_int_distribution<int> type = std::uniform_int_distribution<int>(1, 3);
			Item::ItemType t = static_cast<Item::ItemType>(type(Constants::rng));
			std::string s = "TEMP STRING. SHOULD GET FROM A LIST OF STRINGS OF THE SAME ITEM TYPE";
			int effect = 0;
			float mult = 0.0f;
			switch (t) {
				case Item::ItemType::EMPTY:
					break;
				case Item::ItemType::HEALING: {
					std::uniform_int_distribution<int> healing = std::uniform_int_distribution<int>(1, 3);
					int heal = healing(Constants::rng);
					if (heal == 1 || heal == 2) {
						effect = 10;
					} else {
						effect = 25;
					}
					break;
				}
				case Item::ItemType::WEAPON: {
					std::uniform_real_distribution<float> f = std::uniform_real_distribution<float>(1.1f, 2.0f);
					mult = f(Constants::rng);
					break;
				}
				case Item::ItemType::INSTANT_DAMAGE: {
					std::uniform_int_distribution<int> damage = std::uniform_int_distribution<int>(1, 3);
					int dama = damage(Constants::rng);
					if (dama == 1 || dama == 2) {
						effect = 10;
					} else {
						effect = 20;
					}
					break;
				}
				default:
					break;
			}
			Item i = Item(t, s, effect, mult);
			Chest c = Chest(i);
			chests.push(c);
			break;
		}
		case Room::RoomType::MYSTIC: {
			std::uniform_int_distribution<int> type = std::uniform_int_distribution<int>(1, 3);
			Item::ItemType t = static_cast<Item::ItemType>(type(Constants::rng));
			std::string s = "TEMP STRING. SHOULD GET FROM A LIST OF STRINGS OF THE SAME ITEM TYPE";
			int effect = 0;
			float mult = 0.0f;
			switch (t) {
				case Item::ItemType::EMPTY:
					break;
				case Item::ItemType::HEALING: {
					std::uniform_int_distribution<int> healing = std::uniform_int_distribution<int>(1, 3);
					int heal = healing(Constants::rng);
					if (heal == 1 || heal == 2) {
						effect = 25;
					} else {
						effect = 50;
					}
					break;

				}
				case Item::ItemType::WEAPON: {
					std::uniform_real_distribution<float> f = std::uniform_real_distribution<float>(1.5f, 2.5f);
					mult = f(Constants::rng);
					break;
				}
				case Item::ItemType::INSTANT_DAMAGE: {
					std::uniform_int_distribution<int> damage = std::uniform_int_distribution<int>(1, 3);
					int dama = damage(Constants::rng);
					if (dama == 1 || dama == 2) {
						effect = 10;
					} else {
						effect = 25;
					}
					break;
				}
				default:
					break;
			}
			Item i = Item(t, s, effect, mult);
			Chest c = Chest(i);
			chests.push(c);
			break;
		}
		default:
			break;
	}
}

bool Room::hasLootableChest() {
	return !chests.empty();
}

Item Room::lootChest() {
	if (chests.empty()) {
		return Item();
	}

	Chest& c = chests.front();
	chests.pop();

	if (!c.isLooted()) {
		return c.loot();
	} else {
		return Item();
	}
}

Room::Chest& Room::Chest::operator=(const Chest & rhs) {
	if (*this != rhs) {
		this->looted = rhs.looted;
		item = rhs.item;
	}
	return *this;
}

bool Room::Chest::operator==(const Chest & rhs) {
	if (this->item == rhs.item && this->looted == rhs.looted) {
		return true;
	}
	return false;
}

bool Room::Chest::operator!=(const Chest & rhs) {
	return !(*this == rhs);
}