#pragma once
#include<SFML/Graphics.hpp>
#include"TurretData.h"
#include"Enemy.h"

class Turret{
public:
	Turret(const float gridSize, sf::Texture* texture, sf::Vector2f pos, TurretData* turretData, std::vector<Enemy*>* enemies);
	~Turret();

	void chooseTarget();

	double distance(sf::Vector2f v);
	sf::Vector2f getPosition();
	TurretData* getTurretData();

	void shoot();
	void shootEffect();
	void update();

	void initSprite();
	void render(sf::RenderTarget& target);

private:
	sf::Texture* texture = new sf::Texture();
	sf::Sprite sprite;

	sf::Vertex shootLine[2];

	TurretData* turretData;
	std::vector<Enemy*>* enemies;

	Enemy* target = nullptr;
	sf::Clock clock;

	sf::Clock clockEffect;
	float shootEffectTime = 0.2f;
	bool isActivedShoot = false;

	float gridSize;
};

