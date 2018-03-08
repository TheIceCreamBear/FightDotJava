#include "Item.h"

Item::Item() {
	type = ItemType::EMPTY;
	description	= "";
	loc = { -1, -1 };
}

Item::Item(ItemType t, std::string description, Location loc) {
	type = t;
	this->description = description;
	this->loc = loc;
}

Item::Item(ItemType t, std::string description, Location loc, int effect, float multiplier) {
	type = t;
	this->description = description;
	this->loc = loc;
	this->effect = effect;
	this->multiplier = multiplier;
}

Item::ItemType Item::getType() const {
	return type;
}

std::string Item::getDescription() const {
	return description;
}

Location Item::getLocation() const {
	return loc;
}

int Item::getEffect() const {
	return effect;
}

float Item::getMultiplier() const {
	return multiplier;
}