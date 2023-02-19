#include "TileMap.h"

TileMap::TileMap(const float gridSize, std::vector<std::string>* mapData) {
	this->gridSize = gridSize;
	this->mapData = mapData;

	loadTexture();
	loadMap();
}

TileMap::~TileMap() {
	delete mapData;
	for (size_t x = 0; x < 5; x++) {
		for (size_t y = 0; y < 5; y++) {
			delete map[x][y];
		}
	}
}

void TileMap::loadTexture() {
	if (!tileSheet.loadFromFile("Map/tileSheet1.png"))
		std::cout << "TILEMAP.CPP::CANT LOAD TEXTURE" << std::endl;

	for (int x = 0; x < 8; x++) {
			tiles.push_back(new sf::Sprite(tileSheet, sf::IntRect(x*100, 0, 100, 100)));
	}

	for (auto& it : tiles) {
		it->setScale(gridSize / 100, gridSize / 100);
	}
}

void TileMap::loadMap() {
	map.resize(mapData->size(), std::vector<Tile*>());
	for (size_t y = 0; y < mapData->size(); y++) {
		for (size_t x = 0; x < mapData->at(y).size(); x++) {
			int id = int(mapData->at(y)[x]) - 48;
			map[y].push_back(new Tile(static_cast<float>(x), static_cast<float>(y), gridSize, tiles[id]));
		}
	}
}

std::vector<std::string>* TileMap::getSaveMapData() {
	return mapData;
}

void TileMap::render(sf::RenderTarget& target) {
	for (auto& x : map) {
		for (auto* y : x) {
			target.draw(*y->getSprite());
		}
	}
}