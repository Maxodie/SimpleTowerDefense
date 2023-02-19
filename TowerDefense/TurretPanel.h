#pragma once
#include"Gui.h"
#include"PlayerData.h"
#include"Global.h"
#include"TurretManager.h"

enum class PanelButtonInstructions{
	NOTHING,
	BUY_TURRET,
	SELECT_BASIC_TURRET,
	SELECT_FREEZE_TURRET,
};

class TurretPanel {
public:
	TurretPanel(const float gridSize, sf::Font& font, PlayerData* playerData, 
		TurretManager* turretManager, std::map<const std::string, TurretData*>* turretsData);
	~TurretPanel();

	void initButtons();
	void initPanel();
	void initText();

	PanelButtonInstructions getButtonPressed();
	void updateButtons(sf::Vector2f mousePos);
	void updateTexts();
	void changeInfoText(std::string info, sf::Color color);
	void changeSelectedTurret(TurretType type);

	void render(sf::RenderTarget& target);

private:
	TurretManager* turretManager;

	std::map<std::string, gui::Button*> buttons;
	std::map<const std::string, TurretData*> turretsData;

	std::vector<sf::RectangleShape> turretIcons;
	std::vector<sf::Text> turretInfoText;

	sf::RectangleShape backgroundRectangle;
	sf::RectangleShape backgroundSelectedTurretIcon;
	sf::Font* font;
	sf::Text playerMoneyText;
	sf::Text infoText;
	PlayerData* playerData;

	float gridSize;
};

