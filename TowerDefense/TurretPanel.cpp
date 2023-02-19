#include "TurretPanel.h"

TurretPanel::TurretPanel(const float gridSize, sf::Font& font, PlayerData* playerData, 
	TurretManager* turretManager, std::map<const std::string, TurretData*>* turretsData) {

	this->turretManager = turretManager;
	this->gridSize = gridSize;
	this->font = &font;
	this->playerData = playerData;
	this->turretsData = *turretsData;

	initButtons();
	initPanel();
	initText();

}

TurretPanel::~TurretPanel() {
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
	
	delete font;
	delete turretManager;
}

void TurretPanel::initButtons() {

	buttons["SELECT_BASIC_TURRET"] = new gui::Button(
		13 * gridSize + 52, 260.f, 100.f, 100.f,
		font, "", 35,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50)
	);

	buttons["SELECT_FREEZE_TURRET"] = new gui::Button(
		13 * gridSize + 152, 260.f, 100.f, 100.f,
		font, "", 35,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50)
	);

	buttons["BUY_TURRET"] = new gui::Button(
		13*gridSize+27, 180.f, 250.f, 65.f,
		font, "Buy turret", 45,
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50),
		sf::Color(66, 66, 66), sf::Color(32, 32, 32), sf::Color(20, 20, 20),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50)
	);

	turretManager->setDeleteOrBuyButton(buttons["BUY_TURRET"]);
}

void TurretPanel::initPanel() {
	//The background
	backgroundRectangle = sf::RectangleShape(sf::Vector2f(304, WIN_HEIGHT));
	backgroundRectangle.setPosition(sf::Vector2f(13*gridSize, 0));
	backgroundRectangle.setFillColor(sf::Color(93, 204, 215));

	//the icons
	//Basic Turret
	sf::RectangleShape basicTurretIcon = sf::RectangleShape(sf::Vector2f(100, 100));
	basicTurretIcon.setTextureRect(sf::IntRect(0, 0, 32, 32));
	basicTurretIcon.setTexture(turretManager->getTurretTextures(TurretType::BASIC_TURRET));
	basicTurretIcon.setPosition(13*gridSize+52, 260);

	//Freeze Turrer
	sf::RectangleShape freezeTurretIcon = sf::RectangleShape(sf::Vector2f(100, 100));
	freezeTurretIcon.setTextureRect(sf::IntRect(0, 0, 32, 32));
	freezeTurretIcon.setTexture(turretManager->getTurretTextures(TurretType::FREEZE_TURRET));
	freezeTurretIcon.setPosition(13 * gridSize + 152, 260);

	turretIcons.push_back(basicTurretIcon);
	turretIcons.push_back(freezeTurretIcon);

	backgroundSelectedTurretIcon = sf::RectangleShape(sf::Vector2f(100, 100));
	backgroundSelectedTurretIcon.setFillColor(sf::Color(20, 20, 20, 150));
}

void TurretPanel::initText() {
	playerMoneyText.setFont(*font);
	playerMoneyText.setCharacterSize(40);
	playerMoneyText.setOutlineColor(sf::Color::Black);
	playerMoneyText.setOutlineThickness(1);
	playerMoneyText.setStyle(sf::Text::Bold);
	playerMoneyText.setPosition(13*gridSize + 10, 60);

	infoText.setFont(*font);
	infoText.setCharacterSize(24);
	infoText.setOutlineColor(sf::Color::Black);
	infoText.setOutlineThickness(1);

	//Basic Turret
	std::string turretType_ = turretManager->getTurretTypeStringWithType(TurretType::BASIC_TURRET);
	std::string text = "Basic Turret:\n Price: " + std::to_string((int)turretsData[turretType_]->cost) + "\nDamage: " + std::to_string((int)turretsData[turretType_]->damageAmount) +
		"\nRange: " + std::to_string((int)turretsData[turretType_]->range);

	sf::Text basicTurretIcon = sf::Text(text, *font, 18);
	basicTurretIcon.setPosition(13 * gridSize + 52, 360);

	//Freeze Turrer
	turretType_ = turretManager->getTurretTypeStringWithType(TurretType::FREEZE_TURRET);
	text = "Freeze Turret:\n Price: " + std::to_string((int)turretsData[turretType_]->cost) + "\nDamage: " + std::to_string((int)turretsData[turretType_]->damageAmount) + "\nRange: " +
		std::to_string((int)turretsData[turretType_]->range) + "\nFreeze: -" + std::to_string((int)(turretsData[turretType_]->freezeAmount*100)) + "%";

	sf::Text freezeTurretIcon = sf::Text(text, *font, 18);
	freezeTurretIcon.setPosition(13 * gridSize + 152, 360);

	turretInfoText.push_back(basicTurretIcon);
	turretInfoText.push_back(freezeTurretIcon);

	updateTexts();
}

PanelButtonInstructions TurretPanel::getButtonPressed() {
	//Select turret
	if (buttons["SELECT_BASIC_TURRET"]->isPressed())
		return PanelButtonInstructions::SELECT_BASIC_TURRET;

	if (buttons["SELECT_FREEZE_TURRET"]->isPressed())
		return PanelButtonInstructions::SELECT_FREEZE_TURRET;

	//Confirm
	if (buttons["BUY_TURRET"]->isPressed())
		return PanelButtonInstructions::BUY_TURRET;

	return PanelButtonInstructions::NOTHING;
}

void TurretPanel::updateButtons(sf::Vector2f mousePos) {
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		it->second->update(mousePos);
	}
}

void TurretPanel::updateTexts() {
	playerMoneyText.setString("Money: " + std::to_string(playerData->getPlayerMoney()));
}

void TurretPanel::changeInfoText(std::string info, sf::Color color) {
	infoText.setFillColor(color);
	infoText.setString(info);
	//Recenter
	infoText.setPosition(13 * gridSize + (WIN_WIDTH - 13 * gridSize) / 2 - infoText.getGlobalBounds().width / 2, 5);
}

void TurretPanel::changeSelectedTurret(TurretType type) {
	switch (type) {
	case TurretType::BASIC_TURRET:
		backgroundSelectedTurretIcon.setPosition(sf::Vector2f(13 * gridSize + 52, 260));
		break;
	case TurretType::FREEZE_TURRET:
		backgroundSelectedTurretIcon.setPosition(sf::Vector2f(13 * gridSize + 152, 260));
		break;
	default:
		break;
	}
}

void TurretPanel::render(sf::RenderTarget& target) {
	target.draw(backgroundRectangle);

	target.draw(backgroundSelectedTurretIcon);

	for (auto& it : turretIcons) {
		target.draw(it);
	}

	for (auto& it : turretInfoText) {
		target.draw(it);
	}

	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		it->second->render(target);
	}

	target.draw(playerMoneyText);
	target.draw(infoText);
}
