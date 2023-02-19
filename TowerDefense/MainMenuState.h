#pragma once
#include"GameState.h"
#include"Gui.h"
#include<sstream>

class MainMenuState : public State {
public:
	MainMenuState(sf::RenderWindow* window_, float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem);
	virtual ~MainMenuState();

	void initMapsData();
	void loadWayPoints();

	void initVariable();
	void initButtons();
	void initMapsTexture();
	void changeSelectedMap(unsigned int id);

	void startGame();

	void event(sf::Event sfEvent);
	void update(const float dt);
	void updateTexts();
	void updateButtons();
	void render();

private:
	sf::Text text;
	std::map<std::string, gui::Button*>  buttons;
	std::map<std::string, sf::Text>  mapsText;
	std::map<std::string, sf::Texture>  mapsTextures;
	std::map<std::string, sf::Sprite>  mapsSprites;

	std::vector< std::vector<std::string > > mapData;
	std::vector< std::vector<sf::Vector2f > > wayPoints;

	sf::RectangleShape backgroundSelectedTurretIcon;

	unsigned int selectedMapId = 0;
};