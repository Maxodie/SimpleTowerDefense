#pragma once
#include <vector>
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include"Tile.h"

class TileMap {
public:
	TileMap(const float gridSize, std::vector<std::string>* mapData);
	~TileMap();

	void loadTexture();
	void loadMap();
	
	std::vector<std::string>* getSaveMapData();

	void render(sf::RenderTarget& target);

private:
	std::vector< std::vector< Tile* > > map;
	sf::Texture tileSheet;
	std::vector< sf::Sprite* > tiles;

	std::vector<std::string>* mapData;

	float gridSize;
};

