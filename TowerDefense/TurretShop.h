#pragma once
#include"TurretPanel.h"
#include<map>
#include"TurretData.h"


class TurretShop {
public:
	TurretShop(const float gridSize, sf::Font& font, TurretManager* turretManager, PlayerData* playerData);
	~TurretShop();

	void initBuyableTurrets();

	void buyTurret();
	void deleteTurret();
	void changeSelectedTurret(TurretType type);

	TurretPanel* getTurretPanel();

	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);

private:
	std::map<const std::string, TurretData*> buyableTurrets;

	TurretPanel* turretPanel;
	TurretManager* turretManager;

	TurretType selectedTurret;

	PlayerData* playerData;
};

