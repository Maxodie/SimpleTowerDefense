#include"GameState.h"

GameState::GameState(sf::RenderWindow* window_, const float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem,
	std::vector<std::string>* mapData, std::vector<sf::Vector2f>* wayPoints, int mapId):
	State(window_, gridSize_, states, saveSystem) {
	this->mapId = mapId;
	this->tileMap = new TileMap(gridSize, mapData);
	initButtons();
	initText();

	this->player = new Player(gridSize, tileMap->getSaveMapData(), font);
	this->enemyManager = new EnemyManager(gridSize, player, wayPoints);
	this->turretManager = new TurretManager(gridSize, this->enemyManager->getEnemies());
	this->turretShop = new TurretShop(gridSize, font, turretManager, player->getPlayerData());

	this->enemyManager->setTurretPanel(turretShop->getTurretPanel());

	this->player->setTurretManager(turretManager);
}

GameState::~GameState() {
	delete enemyManager;
	delete tileMap;
	delete player;
	delete turretManager;
	delete turretShop;

	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void GameState::initButtons() {
	buttons["EXIT_STATE"] = new gui::Button(
		10.f, 10.f * gridSize + 50.f, 150.f, 40.f,
		&font, "Quit", 45,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void GameState::initText() {
	timerText.setFont(font);
	timerText.setCharacterSize(32);
	timerText.setStyle(sf::Text::Bold);
	timerText.setPosition(250 - timerText.getGlobalBounds().width / 2, 330);
}

void GameState::event(sf::Event sfEvent) {
	player->inputEvent(sfEvent, mousePosView);
}

void GameState::update(const float dt) {
	State::update(dt);
	updateButtons();

	timerText.setString("Time: " + std::to_string((int)gameTimer.getElapsedTime().asSeconds()));

	enemyManager->update(dt);
	turretShop->update(mousePosView);
	turretManager->update();

	if (!getQuitState() && player->getDeadState()) {
		endState();
		states->push(new EndState(window, gridSize, states, saveSystem, gameTimer.getElapsedTime().asSeconds(), mapId));
	}
}

void GameState::updateButtons() {
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}

	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
}

void GameState::render() {
	if (getQuitState()) return;

	for (auto& it : buttons) {
		it.second->render(*window);
	}

	window->draw(timerText);

	tileMap->render(*window);

	turretManager->render(*window);
	enemyManager->render(*window);
	turretShop->render(*window);

	player->render(*window);
}