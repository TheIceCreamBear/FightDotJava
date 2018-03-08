#pragma once
#include <string>
#include "Location.h"

class Item {
public:
	enum class ItemType {
		HEALING, WEAPON, INSTANT_DAMAGE
	};
	Item(ItemType t, std::string description, Location loc);
	Item(ItemType t, std::string description, Location loc, int effect, float multiplier);
	ItemType getType() const;
	std::string getDescription() const;
	Location getLocation() const;
	int getEffect() const;
	float getMultiplier() const;
private:
	ItemType type;
	std::string description;
	Location loc;
	int effect;
	float multiplier;
};