// FightDotJava.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include "Room.h"
#include "Location.h"
#include "Constants.h"
#include "InitRefrence.h"
#include "Player.h"

Room rooms[Constants::GAME_HEIGHT][Constants::GAME_WITDH];

using namespace std;

void testCode(void);
void findPlayerStartLoc(void);
void initRooms(void);
void printRooms(void);

int main() {
	initRooms();

	printRooms(); // THIS IS A DEBUG CODE CALL

	system("pause");

	findPlayerStartLoc();

	int pStartX = Constants::playerStartX;
	int pStartY = Constants::playerStartY;

	if (Constants::recommendedStartX != Constants::playerStartX) {
		pStartX = Constants::recommendedStartX;
	}
	if (Constants::recommendedStartY != Constants::playerStartY) {
		pStartY = Constants::recommendedStartY;
	}

	cout << "Start position: x=" << pStartX << " y=" << pStartY << endl;

	system("Pause");

	Player p(rooms[pStartY][pStartX], pStartX, pStartY);

	cout << "You see a castle on the horizion. Finally you made it. You enter." << endl << "Welcome to FightDotJava.cpp (A remake of the ever popular Fight.java game)." << endl;
	cout << "WARNING, THIS IS A DEVELOPMENT VERSION AND NOT ALL FEATURES ARE IMPLEMENTED!!" << endl << "Currently only the exploration works, and on a minimum level." << endl << endl;

	while (Constants::run) {
		p.update();
		if (p.movedLastUpdate()) {
			Location pLoc = p.getLocation();
			p.setCurrentRoom(rooms[pLoc.y][pLoc.x]); // FIGURE OUT WHY LOCATIONS ARE BACKWARS!!!!!
		}
	}


	system("pause");

	return 0;
}

void findPlayerStartLoc(void) {
	for (int i = 0; i < Constants::GAME_WITDH; i++) {
		Room* current = &rooms[0][i];
		if (current->getRoomType() != Room::RoomType::ENTRANCE) {
			continue;
		} else {
			if (current->isIsolatedRoom()) {
				continue;
			} else {
				Constants::recommendedStartX = i;
				Constants::recommendedStartY = 0;
				return;
			}
		}
	}

	cout << "Failure to find valid entracne in the first row." << endl;
}

void initRooms(void) {
	long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	seed = 15198726674730761; // decent seed for 5x5

	std::mt19937 rng(seed);
	// Init room loop

	int numEnt = 0;
	for (int y = 0; y < Constants::GAME_HEIGHT; y++) {
		for (int x = 0; x < Constants::GAME_WITDH; x++) {
			Room::RoomType r;
			Location l = { x, y };

			// allow only for entrences, empty, and hallways in the outer row col
			if ((y == 0 || x == 0 || y == Constants::GAME_HEIGHT - 1 || x == Constants::GAME_WITDH - 1) && numEnt < 3) {
				std::uniform_int_distribution<int> type(static_cast<int>(Room::RoomType::ENTRANCE), static_cast<int>(Room::RoomType::HALLWAY));
				int iType = type(rng);
				//numEnt++;
				r = static_cast<Room::RoomType>(iType);
			} else if ((y == 0 || x == 0 || y == Constants::GAME_HEIGHT - 1 || x == Constants::GAME_WITDH - 1) && numEnt <= 3) {
				std::uniform_int_distribution<int> type(static_cast<int>(Room::RoomType::EMPTY), static_cast<int>(Room::RoomType::HALLWAY));
				int iType = type(rng);
				r = static_cast<Room::RoomType>(iType);
			} else { // allow for all but entrences in the inner locations
				std::uniform_int_distribution<int> type(static_cast<int>(Room::RoomType::EMPTY), static_cast<int>(Room::RoomType::MYSTIC));
				int iType = type(rng);
				r = static_cast<Room::RoomType>(iType);
			}

			rooms[y][x] = Room(r, l);
			// , std::string("ID=" + y + ',' + x)
		}
	}

	// Init doors loop
	/*
	*	This loop initializes the doors of all of the room based on what they are connected to.
	*	This is an annoy little algo but its necessary for my master vision for this game
	*	(One where evey play through is unique adding replayability to the game)
	*/
	for (int y = 0; y < Constants::GAME_HEIGHT; y++) {
		for (int x = 0; x < Constants::GAME_WITDH; x++) {
			Room* current = &rooms[x][y];
			if (current->getRoomType() == Room::RoomType::EMPTY) {
				continue;
			}
			Room::Door up;
			Room::Door left;
			Room::Door right;
			Room::Door down;

			if (y == 0) {
				up = Room::Door(); // REDUNDANT
				Room* r = &rooms[1][x];
				Room::RoomType rType = r->getRoomType();
				switch (rType) {
					case Room::RoomType::ENTRANCE:
						down = Room::Door(true, false);
						/*if (current->getRoomType() == Room::RoomType::HALLWAY) {
						} else {
							down = Room::Door(false, false);
						}*/
						break;
					case Room::RoomType::EMPTY:
						down = Room::Door(false, false);
						break;
					case Room::RoomType::HALLWAY:
						down = Room::Door(true, false);
						break;
					case Room::RoomType::CHEST:
						down = Room::Door(true, false); // todo locking
						break;
					case Room::RoomType::CENTRAL:
						down = Room::Door(true, false);
						break;
					case Room::RoomType::MYSTIC:
						down = Room::Door(true, false);
						break;
					default:
						break;
				}
			} else if (y == Constants::GAME_HEIGHT - 1) {
				down = Room::Door(); // REDUNDANT
				Room* r = &rooms[Constants::GAME_HEIGHT - 2][x];
				Room::RoomType rType = r->getRoomType();
				switch (rType) {
					case Room::RoomType::ENTRANCE:
						up = Room::Door(true, false);
						/*if (current->getRoomType() == Room::RoomType::HALLWAY) {
						} else {
						up = Room::Door(false, false);
						}*/
						break;
					case Room::RoomType::EMPTY:
						up = Room::Door(false, false);
						break;
					case Room::RoomType::HALLWAY:
						up = Room::Door(true, false);
						break;
					case Room::RoomType::CHEST:
						up = Room::Door(true, false); // todo locking
						break;
					case Room::RoomType::CENTRAL:
						up = Room::Door(true, false);
						break;
					case Room::RoomType::MYSTIC:
						up = Room::Door(true, false);
						break;
					default:
						break;
				}
			} else {
				Room* rU = &rooms[y - 1][x];
				Room::RoomType rType1 = rU->getRoomType();
				if (rType1 != Room::RoomType::EMPTY) {
					up = Room::Door(true, false);
				}

				Room* rD = &rooms[y + 1][x];
				Room::RoomType rType2 = rD->getRoomType();
				if (rType2 != Room::RoomType::EMPTY) {
					down = Room::Door(true, false);
				}
			}
			// end if

			if (x == 0) {
				left = Room::Door(); // REDUNDANT
				Room* r = &rooms[y][1];
				Room::RoomType rType = r->getRoomType();
				switch (rType) {
					case Room::RoomType::ENTRANCE:
						right = Room::Door(true, false);
						/*if (current->getRoomType() == Room::RoomType::HALLWAY) {
						} else {
						right = Room::Door(false, false);
						}*/
						break;
					case Room::RoomType::EMPTY:
						right = Room::Door(false, false);
						break;
					case Room::RoomType::HALLWAY:
						right = Room::Door(true, false);
						break;
					case Room::RoomType::CHEST:
						right = Room::Door(true, false); // todo locking
						break;
					case Room::RoomType::CENTRAL:
						right = Room::Door(true, false);
						break;
					case Room::RoomType::MYSTIC:
						right = Room::Door(true, false);
						break;
					default:
						break;
				}
			} else if (x == Constants::GAME_WITDH - 1) {
				right = Room::Door(); // REDUNDANT
				Room* r = &rooms[y][Constants::GAME_WITDH - 2];
				Room::RoomType rType = r->getRoomType();
				switch (rType) {
					case Room::RoomType::ENTRANCE:
						left = Room::Door(true, false);
						/*if (current->getRoomType() == Room::RoomType::HALLWAY) {
						} else {
						left = Room::Door(false, false);
						}*/
						break;
					case Room::RoomType::EMPTY:
						left = Room::Door(false, false);
						break;
					case Room::RoomType::HALLWAY:
						left = Room::Door(true, false);
						break;
					case Room::RoomType::CHEST:
						left = Room::Door(true, false); // todo locking
						break;
					case Room::RoomType::CENTRAL:
						left = Room::Door(true, false);
						break;
					case Room::RoomType::MYSTIC:
						left = Room::Door(true, false);
						break;
					default:
						break;
				}
			} else {
				Room* rU = &rooms[y][x - 1];
				Room::RoomType rType1 = rU->getRoomType();
				if (rType1 != Room::RoomType::EMPTY) {
					left = Room::Door(true, false);
				}

				Room* rD = &rooms[y][x + 1];
				Room::RoomType rType2 = rD->getRoomType();
				if (rType2 != Room::RoomType::EMPTY) {
					right = Room::Door(true, false);
				}
			}
			// end if

			current->initDoors(up, left, right, down);
		}
	}
	cout << seed;
}
// end of initRooms()

void printRooms() {
	Room* r;
	for (int y = 0; y < Constants::GAME_HEIGHT; y++) {
		for (int x = 0; x < Constants::GAME_WITDH; x++) {
			r = &rooms[y][x];
			cout << "Room:" << endl;
			cout << "\tLocation: x=" << r->getLocation().x << " & y=" << r->getLocation().y << endl;
			cout << "\t\tVariables: x=" << x << " & y=" << y << endl;
			cout << "\tDescription: " << r->getDescription() << endl;
			cout << "\tRoomType: " << static_cast<int>(r->getRoomType()) << endl;
			cout << "\tDoors:" << r->canLeaveFrom(Direction::UP) << r->canLeaveFrom(Direction::LEFT) << r->canLeaveFrom(Direction::RIGHT) << r->canLeaveFrom(Direction::DOWN) << endl;
		}
	}
}

void testCode() {
	// Room r();
}