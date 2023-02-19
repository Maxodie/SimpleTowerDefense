#include "Enemy.h"

Enemy::Enemy(const float gridSize, sf::Texture* texture, EnemyData* enemyData, std::vector<sf::Vector2f>* wayPoints) {
	this->gridSize = gridSize;
	this->enemyData = new EnemyData(*enemyData);
	this->texture = texture;
	this->wayPoints = wayPoints;

	life = enemyData->life;
	speed = enemyData->speed;

	initSprite();
	initLifeBar();
	goToNextPoint();
}

Enemy::~Enemy() {
	delete texture;
	delete enemyData;
	delete wayPoints;
}

void Enemy::initSprite() {
	sprite = sf::Sprite(*texture, sf::IntRect(0, 0, 20, 20));
	sprite.setScale(gridSize/20, gridSize/20);//gridSize/20 pour avoir la taille général
	sprite.setPosition(wayPoints->at(0) * gridSize);
}

void Enemy::initLifeBar() {
	lifeBarBackground = sf::RectangleShape(sf::Vector2f(50, 10));
	lifeBarBackground.setFillColor(sf::Color(49, 49, 49));
	lifeBarBackground.setOutlineColor(sf::Color(20, 20, 20));
	lifeBarBackground.setOutlineThickness(1);

	lifeBarFill = sf::RectangleShape(sf::Vector2f(50, 10));
	lifeBarFill.setFillColor(sf::Color(167, 25, 25));
}



void Enemy::goToNextPoint() {
	if (!destroyState && wayPoints->size() > posId+1) {
		posId ++;
	}
	else {//at the end of the way
		getReadyToBeDestroy();
	}
}

void Enemy::changeSpeed(float percentage, float time) {
	if (speed != enemyData->speed) return;//already affect by speed changer

	speedChangeTime = time;
	speed *= 1-percentage;
	clock.restart();
}

void Enemy::updateSpeedChanges() {
	if (speedChangeTime <= clock.getElapsedTime().asSeconds()) {
		speed = enemyData->speed;
	}
}

void Enemy::getReadyToBeDestroy() {
	destroyState = true;
}

bool Enemy::getDestroyState() {
	return destroyState;
}

bool Enemy::getIsDropLoot() {
	return isDroppingLoot;
}

EnemyData* Enemy::getEnemyData() {
	return enemyData;
}

sf::Vector2f Enemy::getPosition() {
	return sprite.getPosition();
}

sf::Vector2f Enemy::getSize() {
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Enemy::lostHP(float amount) {
	life -= amount;

	if (life <= 0) {
		life = 0;
		isDroppingLoot = true;
		getReadyToBeDestroy();
	}

}

void Enemy::updateGUI() {
	lifeBarFill.setScale(life / enemyData->life, 1);

	sf::Vector2f sPos = sprite.getPosition();
	float sWidth = sprite.getGlobalBounds().width;
	lifeBarBackground.setPosition(sPos.x + sWidth / 2 - 25, sPos.y - 10);
	lifeBarFill.setPosition(sPos.x + sWidth/2-25, sPos.y - 10);
}

sf::Vector2f Enemy::normilize(const sf::Vector2f& source) {
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
	
}

void Enemy::checkForNextPoint() {
	if (std::abs(sprite.getPosition().x / gridSize - wayPoints->at((int)posId).x) < .1f && std::abs(sprite.getPosition().y / gridSize - wayPoints->at((int)posId).y) < .1f)
		goToNextPoint();
}

void Enemy::update(const float dt) {
	updateSpeedChanges();
	checkForNextPoint(); 
	dir = normilize(sf::Vector2f(wayPoints->at(static_cast<int>(posId)) - (sprite.getPosition()/gridSize)));
	sprite.move(dir * speed * dt);

	updateGUI();
}

void Enemy::render(sf::RenderTarget& target) {
	target.draw(sprite);
	target.draw(lifeBarBackground);
	target.draw(lifeBarFill);
}