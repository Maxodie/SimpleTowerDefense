#include "Player.h"

Player::Player(const float gridSize, std::vector<std::string>* mapData, sf::Font& font) {
	this->gridSize = gridSize;
	this->mapData = mapData;
	this->font = &font;
	this->playerData = new PlayerData(1000);
	this->playerGUI = new PlayerGUI(gridSize, &font, life);
	this->turretManager = nullptr;
}

Player::~Player() {
	delete turretManager;
	delete font;
	delete mapData;
	delete playerData;
}

PlayerData* Player::getPlayerData() {
	return playerData;
}

void Player::setTurretManager(TurretManager* turretManager) {
	this->turretManager = turretManager;
}

bool Player::getDeadState() {
	return deadState;
}

void Player::lostHP(const float amount) {
	life -= amount;
	if (life <= 0) {
		life = 0;
		die();
	}

	playerGUI->updateLifeBar(life);
}

void Player::die() {
	deadState = true;
}

void Player::inputEvent(const sf::Event sfEvent, const sf::Vector2f mousePosView) {
	if (sfEvent.type == sf::Event::MouseButtonPressed) {
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			setActiveTorretPanel(mousePosView);
	}
}

void Player::setActiveTorretPanel(const sf::Vector2f mousePos) {
	if (turretManager == nullptr) return;

	const sf::Vector2f gridPos = sf::Vector2f(floor(mousePos.x / gridSize), floor(mousePos.y / gridSize));

	const std::vector<std::string> mapData_ = *mapData;

	if (gridPos.y < mapData_.size() && gridPos.x < mapData_[gridPos.y].size()) {
		if (mapData_[gridPos.y][gridPos.x] != '1') {
			turretManager->changePosition(gridPos);
			turretManager->setActiveSelectedPos(true);
		}
		else
			turretManager->setActiveSelectedPos(false);
	}
		
}

void Player::render(sf::RenderTarget& target) {
	playerGUI->render(target);
}
