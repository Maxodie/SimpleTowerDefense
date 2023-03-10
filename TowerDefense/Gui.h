#pragma once
#include <SFML/Graphics.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button
	{
	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned charracter_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;

		//Modifiers
		void setText(const std::string new_text);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	private:
		short unsigned buttonState;
		bool isButtonDown = false;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
	};
}