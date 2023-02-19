#include "EndState.h"

EndState::EndState(sf::RenderWindow* window_, const float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem,
	float survivedTime, int mapId) :
	State(window_, gridSize_, states, saveSystem) {
	this->survivedTime = survivedTime;
	this->bestTimes = saveSystem->getBestTimes();
	this->mapId = mapId;


	initTexts();
	initButtons();

	saveBestTime();
}

EndState::~EndState() {
	delete saveSystem;
}

void EndState::initTexts() {
	text.setFont(font);
	text.setCharacterSize(32);
	text.setStyle(sf::Text::Bold);
	text.setString("Survived Time: " + std::to_string((int)survivedTime));
	text.setPosition(360 - text.getGlobalBounds().width / 2, 70);

	bestScoreText.setFont(font);
	bestScoreText.setCharacterSize(32);
	bestScoreText.setStyle(sf::Text::Bold);
	bestScoreText.setString("Best Time: " + std::to_string((int)bestTimes->at(mapId)));
	bestScoreText.setPosition(360 - text.getGlobalBounds().width / 2, 10);
}

void EndState::initButtons() {
	buttons["EXIT_STATE"] = new gui::Button(
		235.f, 170.f, 250.f, 50.f,
		&font, "Quit", 45,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void EndState::saveBestTime() {
	if(survivedTime > bestTimes->at(mapId))
		saveSystem->saveBestTime(survivedTime, mapId);
}

void EndState::event(sf::Event sfEvent) {
}

void EndState::update(const float dt) {
	State::update(dt);

	updateButtons();
}

void EndState::updateButtons() {
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}

	if (buttons["EXIT_STATE"]->isPressed()) {
		saveSystem->loadBestTime();//To be sure it will load the good times
		endState();
	}
}

void EndState::render() {
	window->draw(text);
	window->draw(bestScoreText);

	for (auto& it : buttons) {
		it.second->render(*window);
	}
}
