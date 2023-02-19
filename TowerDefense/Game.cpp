#include"Game.h"
Game::Game(float gridSize_) {
	window = nullptr;
	gridSize = gridSize_;
	dt = 0.f;
	saveSystem = new SaveSystem();

	initWindow();
}

Game::~Game() {
	delete window;
	delete saveSystem;

	while (!states.empty())
	{
		states.pop();
	}
}

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Tower Defense", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void Game::run() {
	states.push(new MainMenuState(window, gridSize, &states, saveSystem));

	while (window->isOpen()) {
		updateDt();
		update();
		render();
	}
}

void Game::updateDt() {
	dt = dtClock.restart().asSeconds();
}

void Game::initInput() {
	if (event.type == sf::Event::Closed)
		window->close();

	if (!states.empty())
		states.top()->event(event);
}

void Game::update() {
    while (window->pollEvent(event)) {
		initInput();
    }

	if (!states.empty()) {
		states.top()->update(dt);

		if (states.top()->getQuitState()) {
			states.pop();
			if (!states.empty()) {
				states.top()->updateTexts();
			}
		}
	}
	else {
		window->close();
	}
}

void Game::render() {
	window->clear();

	if (!states.empty()) {
		states.top()->render();
	}

	window->display();
}