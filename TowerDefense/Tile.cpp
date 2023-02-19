#include "Tile.h"

Tile::Tile(float x, float y, float gridSize, sf::Sprite *texture) {
	sprite = new sf::Sprite(*texture);
	sprite->setPosition(x * gridSize, y * gridSize);
}

Tile::~Tile() {
	delete sprite;
}

sf::Sprite* Tile::getSprite() {
	return sprite;
}