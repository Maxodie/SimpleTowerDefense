#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(const float gridSize, sf::Font* font, const float startLife) {
	this->font = font;
	this->startLife = startLife;
	this->gridSize = gridSize;

	initLifeBar();
	updateLifeBar(startLife);
}

PlayerGUI::~PlayerGUI() {
	delete font;
}

void PlayerGUI::initLifeBar() {
	lifeBarBackground = sf::RectangleShape(sf::Vector2f(200, 40));
	lifeBarBackground.setFillColor(sf::Color(49, 49, 49));
	lifeBarBackground.setOutlineColor(sf::Color(20, 20, 20));
	lifeBarBackground.setOutlineThickness(3);
	lifeBarBackground.setPosition(200, 10 * gridSize + 60);

	lifeBarFill = sf::RectangleShape(sf::Vector2f(200, 40));
	lifeBarFill.setFillColor(sf::Color(167, 25, 25));
	lifeBarFill.setPosition(200, 10 * gridSize + 60);

	lifeText.setFont(*font);
	lifeText.setCharacterSize(32);
	lifeText.setOutlineColor(sf::Color::Black);
	lifeText.setOutlineThickness(1);
	lifeText.setStyle(sf::Text::Bold);
}

void PlayerGUI::updateLifeBar(const float lifeAmount) {
	lifeBarFill.setScale(lifeAmount/startLife, 1);
	lifeText.setString(std::to_string((int)lifeAmount) + "/" + std::to_string((int)startLife));
	lifeText.setPosition(300 - lifeText.getGlobalBounds().width / 2, 10 * gridSize + 60);
}

void PlayerGUI::render(sf::RenderTarget& target) {
	target.draw(lifeBarBackground);
	target.draw(lifeBarFill);
	target.draw(lifeText);
}
