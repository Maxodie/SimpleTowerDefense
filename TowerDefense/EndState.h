#pragma once
#include"State.h"
#include"Gui.h"
#include<map>

class EndState: public State {
public:
	EndState(sf::RenderWindow* window_, const float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem,
		float survivedTime, int mapId);
	~EndState();

	void initTexts();
	void initButtons();

	void saveBestTime();

	void event(sf::Event sfEvent);
	void update(const float dt);
	void updateButtons();
	void render();

private:
	sf::Text text;
	sf::Text bestScoreText;

	std::vector<float>* bestTimes;

	std::map<const std::string, gui::Button*> buttons;

	float survivedTime;
	int mapId;
};

