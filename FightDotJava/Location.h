#pragma once

class Location {
public:
	void add(const Location& loc) {
		x += loc.x;
		y += loc.y;
	}

	Location operator+(const Location& rhs) {
		return { x + rhs.x, y + rhs.y };
	}
	
	void operator+=(const Location& rhs) {
		x += rhs.x;
		y += rhs.y;
	}

	bool operator==(const Location& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	int x;
	int y;
};