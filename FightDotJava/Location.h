#pragma once

class Location {
public:
	void add(const Location& loc) {
		x += loc.x;
		y += loc.y;
	}
	bool operator==(const Location& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};