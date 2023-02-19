#pragma once
#include <SFML/Graphics.hpp>
#include"MainMenuState.h"
#include"Global.h"

class Game {
public:
	//Constructor/Destructor
	Game(float gridSize_);
	virtual ~Game();

	//Function
	void run();
	void initWindow();

	void initInput();
	void updateDt();
	void update();
	void render();

private:
	sf::RenderWindow *window;
	sf::Event event;

	std::stack<State*> states;
	SaveSystem* saveSystem;

	float dt;
	sf::Clock dtClock;
	float gridSize;
};