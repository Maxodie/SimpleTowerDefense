#include "EnemyManager.h"

EnemyManager::EnemyManager(const float gridSize, Player* player, std::vector<sf::Vector2f>* wayPoints) {
	this->gridSize = gridSize;
	this->player = player;
	this->wayPoints = wayPoints;

	increaseEnemiesNumberClock.restart();

	srand(time(0));
	clock.restart();

	initTexture();
	initSpawnableEnemies();
}

EnemyManager::~EnemyManager() {
	delete wayPoints;

	for (auto& it : enemies) {
		delete it;
	}

	for (auto& it : enemiesTextures) {
		delete it.second;
	}

	for (auto& it : spawnableEnemies) {
		delete it.second;
	}

	delete player;
}

std::vector<Enemy*>* EnemyManager::getEnemies() {
	return &enemies;
}

void EnemyManager::initTexture() {
	enemiesTextures[getEnemyTypeStringWithType(EnemyType::BASIC_ENEMY)] = new sf::Texture();
	if (!enemiesTextures[getEnemyTypeStringWithType(EnemyType::BASIC_ENEMY)]->loadFromFile("Sprites/Enemy_01.png"))
		std::cout << "ENEMYMANAGER.CPP::ERROR::CANT_LOAD_BASIC_ENEMY_TEXTURE" << std::endl;

	enemiesTextures[getEnemyTypeStringWithType(EnemyType::FAST_ENEMY)] = new sf::Texture();
	if (!enemiesTextures[getEnemyTypeStringWithType(EnemyType::FAST_ENEMY)]->loadFromFile("Sprites/Enemy_02.png"))
		std::cout << "ENEMYMANAGER.CPP::ERROR::CANT_LOAD_FAST_ENEMY_TEXTURE" << std::endl;

	enemiesTextures[getEnemyTypeStringWithType(EnemyType::TANKY_ENEMY)] = new sf::Texture();
	if (!enemiesTextures[getEnemyTypeStringWithType(EnemyType::TANKY_ENEMY)]->loadFromFile("Sprites/Enemy_03.png"))
		std::cout << "ENEMYMANAGER.CPP::ERROR::CANT_LOAD_TANKY_ENEMY_TEXTURE" << std::endl;

	enemiesTextures[getEnemyTypeStringWithType(EnemyType::BOSS_ENEMY)] = new sf::Texture();
	if (!enemiesTextures[getEnemyTypeStringWithType(EnemyType::BOSS_ENEMY)]->loadFromFile("Sprites/Enemy_04.png"))
		std::cout << "ENEMYMANAGER.CPP::ERROR::CANT_LOAD_BOSS_ENEMY_TEXTURE" << std::endl;
}

std::string EnemyManager::getEnemyTypeStringWithType(const EnemyType type) {
	switch (type) {
	case EnemyType::BASIC_ENEMY:
		return "BASIC_ENEMY";
		break;
	case EnemyType::FAST_ENEMY:
		return "FAST_ENEMY";
		break;
	case EnemyType::TANKY_ENEMY:
		return "TANKY_ENEMY";
		break;
	default:
		return "";
		break;
	}
}

void EnemyManager::onEnemyDestroyed(unsigned int id) {
	if (enemies[id]->getDestroyState()) {
		if (enemies[id]->getIsDropLoot()) {
			player->getPlayerData()->addMoney(enemies[id]->getEnemyData()->moneyDropped);
			turretPanel->updateTexts();
		}
		else
			playerDamage(enemies[id]->getEnemyData());

		enemies.erase(enemies.begin() + id);
	}
}

void EnemyManager::initSpawnableEnemies() {
	EnemyData basicEnemy = EnemyData();
	spawnableEnemies[getEnemyTypeStringWithType(EnemyType::BASIC_ENEMY)] = new EnemyData(basicEnemy);

	basicEnemy.life = 15;
	basicEnemy.speed = 50;
	spawnableEnemies[getEnemyTypeStringWithType(EnemyType::FAST_ENEMY)] = new EnemyData(basicEnemy);

	basicEnemy.life = 60;
	basicEnemy.speed = 20;
	basicEnemy.damage = 2;
	basicEnemy.moneyDropped = 70;
	spawnableEnemies[getEnemyTypeStringWithType(EnemyType::TANKY_ENEMY)] = new EnemyData(basicEnemy);

	basicEnemy.life = 150;
	basicEnemy.speed = 25;
	basicEnemy.damage = 3;
	basicEnemy.moneyDropped = 100;
	spawnableEnemies[getEnemyTypeStringWithType(EnemyType::BOSS_ENEMY)] = new EnemyData(basicEnemy);
}

void EnemyManager::setTurretPanel(TurretPanel* turretPanel) {
	this->turretPanel = turretPanel;
}

void EnemyManager::spawnEnemy(const EnemyType type) {
	enemies.push_back(new Enemy(gridSize, enemiesTextures[getEnemyTypeStringWithType(type)], 
		spawnableEnemies[getEnemyTypeStringWithType(type)], wayPoints));

	spawnableEnemies[getEnemyTypeStringWithType(type)]->life += .5f;
	spawnableEnemies[getEnemyTypeStringWithType(type)]->speed += .1f;
}

void EnemyManager::spawner() {
	if (maxEnemiesNumber < spawnableEnemies.size() && increaseEnemiesNumberClock.getElapsedTime().asSeconds() >= increaseEnemiesNumberTime) {
		increaseEnemiesNumberClock.restart();
		increaseEnemiesNumberTime *= 2;
		maxEnemiesNumber += 1;
	}

	if (clock.getElapsedTime().asSeconds() >= timeBetweenSpawn) {
		if(timeBetweenSpawn > .1f)
			timeBetweenSpawn *= timeBetweenSpawnDiminutionMultiplicator;

		int randomTypeId = rand() % maxEnemiesNumber;
		switch (randomTypeId) {
		case 0:
			spawnEnemy(EnemyType::BASIC_ENEMY);

			break;
		case 1:
			spawnEnemy(EnemyType::FAST_ENEMY);
			break;
		case 2:
			spawnEnemy(EnemyType::TANKY_ENEMY);
			break;
		case 3:
			spawnEnemy(EnemyType::BOSS_ENEMY);
			break;
		default:
			spawnEnemy(EnemyType::BASIC_ENEMY);
			break;
		}
		
		clock.restart();
	}
}

void EnemyManager::playerDamage(EnemyData* enemyData) {
	player->lostHP(enemyData->damage);//mettre lostHP dans PlayerData et faire reférence à player data au lieu de player
}

void EnemyManager::update(const float dt) {
	spawner();

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(dt);

		onEnemyDestroyed(i);
	}
}

void EnemyManager::render(sf::RenderTarget& target) {
	for (int i = enemies.size() - 1; i >= 0; i--) {
		enemies[i]->render(target);
	}
}
