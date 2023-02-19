#pragma once
#include<SFML/Graphics.hpp>

class Tile {
public:
	Tile(float x, float y, float gridSize, sf::Sprite *texture);
	~Tile();

	sf::Sprite* getSprite();

private:
	sf::Sprite *sprite;
};

