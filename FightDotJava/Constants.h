#pragma once
#include <random>

namespace Constants {
	static constexpr int GAME_WITDH = 5;
	static constexpr int GAME_HEIGHT = 5;
	static constexpr bool DEBUG_MODE = true;
	static const int playerStartX = 0;
	static const int playerStartY = 0;

	// If zero, use time, if not zero, use this
	static const long long reccomendSeed = 15198726674730761; // decent seed for 5x5
	
	static std::mt19937 rng = std::mt19937(0);
	static long long seed = 0; // dynamic

	static int recommendedStartX = 0;
	static int recommendedStartY = 0;

	static bool run = true;
}