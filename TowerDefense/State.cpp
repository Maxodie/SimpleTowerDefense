#include"State.h"

State::State(sf::RenderWindow* window_, float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem) {
	gridSize = gridSize_;
	window = window_; 0;
	this->states = states;
	this->saveSystem = saveSystem;

	initVariable();
}

State::~State() {
	delete states;
	delete saveSystem;
}

bool State::getQuitState() {
	return quitState;
}

void State::initVariable() {
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		// error...
	}
}

void State::update(const float dt) {
	updateMousePositions();
}

void State::updateTexts() {
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(mousePosView.x) / static_cast<unsigned>(gridSize),
		static_cast<unsigned>(mousePosView.y) / static_cast<unsigned>(gridSize)
	);
}

void State::endState() {
	quitState = true;
}

void State::render() {
}