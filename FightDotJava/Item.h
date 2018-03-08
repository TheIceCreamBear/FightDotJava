#pragma once
#include <string>
#include "Location.h"

class Item {
public:
	enum class ItemType {
		EMPTY, HEALING, WEAPON, INSTANT_DAMAGE
	};
	Item();
	Item(ItemType t, std::string description);
	Item(ItemType t, std::string description, int effect, float multiplier);
	ItemType getType() const;
	std::string getDescription() const;
	int getEffect() const;
	float getMultiplier() const;
	bool isNegativeItem() const;
	bool operator==(const Item rhs);
private:
	ItemType type;
	std::string description;
	bool negative;
	int effect;
	float multiplier;
};