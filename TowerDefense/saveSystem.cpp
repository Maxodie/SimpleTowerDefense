#include"saveSystem.h"
#include<fstream>
#include<iostream>

const char key[] = "l";

SaveSystem::SaveSystem() {
	loadBestTime();
}

SaveSystem::~SaveSystem() {

}

std::vector<float>* SaveSystem::getBestTimes() {
	return &bestTimes;
}

void SaveSystem::saveBestTime(float bestGameTime, int mapId) {
	std::ofstream flux("save.txt");
	std::string result = "";

	for (int i = 0; i < 3; i++) {
		if (mapId == i) {
			result += std::to_string((int)bestGameTime);
		}
		else {
			result += std::to_string((int)bestTimes[i]);
		}

		result += " ";
	}
	if (flux) {
		flux << encryptAndDecryptString(result);
	}
	else
		std::cout << "ERROR:SAVESYSTEM::CANT_LOAD_SAVE" << std::endl;
}

void SaveSystem::loadBestTime() {
	std::string bestScore = "";
	std::string line = "";
	std::ifstream flux("save.txt");
	bestTimes.clear();
	if (flux) {
		while (std::getline(flux, line)) {
			bestScore += line;
		}
	}

	if (bestScore == "") {
		for (int i = 0; i < 3; i++) {
			bestTimes.push_back(.1f);
		}
		return;
	}

	try {
		bestScore = encryptAndDecryptString(bestScore);
		std::istringstream iss(bestScore);
		float a, b, c;
		iss >> a >> b >> c;
		bestTimes.push_back(a);
		bestTimes.push_back(b);
		bestTimes.push_back(c);
	} catch(const std::exception& e) {
		std::cout << "ERROR::SAVESYSTEM_" << e.what() << std::endl;
	}
}

std::string SaveSystem::encryptAndDecryptString(std::string data) {
	for (int i = 0; i < data.length(); i++)
	{
		data[i] = data[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}

	return data;
}