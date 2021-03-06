#include "Player.h"
#include "Driection.h"
#include "Constants.h"
#include "Enemy.h"
#include <iostream>

Player::Player(Room* currentRoom, int& x, int& y)
	:
	current(currentRoom) {
	this->loc = { x, y };
}

void Player::update() {
	// pre turn var reset /Check
	moved = false;
	if (current->hasEnemy() && !current->getEnemy().isDead() && state != State::FIGHTING) {
		state = State::FIGHTING;
		std::cout << "You have encountered an enemy!\nPrepare to Fight!\n" << std::endl;
	}
	// end

	if (state == State::EXPLORING) {
		while (!printMajorChoices()) {
			if (!run) { return; }
		}
		
	} else if (state == State::FIGHTING) {
		// process turn
		this->processPlayerTrun();
		// end

		// after turn processing
		if (!current->getEnemy().isDead()) {
			this->processEnemyResponse();
		}

		if (specialCounter > 0) {
			specialCounter--;
		}
		// end
	}
}

bool Player::printMajorChoices() {
	using namespace std;
	cout << endl << "What would you like to do?" << endl;
	cout << "1. Explore currently occupied room." << endl; // TODO change this from explore current room to current room actions or something
	cout << "2. Move to another room." << endl;
	cout << "3. Inventory Options." << endl;
	cout << "4. View Player Stats." << endl;
	cout << "5. Exit game." << endl;

	int choice;
	cin >> choice;
	switch (choice) {
		case -1:
			doCheatLoop();
			return false;
		case 1:
			printRoomChoices();
			return true;
		case 2:
			printMoveChoices();
			return true;
		case 3:
			printInventoryChoices();
			return true;
		case 4:
			printPlayerStats();
			return true;
		case 5:
			cout << "Are you sure you wish to exit? (Y/N): ";
			char choice;
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				this->run = false;
			} else {
				cout << "Heh, that's what I thought." << endl << endl;
			}
			return true;
		default:
			cout << "That is not an available choice, please try again." << endl;
			return false;
	}
}

void Player::doCheatLoop() {
	using namespace std;
	char c = 0;
	cin >> c;
	switch (c) {
		case 'g':
			give();
			break;
		default:
			break;
	}
}

void Player::give() {
	using namespace std;
	int i = 0;
	cin >> i;
	Item::ItemType t = static_cast<Item::ItemType>(i);
	cin >> i;
	float f = 0;
	cin >> f;
	items.push_back(Item(t, "CHEATED ITEM", i, f));
}

void Player::printMoveChoices() {
	using namespace std;
	bool valid = false;
	while (!valid) {
		cout << "Where would you like to go?" << endl;
		for (int i = 0; i < 4; i++) {
			Direction val = static_cast<Direction>(i);
			if (current->canLeaveFrom(val)) {
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
		
		if (current->canLeaveFrom(val)) {
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
		} else {
			cout << "Sorry, invalid input. Please try again." << endl;
			valid = false;
		}

		if (valid) {
			cout << "You have entered a new room." << endl;
			cout << "Location: x=" << loc.x << " y=" << loc.y << endl;
			moved = true;
		}
	}
}

// EVENTUALLY TERE WILL BE SOME CHOICES SPECIFIC TO SOME ROOMS
void Player::printRoomChoices() {
	using namespace std;
	cout << "You explore your current room." << endl;
	cout << current->getDescription() << endl;
	if (current->hasLootableChest()) {
		if (current->numLootableChests() == 1) {
			cout << "There is " << current->numLootableChests() << " lootable chest in this room." << endl;
		} else {
			cout << "There are " << current->numLootableChests() << " lootable chests in this room." << endl;
		}
	} else {
		cout << "There are no lootable chests in this room." << endl;
	}
	cout << "Location: x=" << loc.x << " y=" << loc.y << endl;
	if (Constants::DEBUG_MODE) { // DEBUG CODE FOR ME
		cout << static_cast<int>(current->getRoomType()) << endl;
	}

	if (current->hasLootableChest()) {
		cout << "Loot 1 chest in this room?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		
		int c = 0;
		cin >> c;
		switch (c) {
			case 1:
				items.push_back(current->lootChest());
				cout << "Looted one chest." << endl;
				if (current->hasLootableChest()) {
					if (current->numLootableChests() == 1) {
						cout << "There is now " << current->numLootableChests() << " lootable chest in this room." << endl;
					} else {
						cout << "There are now " << current->numLootableChests() << " lootable chests in this room." << endl;
					}
				} else {
					cout << "There are no lootable chests in this room." << endl;
				}
				break;
			case 2:
				cout << "No chests were looted." << endl;
				break;
			default:
				break;
		}
	} else {

	}
}

void Player::printPlayerStats() {
	using namespace std;
	cout << "Printing Player Stats:" << endl;
	cout << "Location: x=" << loc.x << " y=" << loc.y << endl;
	cout << "Health=" << health << endl;
	cout << "DamageMod=" << damageMod << endl;

}

bool Player::printInventoryChoices() {
	using namespace std;
	bool done = false;
	bool didAction = false;
	while (!done) {
		cout << endl << "Which inventory action would you like to perform?" << endl;
		cout << "1. View inventory." << endl;
		cout << "2. Use/Equip Item." << endl;
		cout << "3. Discard Item." << endl;
		cout << "4. Leave Inventory." << endl;
		
		int choice = 0;
		cin >> choice;
		switch (choice) {
			case 1:
				printInventory();
				break;
			case 2:
				cout << "Which item would you like to Use/Equip? (Select by number): " << endl;
				printInventory();
				cin >> choice;
				if (choice >= 0 && choice < items.size()) {
					vector<Item>::iterator it = items.begin() + choice;
					Item& i = *it;
					switch (i.getType()) {
						case Item::ItemType::EMPTY:
							break;
						case Item::ItemType::HEALING:
							health += i.getEffect();
							items.erase(it);
							didAction = true;
							if (this->state == State::FIGHTING) {
								done = true;
							}
							break;
						case Item::ItemType::WEAPON:
							if (hasItemEquipped) {
								cout << "There is already an equipped item. Would you like to unequip it? (Y/N)" << endl;
								char c;
								cin >> c;
								if (c == 'Y' || c == 'y') {
									cout << "Unequipping item..." << endl;
									damageMod = BASE_DAMAGE_MOD;
									equippedItemIndex = -1;
									hasItemEquipped = false;
									cout << "Item upequipped." << endl;
								} else {
									cout << "The Item will not be unequipped." << endl;
									break;
								}
							}
							cout << "Equipping item..." << endl;
							damageMod = BASE_DAMAGE_MOD + i.getMultiplier();
							equippedItemIndex = choice;
							hasItemEquipped = true;
							cout << "Item equipped." << endl;
							didAction = true;

							if (this->state == State::FIGHTING) {
								done = true;
							}
							break;
						case Item::ItemType::INSTANT_DAMAGE:
							if (this->state == State::EXPLORING) {
								cout << "Unable to use selceted item at this time.";
							} else {
								current->getEnemy().damage(i.getEffect());
								done = true;
								didAction = true;
							}
							break;
						default:
							break;
					}
				} else {
					cout << "Invalid index." << endl;
				}
				break;
			case 3:
				cout << "Which item would you like to discard? (Select by number): " << endl;
				printInventory();
				cin >> choice;
				if (choice >= 0 && choice < items.size()) {
					vector<Item>::iterator it = items.begin() + choice;
					if (hasItemEquipped && choice == equippedItemIndex) {
						cout << "The selected item is equipped." << endl;
						cout << "Are you sure you wish to unequip and discard the following item? (Y/N)" << endl;
						printItem(it);
						char c;
						cin >> c;
						if (c == 'Y' || c == 'y') {
							cout << "Discarding item..." << endl;
							hasItemEquipped = false;
							damageMod = BASE_DAMAGE_MOD;
							int s = items.size();
							items.erase(it);
							if (s - 1 == items.size()) {
								cout << "Item Sucessfully discarded." << endl;
								didAction = true;
							}
						} else {
							cout << "The Item will not be discarded." << endl;
						}
					} else {
						cout << "Are you sure you wish to discard the following item? (Y/N)" << endl;
						printItem(it);
						char c;
						cin >> c;
						if (c == 'Y' || c == 'y') {
							cout << "Discarding item..." << endl;
							int s = items.size();
							items.erase(it);
							if (s - 1 == items.size()) {
								cout << "Item Sucessfully discarded." << endl;
								didAction = true;
							}
						} else {
							cout << "The Item will not be discarded." << endl;
						}
					}
				} else {
					cout << "Invalid index. Please try again." << endl;
				}
				break;
			case 4:
				done = true;
				break;
			default:
				break;
		}
	}
	return didAction;
}

void Player::processPlayerTrun() {
	std::uniform_int_distribution<int> pDist = std::uniform_int_distribution<int>(3, 6);
	std::uniform_int_distribution<int> kDist = std::uniform_int_distribution<int>(5, 10);
	std::uniform_int_distribution<int> sDist = std::uniform_int_distribution<int>(9, 14);
	using namespace std;
	cout << endl << "Your Health: " << health << endl;
	cout << "Enemy Health:" << current->getEnemy().getHealth() << " \tEnemy type: " << current->getEnemyName() << endl;
	cout << "Moves:\t1. Punch " << (int)(damageMod * pDist.min()) << "-" << (int)(damageMod * pDist.max()) << "\t2. Kick " << (int)(damageMod * kDist.min()) << "-" << (int)(damageMod * kDist.max());
	cout << "\t3. Special " << (int)(damageMod * sDist.min()) << "-" << (int)(damageMod * sDist.max()) << endl;
	cout << "Other Options:\t4. Inventory \t5. Run Away" << endl;
	bool good = false;
	while (!good) {
		int choice;
		cin >> choice;
		switch (choice) {
			case -1:
				doCheatLoop();
				break;
			case 1: {
				int damage = pDist(Constants::combactRng);
				int newDamage = (int)(damage * damageMod);
				current->getEnemy().damage(newDamage);
				cout << "Punch did " << newDamage << " damage." << endl;
				good = true;
				break;
			}
			case 2: {
				int damage = kDist(Constants::combactRng);
				int newDamage = (int)(damage * damageMod);
				current->getEnemy().damage(newDamage);
				cout << "Kick did " << newDamage << " damage." << endl;
				good = true;
				break;
			}
			case 3: {
				if (specialCounter == 0) {
					int damage = sDist(Constants::combactRng);
					int newDamage = (int)(damage * damageMod);
					current->getEnemy().damage(newDamage);
					cout << "Special did " << newDamage << " damage." << endl;
					good = true;
					break;
				} else {
					cout << "Sorry, this move is on cooldown. Please wait " << specialCounter << " turns." << endl;
				}
			}
			case 4:
				good = printInventoryChoices();
				break;
			case 5: {
				std::uniform_int_distribution<int> chance = std::uniform_int_distribution<int>(1, 5);
				if (chance(Constants::combactRng) != 3) {
					bool valid = false;
					while (!valid) {
						cout << "Where would you like to run to?" << endl;
						for (int i = 0; i < 4; i++) {
							Direction val = static_cast<Direction>(i);
							if (current->canLeaveFrom(val)) {
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

						if (current->canLeaveFrom(val)) {
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
							this->state = State::EXPLORING;
							cout << "Got away successfully." << endl;
						} else {
							cout << "Sorry, invalid input. Please try again." << endl;
							valid = false;
						}
					}
				} else {
					cout << "Did not get away!" << endl;
				}
				good = true;
				break;
			}
			default:
				cout << "Sorry, invalid input. Please try again." << endl;
				good = false;
				break;
		}
	}
	if (current->getEnemy().isDead()) {
		cout << "You survived." << endl;
		this->state = State::EXPLORING;
	}
}

void Player::processEnemyResponse() {
	int damage = current->getEnemy().getDamageFromAttack();
	this->health -= damage;
	std::cout << "Enemy did " << damage << " damage" << std::endl;
}

bool Player::movedLastUpdate() {
	return moved;
}

Location Player::getLocation() const {
	return loc;
}

void Player::setCurrentRoom(Room* r) {
	current = r;
}

void Player::printInventory() {
	using namespace std;
	cout << endl << "Showing Inventory." << endl;
	int n = 0;
	for (vector<Item>::iterator i = items.begin(); i != items.end(); ++i, ++n) {
		Item& item = *i;
		if (n == equippedItemIndex) {
			cout << "EQUIPPED Item" << n << ": Type=" << item.getTypeAsString() << " Description=" << item.getDescription() << ((item.isNegativeItem()) ? " Damage=" : " HealthRestore=") << item.getEffect() << ((item.isNegativeItem()) ? " DamageMultiplier=" : " Mult=") << item.getMultiplier() << endl;
		} else {
			cout << "Item" << n << ": Type=" << item.getTypeAsString() << " Description=" << item.getDescription() << ((item.isNegativeItem()) ? " Damage="  : " HealthRestore=") << item.getEffect() << ((item.isNegativeItem()) ? " DamageMultiplier=" : " Mult=") << item.getMultiplier() << endl;
		}
	}
}

void Player::printItem(std::vector<Item>::iterator it) {
	using namespace std;
	Item& item = *it;
	cout << "Item: Type=" << item.getTypeAsString() << " Description=" << item.getDescription() << ((item.isNegativeItem()) ? " Damage=" : " HealthRestore=") << item.getEffect() << ((item.isNegativeItem()) ? " DamageMultiplier=" : " Mult=") << item.getMultiplier() << endl;
}