#include "PlayerData.h"
PlayerData::PlayerData(const float money) {
	playerMoney = money;
}

PlayerData::~PlayerData() {

}

void PlayerData::addMoney(const unsigned int addedMoney) {
	this->playerMoney += addedMoney;
}

bool PlayerData::buy(const unsigned int cost) {
	if (playerMoney >= cost) {
		playerMoney -= cost;
		return true;
	}
	return false;
}

const unsigned int PlayerData::getPlayerMoney() {
	return playerMoney;
}
