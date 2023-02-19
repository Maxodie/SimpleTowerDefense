#pragma once
#include"Turret.h"
#include"TurretType.h"
#include"Enemy.h"
#include"Gui.h"

struct TurretPosInfo {
	Turret* turret = nullptr;
	sf::Vector2f pos;
};

class TurretManager {
public:
	TurretManager(const float gridSize, std::vector<Enemy*>* enemies);
	~TurretManager();

	const sf::Texture* getTurretTextures(TurretType type);

	void initGraphics();
	void initTextures();

	void setDeleteOrBuyButton(gui::Button* button);

	void setActiveSelectedPos(bool state);
	void changePosition(const sf::Vector2f selectedPos);
	void ChangeMode(bool isBuyMode);
	bool getIsBuyMode();
	TurretData* getSelectedTurretData();

	bool selectTurret();

	bool canBuildTurret();
	std::string getTurretTypeStringWithType(TurretType type);
	void createTurret(TurretType type, TurretData* turretData);
	void deleteSelectedTurret();

	void update();
	void render(sf::RenderTarget& target);


private:
	std::vector<TurretPosInfo*> turretsInfo;
	sf::RectangleShape* rectangleSelectedPos;

	sf::Vector2f* selectedPos = nullptr;
	TurretPosInfo* selectedTurret = nullptr;

	gui::Button* deleteOrBuyButton;

	std::vector<Enemy*>* enemies;

	std::map<const std::string, sf::Texture*> turretTextures;

	float gridSize;
	bool activeState = false;
	bool isDeleteMode = false;
};