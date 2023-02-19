#include"TurretManager.h"

TurretManager::TurretManager(const float gridSize, std::vector<Enemy*>* enemies) {
	this->gridSize = gridSize;
	this->enemies = enemies;
	
	initGraphics();
	initTextures();
}

TurretManager::~TurretManager() {
	delete selectedPos;
	delete rectangleSelectedPos;
	delete enemies;
	delete deleteOrBuyButton;
	delete selectedTurret;

	for (size_t i = 0; i < turretsInfo.size();) {
		delete turretsInfo[turretsInfo.size()-1];
		turretsInfo.pop_back();
	}

	for (auto it = turretTextures.begin(); it != turretTextures.end(); it++) {
		delete it->second;
	}
}

const sf::Texture* TurretManager::getTurretTextures(TurretType type) {
	return turretTextures[getTurretTypeStringWithType(type)];
}

void TurretManager::initGraphics() {
	//The selected rectangle
	rectangleSelectedPos = new sf::RectangleShape(sf::Vector2f(gridSize, gridSize));
	rectangleSelectedPos->setFillColor(sf::Color(67, 148, 156, 200));
}

void TurretManager::initTextures() {
	turretTextures[getTurretTypeStringWithType(TurretType::BASIC_TURRET)] = new sf::Texture();
	if (!turretTextures[getTurretTypeStringWithType(TurretType::BASIC_TURRET)]->loadFromFile("Sprites/turret_01.png"))
		std::cout << "ERROR::TURRETMANAGER::CANT_LOAD_BASIC_TURRET_TEXTURE" << std::endl;

	turretTextures[getTurretTypeStringWithType(TurretType::FREEZE_TURRET)] = new sf::Texture();
	if (!turretTextures[getTurretTypeStringWithType(TurretType::FREEZE_TURRET)]->loadFromFile("Sprites/turret_02.png"))
		std::cout << "ERROR::TURRETMANAGER::CANT_LOAD_FREEZE_TURRET_TEXTURE" << std::endl;
}

void TurretManager::setDeleteOrBuyButton(gui::Button* button) {
	deleteOrBuyButton = button;
}

void TurretManager::setActiveSelectedPos(bool state) {
	activeState = state;
	if (!state) {
		delete selectedPos;
		selectedPos = nullptr;
	}
}

void TurretManager::changePosition(const sf::Vector2f selectedPos) {
	this->selectedPos = new sf::Vector2f(selectedPos);
	rectangleSelectedPos->setPosition(selectedPos * gridSize);

	if (selectTurret()) {
		rectangleSelectedPos->setFillColor(sf::Color(156, 67, 67, 200));
		ChangeMode(true);
	}
	else {
		rectangleSelectedPos->setFillColor(sf::Color(67, 148, 156, 200));
		ChangeMode(false);
	}
}

void TurretManager::ChangeMode(bool isDeleteMode) {
	this->isDeleteMode = isDeleteMode;
	if (isDeleteMode) {
		deleteOrBuyButton->setText("Sell for: " + std::to_string((int)selectedTurret->turret->getTurretData()->sellPrice));
	}
	else {
		selectedTurret = nullptr;
		deleteOrBuyButton->setText("Buy turret");
	}
}

bool TurretManager::getIsBuyMode() {
	return !isDeleteMode;
}

TurretData* TurretManager::getSelectedTurretData() {
	return selectedTurret->turret->getTurretData();
}

bool TurretManager::selectTurret() {
	for (size_t i = 0; i < turretsInfo.size(); i++) {
		if (turretsInfo[i]->pos == *selectedPos) {
			selectedTurret = turretsInfo[i];
			return true;
		}
	}
	return false;
}

bool TurretManager::canBuildTurret() {
	if (selectedPos == nullptr) return false;

	return !selectTurret();
}

std::string TurretManager::getTurretTypeStringWithType(TurretType type) {
	switch (type) {
	case TurretType::BASIC_TURRET:
		return "BASIC_TURRET";
		break;
	case TurretType::FREEZE_TURRET:
		return "FREEZE_TURRET";
		break;
	default:
		return "";
		break;
	}
}

void TurretManager::createTurret(TurretType type, TurretData* turretData) {
	TurretPosInfo* turretInfo = new TurretPosInfo();
	turretInfo->turret = new Turret(gridSize, turretTextures[getTurretTypeStringWithType(type)], *selectedPos, turretData, enemies);
	turretInfo->pos = *selectedPos;
	turretsInfo.push_back(turretInfo);

	setActiveSelectedPos(false);
}

void TurretManager::deleteSelectedTurret() {
	for (size_t i = 0; i < turretsInfo.size(); i++) {
		if (turretsInfo[i]->pos == *selectedPos) {
			turretsInfo.erase(turretsInfo.begin() + i);
			delete selectedTurret;
			selectedTurret = nullptr;

			setActiveSelectedPos(false);

			break;
		}
	}
}

void TurretManager::update() {
	for (auto& it : turretsInfo) {
		it->turret->update();
	}
}

void TurretManager::render(sf::RenderTarget& target) {
	for (size_t i = 0; i < turretsInfo.size(); i++) {
		turretsInfo[i]->turret->render(target);
	}

	if (activeState)
		target.draw(*rectangleSelectedPos);
}
