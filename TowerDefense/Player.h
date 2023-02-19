#pragma once
#include"TurretManager.h"
#include"PlayerData.h"
#include <math.h>
#include<iostream>
#include<vector>
#include"PlayerGUI.h"

class Player {
public:
	Player(const float gridSize, std::vector<std::string>* mapData, sf::Font& font);
	~Player();

	PlayerData* getPlayerData();

	void setTurretManager(TurretManager* turretManager);
	bool getDeadState();

	void lostHP(const float amount);
	void die();

	void inputEvent(const sf::Event sfEvent, const sf::Vector2f mousePosView);
	void setActiveTorretPanel(const sf::Vector2f mousePos);

	void render(sf::RenderTarget& target);

private:
	float gridSize;
	std::vector<std::string>* mapData;

	PlayerData* playerData;

	sf::Font* font;
	TurretManager* turretManager = nullptr;

	PlayerGUI* playerGUI;

	float life = 10;

	bool deadState = false;
};