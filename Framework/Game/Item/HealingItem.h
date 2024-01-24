#pragma once

class HealingItem
{
public:
	HealingItem();
	~HealingItem();

	class AnimationClip* GetHealingItemClip() { return healingItemClip; }
	string GetName(int indexNo) { return name[indexNo - 1]; }
	string GetExplan(int indexNo) { return explain[indexNo - 1]; }
	int HealingNum(int indexNo);

private:
	class AnimationClip* healingItemClip = nullptr;
	vector<string> name;
	vector<string> explain;

	
};