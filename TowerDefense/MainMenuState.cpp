#include"MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window_, float gridSize_, std::stack<State*>* states, SaveSystem* saveSystem) :
	State(window_, gridSize_, states, saveSystem) {
	initMapsTexture();
	initVariable();
	initButtons();
	initMapsData();
	loadWayPoints();

	changeSelectedMap(0);
}
MainMenuState::~MainMenuState() {
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		delete it->second;
	}
}

void MainMenuState::initMapsData() {
	std::ifstream in_file;
	std::string line;
	unsigned int i = -1;

	in_file.open("Map/map.txt");

	if (in_file.is_open()) {
		while (std::getline(in_file, line)) {
			if (line == "START") {
				mapData.push_back(std::vector<std::string>());
				i++;
			}
			else
				mapData[i].push_back(line);
		}
	}
	else
		std::cout << "MAINMENU.CPP::ERROR_LOADING_MAP_FILE" << std::endl;

	in_file.close();
}

void MainMenuState::loadWayPoints() {
	std::ifstream in_file;
	std::string line;
	sf::Vector2f v;
	unsigned int i = -1;

	in_file.open("Map/waypointsPos.txt");
	wayPoints.push_back(std::vector<sf::Vector2f>());
	if (in_file.is_open()) {
		while (std::getline(in_file, line)) {
			std::istringstream iss(line);
			if (line == "START") {
				wayPoints.push_back(std::vector<sf::Vector2f>());
				i++;
			}
			else {
				iss >> v.x >> v.y;
				wayPoints[i].push_back(v);
			}
		}
	}
	else
		std::cout << "MAINMENU.CPP::ERROR_LOADING_MAP_FILE" << std::endl;

	in_file.close();
}

void MainMenuState::initVariable() {
	
	text.setFont(font);
	text.setCharacterSize(38);
	text.setStyle(sf::Text::Bold);
	text.setString("Basic Tower Defense");
	text.setPosition(360-text.getGlobalBounds().width/2, 10);

	backgroundSelectedTurretIcon = sf::RectangleShape(sf::Vector2f(100, 100));
	backgroundSelectedTurretIcon.setFillColor(sf::Color(20, 20, 20, 150));
	backgroundSelectedTurretIcon.setPosition(sf::Vector2f(130.f, 100.f));

	//init les 3 texts
	if (saveSystem->getBestTimes()->size() >= 3) {
		for (unsigned int i = 0; i < 3; i++) {
			mapsText[std::to_string(i)] = sf::Text("best Time: " + std::to_string((int)saveSystem->getBestTimes()->at(i)), font, 12);
			mapsText[std::to_string(i)].setStyle(sf::Text::Bold);
			mapsText[std::to_string(i)].setPosition(130+180*i, 200);
		}
	}


}

void MainMenuState::initButtons() {
	buttons["SELECT_FIRST_MAP"] = new gui::Button(
		130.f , 100.f, 100.f, 100.f,
		&font, "", 35,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50)
	);

	buttons["SELECT_SECOND_MAP"] = new gui::Button(
		310.f , 100.f, 100.f, 100.f,
		&font, "", 35,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50)
	);

	buttons["SELECT_THIRD_MAP"] = new gui::Button(
		490.f, 100.f, 100.f, 100.f,
		&font, "", 35,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(250, 250, 250), sf::Color(200, 200, 200, 200), sf::Color(100, 100, 100, 50)
	);

	buttons["START_GAME"] = new gui::Button(
		235.f, 270.f, 250.f, 50.f,
		&font, "Start", 45,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["EXIT_STATE"] = new gui::Button(
		235.f, 340.f, 250.f, 50.f,
		&font, "Quit", 45,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void MainMenuState::initMapsTexture() {
	for (int i = 0; i < 3; i++) {
		mapsTextures[std::to_string(i)] = sf::Texture();
		if (!mapsTextures[std::to_string(i)].loadFromFile("Map/map" + std::to_string(i) + "Icon.png")) {
			std::cout << "ERROR::MAINMENUSTATE_CANT_LOAD_TEXTURE::" << i << std::endl;
		}

		mapsSprites[std::to_string(i)] = sf::Sprite(mapsTextures[std::to_string(i)], sf::IntRect(0, 0, 321, 321));
		mapsSprites[std::to_string(i)].setScale(100.f/321.f, 100.f/321.f);
		mapsSprites[std::to_string(i)].setPosition(130 + 180 * i, 100);
	}
}


void MainMenuState::changeSelectedMap(unsigned int id) {
	selectedMapId = id;
	switch (id) {
	case 0:
		backgroundSelectedTurretIcon.setPosition(sf::Vector2f(130.f, 100.f));
		break;
	case 1:
		backgroundSelectedTurretIcon.setPosition(sf::Vector2f(310.f, 100.f));
		break;
	case 2:
		backgroundSelectedTurretIcon.setPosition(sf::Vector2f(490, 100.f));
		break;
	default:
		break;
	}
}

void MainMenuState::startGame() {
	states->push(new GameState(window, gridSize, states, saveSystem, &mapData[selectedMapId], &wayPoints[selectedMapId], selectedMapId));
}

void MainMenuState::event(sf::Event sfEvent) {
}

void MainMenuState::update(const float dt) {
	State::update(dt);

	updateButtons();
}

void MainMenuState::updateTexts() {
	initVariable();
}

void MainMenuState::updateButtons() {
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}

	if (buttons["SELECT_FIRST_MAP"]->isPressed())
		changeSelectedMap(0);

	if (buttons["SELECT_SECOND_MAP"]->isPressed())
		changeSelectedMap(1);

	if (buttons["SELECT_THIRD_MAP"]->isPressed())
		changeSelectedMap(2);

	if (buttons["START_GAME"]->isPressed())
		startGame();

	if (buttons["EXIT_STATE"]->isPressed())
		endState();
}

void MainMenuState::render() {
	window->draw(text);

	for (auto& it : mapsSprites) {
		window->draw(it.second);
	}

	for (auto& it : buttons) {
		it.second->render(*window);
	}

	for (auto& it : mapsText) {
		window->draw(it.second);
	}

	window->draw(backgroundSelectedTurretIcon);
}