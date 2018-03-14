#include "Item.h"
#include "Constants.h"

Item::Item() {
	type = ItemType::EMPTY;
	description	= "";
	effect = 0;
	multiplier = 0.0f;
	negative = false;
	id = -1;
}

Item::Item(ItemType t, std::string description) {
	type = t;
	this->description = description;
	if (type == ItemType::INSTANT_DAMAGE || type == ItemType::WEAPON) {
		negative = true;
	} else {
		negative = false;
	}
	id = Constants::itemID;
	Constants::itemID++;
}

Item::Item(ItemType t, std::string description, int effect, float multiplier) {
	type = t;
	this->description = description;
	this->effect = effect;
	this->multiplier = multiplier;
	if (type == ItemType::INSTANT_DAMAGE || type == ItemType::WEAPON) {
		negative = true;
	} else {
		negative = false;
	}
	id = Constants::itemID;
	Constants::itemID++;
}

Item::ItemType Item::getType() const {
	return type;
}

std::string Item::getDescription() const {
	return description;
}

int Item::getEffect() const {
	return effect;
}

float Item::getMultiplier() const {
	return multiplier;
}

bool Item::isNegativeItem() const {
	return negative;
}

bool Item::operator==(const Item rhs) {
	if (this->type == rhs.type && this->description == rhs.description && this->effect == rhs.effect && this->multiplier == rhs.multiplier) {
		return true;
	}
	return false;
}