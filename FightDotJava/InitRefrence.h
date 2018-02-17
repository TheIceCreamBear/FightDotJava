#pragma once

#include <string>
#include "Constants.h"

namespace Refrence {
	std::string descriptions[Constants::GAME_WITDH * Constants::GAME_HEIGHT] = {
		"Bed room. This must be where the ruler sleeps.", "Throne Room. Who ever rules this place is large and wealthy.", "Chest storage Room. There might be valuables in these chests.",
		"Unknow purpose room. There is a shrine to an unknow diety in here as well as several mysitcal devices...", "Centeral Hall. Quiet, but bright and livid.", "Dining room. There is a long table, with a full meal on the table, but no one to eat it.",
		"Common room. There is a warm fire in here, but there are also some very intimidating paintings.", "Entrance Hallway. Large banners of some unknown faction hang from the ceiling.", "Kitchen. There are by products and utensils still out from the making of the last meal but still no people..."

	};

	// UP, LEFT, RIGHT, DOWN
	bool roomDoors[Constants::GAME_HEIGHT * Constants::GAME_WITDH][4] = {
		{ false, false, false, true },{ false, false, false, true },{ false, false, false, true },
		{ true, false, true, true },{ true, true, true, true },{ true, true, false, true },
		{ true, false, true, false },{ true, true, false, true },{ true, false, false, false }
	};

	std::string getDescriptionForRoom(int id) {
		return descriptions[id];
	}

	bool* getBoolArrayForRoom(int id) {
		return roomDoors[id];
	}
}