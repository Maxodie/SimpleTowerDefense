#pragma once
#include<SFML/Graphics.hpp>

class PlayerGUI {
public:
	PlayerGUI(const float gridSize, sf::Font* font, const float startLife);
	~PlayerGUI();

	void initLifeBar();

	void updateLifeBar(const float lifeAmount);

	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape lifeBarBackground;
	sf::RectangleShape lifeBarFill;

	sf::Text lifeText;

	sf::Font* font;

	float startLife;
	float gridSize;
};

