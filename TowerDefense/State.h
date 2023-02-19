#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include <stack> 
#include"saveSystem.h"

class State
{
public:
	State(sf::RenderWindow *window_, float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem);
	virtual ~State();

	bool getQuitState();

	virtual void initVariable();
	virtual void event(sf::Event sfEvent) = 0;
	virtual void update(const float dt);
	virtual void updateTexts();
	void updateMousePositions();
	virtual void render() = 0;
	void endState();

protected:
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	sf::RenderWindow* window;
	std::stack<State*>* states;
	SaveSystem* saveSystem;

	sf::Font font;

	float gridSize;

	bool quitState = false;

};