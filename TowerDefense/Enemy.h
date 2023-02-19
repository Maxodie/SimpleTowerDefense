#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include <stdlib.h>
#include"TileMap.h"

#include"EnemyData.h"

class Enemy {
public:
	Enemy(const float gridSize, sf::Texture* texture, EnemyData* enemyData, std::vector<sf::Vector2f>* wayPoints);
	~Enemy();

	void initSprite();
	void initLifeBar();

	void goToNextPoint();

	void changeSpeed(float percentage, float time);
	void updateSpeedChanges();

	void getReadyToBeDestroy();
	bool getDestroyState();
	bool getIsDropLoot();
	EnemyData* getEnemyData();

	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	void lostHP(float amount);
	void updateGUI();

	sf::Vector2f normilize(const sf::Vector2f& source);
	void checkForNextPoint();
	void update(const float dt);
	void render(sf::RenderTarget& target);

private:
	std::vector<sf::Vector2f>* wayPoints;
	sf::Texture* texture;
	sf::Sprite sprite;

	sf::RectangleShape lifeBarBackground;
	sf::RectangleShape lifeBarFill;

	sf::Vector2f dir;
	EnemyData* enemyData;
	float posId = 0;

	float gridSize;

	float life;
	float speed;
	float speedChangeTime;

	sf::Clock clock;

	bool destroyState = false;
	bool isDroppingLoot = false;
};

