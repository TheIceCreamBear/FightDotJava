#include "Player.h"
#include "Driection.h"
#include "Constants.h"
#include <iostream>

Player::Player(Room& currentRoom, int& x, int& y)
	:
	current(currentRoom) {
	this->loc = { x, y };
}

void Player::update() {
	// pre turn var reset
	moved = false;
	// end

	// process turn
	while (!printMajorChoices()) {}
	// end

	// after turn processing
	// end
}

bool Player::printMajorChoices() {
	using namespace std;
	cout << endl << "What would you like to do?" << endl;
	cout << "1. Explore currently occupied room." << endl;
	cout << "2. Move to another room." << endl;
	cout << "3. Exit game. (WARNING, THIS OPTION IS TEMPORARY)." << endl;

	int choice;
	cin >> choice;
	switch (choice) {
		case 1:
			cout << "You explore your current room." << endl;
			cout << current.getDescription() << endl;
			cout << "Location: x=" << loc.x << " y=" << loc.y << endl;
			Location rloc = current.getLocation();
			cout << "RoomLocation: x=" << rloc.x << " y=" << rloc.y << endl;
			cout << static_cast<int>(current.getRoomType()) << endl;
			return true;
		case 2:
			printMoveChoices();
			return true;
			break;
		case 3:
			cout << "Are you sure you wish to exit? (Y/N): ";
			char choice;
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				Constants::run = false;
			} else {
				cout << "Heh, that's what I though." << endl << endl;
			}
			Constants::run = false;
			return true;
		default:
			cout << "That is not an available choice, please try again." << endl;
			return false;
	}
}

void Player::printMoveChoices() {
	using namespace std;
	bool valid = false;
	while (!valid) {
		cout << "Where would you like to go?" << endl;
		for (int i = 0; i < 4; i++) {
			Direction val = static_cast<Direction>(i);
			if (current.canLeaveFrom(val)) {
				switch (val) {
					case UP:
						cout << "1. UP" << endl;
						break;
					case LEFT:
						cout << "2. LEFT" << endl;
						break;
					case RIGHT:
						cout << "3. RIGHT" << endl;
						break;
					case DOWN:
						cout << "4. DOWN" << endl;
						break;
					default:
						break;
				}
			}
		}

		int choice;
		cin >> choice;

		choice--;
		Direction val = static_cast<Direction>(choice);

		switch (val) {
			case UP:
				loc += {0, -1};
				valid = true;
				break;
			case LEFT:
				loc += {-1, 0};
				valid = true;
				break;
			case RIGHT:
				loc += {1, 0};
				valid = true;
				break;
			case DOWN:
				loc += {0, 1};
				valid = true;
				break;
			default:
				cout << "Sorry, invalid input. Please try again." << endl;
				valid = false;
				break;
		}

		if (valid) {
			cout << "You have entered a new room." << endl;
			moved = true;
		}
	}
}

// EVENTUALLY TERE WILL BE SOME CHOICES SPECIFIC TO SOME ROOMS
void Player::printRoomChoices() {
	using namespace std;

}

bool Player::movedLastUpdate() {
	return moved;
}

Location Player::getLocation() const {
	return loc;
}

void Player::setCurrentRoom(Room& r) {
	current = r;
}