#pragma once

class Item
{
public:
	Item();
	~Item();

	class PokeBall* GetPokeballs() { return balls; }
	class HealingItem* GetHealingItems() { return healings; }
	class Keyitem* GetKeyItems() { return keyitems; }
	int GetBallNums(int indexNo) { return ballsNum[indexNo - 1]; } // ball indexNo 1 ~ 17
	int GethealingNums(int indexNo) { return healingNum[indexNo - 1]; } // ball indexNo 1 ~ 17

	void UseBalls(int indexNo) { ballsNum[indexNo - 1] -= 1; }
	void UseItemNum(int indexNo) { healingNum[indexNo - 1] -= 1; }
	void UseItems(int indexNo , class Pokemon* pokemon);

private:
	class PokeBall* balls = nullptr;
	class HealingItem* healings = nullptr;
	class Keyitem* keyitems = nullptr;
	int ballsNum[17];
	int healingNum[21];

};