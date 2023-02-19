#pragma once
#include"EnemyData.h"
#include"EnemyType.h"
#include"Enemy.h"
#include<SFML/Graphics.hpp>
#include<map>
#include<string>
#include<iostream>
#include"Player.h"
#include <ctime>
#include"TurretPanel.h"

class EnemyManager {
public:
	EnemyManager(const float gridSize, Player* player, std::vector<sf::Vector2f>* wayPoints);
	~EnemyManager();

	std::vector<Enemy*>* getEnemies();

	void initSpawnableEnemies();

	void setTurretPanel(TurretPanel* turretPanel);

	void spawnEnemy(const EnemyType type);
	void spawner();

	void playerDamage(EnemyData* enemyData);

	void initTexture();
	std::string getEnemyTypeStringWithType(const EnemyType type);

	void onEnemyDestroyed(unsigned int id);

	void update(const float dt);
	void render(sf::RenderTarget& target);

private:
	Player* player;
	TurretPanel* turretPanel;

	std::vector<sf::Vector2f>* wayPoints;
	std::map<const std::string, sf::Texture*> enemiesTextures;
	std::vector<Enemy*> enemies;

	std::map<const std::string, EnemyData*> spawnableEnemies;

	sf::Clock clock;
	float timeBetweenSpawn = 3;
	float timeBetweenSpawnDiminutionMultiplicator = .99f;

	sf::Clock increaseEnemiesNumberClock;
	float increaseEnemiesNumberTime = 120.f;
	unsigned int maxEnemiesNumber = 2;

	float gridSize;
};

