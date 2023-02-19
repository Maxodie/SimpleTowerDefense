#pragma once
#include<string>
#include<vector>
#include<sstream>

class SaveSystem {
public:
	SaveSystem();
	~SaveSystem();

	std::vector<float>* getBestTimes();

	void saveBestTime(float bestGameTime, int mapId);
	void loadBestTime();
	std::string encryptAndDecryptString(std::string data);

private:
	std::vector<float> bestTimes;
};