#pragma once
#include"TileMap.h"
#include"EnemyManager.h"
#include"Player.h"
#include"TurretShop.h"
#include"EndState.h"

class GameState : public State {
public:
	GameState(sf::RenderWindow* window_, const float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem, std::vector<std::string>* mapData,
		std::vector<sf::Vector2f>* wayPoints, int mapId);
	~GameState();

	void initButtons();
	void initText();

	void event(sf::Event sfEvent);
	void update(const float dt);
	void updateButtons();
	void render();

private:
	int mapId;
	std::map<std::string, gui::Button*>  buttons;
	TileMap* tileMap;

	sf::Clock gameTimer;
	sf::Text timerText;

	EnemyManager* enemyManager;
	Player* player;
	TurretManager* turretManager;
	TurretShop* turretShop;
};