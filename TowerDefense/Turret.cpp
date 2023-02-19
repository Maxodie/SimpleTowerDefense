#include "Turret.h"

Turret::Turret(const float gridSize, sf::Texture* texture, sf::Vector2f pos, TurretData* turretData, std::vector<Enemy*>* enemies) {
	this->texture = texture;
	this->gridSize = gridSize;
	this->turretData = turretData;
	this->enemies = enemies;
	this->target = nullptr;
	initSprite();

	sprite.setPosition(pos*gridSize);
}

Turret::~Turret() {
	delete texture;
	delete turretData;
	delete enemies;
}

void Turret::chooseTarget() {
	//the enemy distance needs to be less than the range+1
	float minDistance = turretData->range+1;
	float currentDistance = .0f;

	for (int i = 0; i < enemies->size(); i++) {
		currentDistance = distance(enemies->at(i)->getPosition() - getPosition())/gridSize;
		if (currentDistance <= turretData->range && currentDistance < minDistance) {
			minDistance = currentDistance;
			target = enemies->at(i);
			clock.restart();
		}
	}
}

double Turret::distance(sf::Vector2f v) {
	return std::sqrt(v.x*v.x+v.y*v.y);
}

sf::Vector2f Turret::getPosition() {
	return sprite.getPosition();
}

TurretData* Turret::getTurretData() {
	return turretData;
}

void Turret::shoot() {
	if (clock.getElapsedTime().asSeconds() >= turretData->fireRate) {
		target->lostHP(turretData->damageAmount);
		clock.restart();

		if (turretData->type == TurretType::FREEZE_TURRET) {
			target->changeSpeed(turretData->freezeAmount, turretData->fireRate);
		}

		shootEffect();
	}
}

void Turret::shootEffect() {
	shootLine[0].position = sf::Vector2f(getPosition().x + sprite.getGlobalBounds().width / 2, getPosition().y + sprite.getGlobalBounds().height / 2);
	shootLine[1].position = sf::Vector2f(target->getPosition().x + target->getSize().x / 2, target->getPosition().y + target->getSize().y / 2);
	clockEffect.restart();
	isActivedShoot = true;
}

void Turret::update() {
	if (target == nullptr) {
		chooseTarget();
	}
	else {
		if (distance(target->getPosition() - getPosition())/gridSize > turretData->range || target->getDestroyState())
			target = nullptr;
		else
			shoot();
	}

	if (isActivedShoot && clockEffect.getElapsedTime().asSeconds() >= shootEffectTime)
		isActivedShoot = false;
}

void Turret::initSprite() {
	sprite = sf::Sprite(*texture, sf::IntRect(0, 0, 32, 32));
	sprite.setScale(gridSize / 32, gridSize / 32);

	shootLine[0] = sf::Vertex(sf::Vector2f(10, 3), sf::Color::Red);
	shootLine[1] = sf::Vertex(sf::Vector2f(20, 3), sf::Color::Red);
}

void Turret::render(sf::RenderTarget& target) {
	target.draw(sprite);

	if (isActivedShoot)
		target.draw(shootLine, 2, sf::Lines);
}
