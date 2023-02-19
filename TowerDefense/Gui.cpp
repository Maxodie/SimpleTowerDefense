#include"Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned charracter_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color)
{
	buttonState = BTN_IDLE;

	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(idle_color);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(charracter_size);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		shape.getPosition().y //+ (shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
	);

	idleColor = idle_color;
	hoverColor = hover_color;
	activeColor = active_color;

	textIdleColor = text_idle_color;
	textHoverColor = text_hover_color;
	textActiveColor = text_active_color;

	outlineIdleColor = outline_idle_color;
	outlineHoverColor = outline_hover_color;
	outlineActiveColor = outline_active_color;

	shape.setFillColor(this->idleColor);
}

gui::Button::~Button()
{
	delete font;
}

//Accessors
const bool gui::Button::isPressed() const
{
	return (buttonState == BTN_ACTIVE);
}

const std::string gui::Button::getText() const
{
	return text.getString();
}

//Modifiers
void gui::Button::setText(const std::string new_text)
{
	text.setString(new_text);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		shape.getPosition().y);
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the State for idle, hover and pressed*/

	//Idle
	buttonState = BTN_IDLE;

	//Hover
	if (shape.getGlobalBounds().contains(mousePos)) {
		if (isButtonDown && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			isButtonDown = false;

		buttonState = BTN_HOVER;

		//Pressed
		if (!isButtonDown && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_ACTIVE;
			isButtonDown = true;
		}
	}
	else //if pressed before being on the button
		isButtonDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(outlineActiveColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Blue);
		shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}