#pragma once
#include <string>
#include "Location.h"

class Item {
public:
	enum class ItemType {
		EMPTY, HEALING, WEAPON, INSTANT_DAMAGE
	};
	Item();
	Item(ItemType t, std::string description, Location loc);
	Item(ItemType t, std::string description, Location loc, int effect, float multiplier);
	ItemType getType() const;
	std::string getDescription() const;
	Location getLocation() const;
	int getEffect() const;
	float getMultiplier() const;
	bool operator==(const Item rhs);
private:
	ItemType type;
	std::string description;
	Location loc;
	int effect;
	float multiplier;
};