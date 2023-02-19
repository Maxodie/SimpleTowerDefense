#include "TurretShop.h"

TurretShop::TurretShop(const float gridSize, sf::Font& font, TurretManager* turretManager, PlayerData* playerData) {
	this->turretManager = turretManager;
	initBuyableTurrets();
	this->turretPanel = new TurretPanel(gridSize, font, playerData, turretManager, &buyableTurrets);
	this->playerData = playerData;
	changeSelectedTurret(TurretType::BASIC_TURRET);
}

TurretShop::~TurretShop() {
	delete turretPanel;
}

void TurretShop::initBuyableTurrets() {
	TurretData basicTurretData = TurretData();
	buyableTurrets[turretManager->getTurretTypeStringWithType(TurretType::BASIC_TURRET)] = new TurretData(basicTurretData);

	basicTurretData.damageAmount = 2.f;
	basicTurretData.range = 4.f;
	basicTurretData.freezeAmount = .8f;
	basicTurretData.cost = 500.f;
	basicTurretData.fireRate = 2.f;
	basicTurretData.sellPrice = 250.f;
	basicTurretData.type = TurretType::FREEZE_TURRET;
	buyableTurrets[turretManager->getTurretTypeStringWithType(TurretType::FREEZE_TURRET)] = new TurretData(basicTurretData);
}

void TurretShop::buyTurret() {
	if (turretManager->canBuildTurret()) {
		if (playerData->buy(buyableTurrets[turretManager->getTurretTypeStringWithType(selectedTurret)]->cost)) {
			turretManager->createTurret(selectedTurret, buyableTurrets[turretManager->getTurretTypeStringWithType(selectedTurret)]);
			turretPanel->changeInfoText("Turret bought", sf::Color::Green);
			turretPanel->updateTexts();
		}
		else
			turretPanel->changeInfoText("Not enough money\n to buy this turret", sf::Color::Red);
	}
	else
		turretPanel->changeInfoText("No location chosen or\n turret already present", sf::Color::Red);
}

void TurretShop::deleteTurret() {
	if (turretManager->getSelectedTurretData() != nullptr) {
		playerData->addMoney(turretManager->getSelectedTurretData()->sellPrice);
		turretManager->deleteSelectedTurret();
		turretPanel->updateTexts();
	}
}

void TurretShop::changeSelectedTurret(TurretType type) {
	selectedTurret = type;
	turretPanel->changeSelectedTurret(type);
}

TurretPanel* TurretShop::getTurretPanel() {
	return turretPanel;
}

void TurretShop::update(const sf::Vector2f mousePos) {
	turretPanel->updateButtons(mousePos);
	PanelButtonInstructions result = turretPanel->getButtonPressed();

	//Turret selector
	if (result == PanelButtonInstructions::SELECT_BASIC_TURRET)
		changeSelectedTurret(TurretType::BASIC_TURRET);

	if (result == PanelButtonInstructions::SELECT_FREEZE_TURRET)
		changeSelectedTurret(TurretType::FREEZE_TURRET);

	//Confirm 
	if (result == PanelButtonInstructions::BUY_TURRET) {
		if (turretManager->getIsBuyMode())
			buyTurret();
		else
			deleteTurret();
	}
}

void TurretShop::render(sf::RenderTarget& target) {
	turretPanel->render(target);
}