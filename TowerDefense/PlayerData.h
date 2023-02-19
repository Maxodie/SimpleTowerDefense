#pragma once
class PlayerData {
public:
	PlayerData(const float money);
	~PlayerData();

	void addMoney(const unsigned int addedMoney);
	bool buy(const unsigned int cost);
	const unsigned int getPlayerMoney();

private:
	unsigned int playerMoney;
};

