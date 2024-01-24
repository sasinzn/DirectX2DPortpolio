#pragma once
#include "Game\Status\Status.h"
#include "Game\Status\PokeDex.h"
#include "Game\Status\Skills.h"
#include "Game/AI/State/MonsterState.h"

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

struct PkData
{
	int indexNo;
	string indexName;
	string name;
	int level;
	int exp;
	int maxHp;
	int currentHp;
	int skill1PP;
	int skill2PP;
	int skill3PP;
	int skill4PP;
	int skill1currentPP;
	int skill2currentPP;
	int skill3currentPP;
	int skill4currentPP;
};

class Pokemon
{
public:
	Pokemon(int indexNo, int level,bool playerPokemon = false);
	~Pokemon();

	void Update();
	void Render();

	void SetPokeMonName(string name) { pInfo.name = name; }
	void SetPokemon(int indexNo, int level, bool playerPokemon = false);
	void SetSkill(int level);
	void SetCurrentHP(int currentHP) { pInfo.currentHp = currentHP; }
	void SetDamage(int damage);
	void VisitPMCenter(); // ���ϸ� ���� �湮 (HP/PP ��üȸ��)
	void EarnExp(int exp);
	void LevelUp();
	void StrangeCandyEat();
	bool GetLevelUp() { return levelup; }
	void SetLevelupEnd() { levelup = false; }
	void UsingSkill(int skillnum);
	bool NotEnoughPP(int skillnum);
	void UsingItem(int itemcode);
	void Healing(int num);
	void ResetItemCount() { usingitemcount = 0; }
	bool isRevolution() { if (revolution && pInfo.level >= revolutionLevel) return true; else return false; }
	int RevolutionIndexNo() { return revolutionIndexNo; }
	int GetCurrentLevel() { return pInfo.level; }
	

	SkillData GetSkillData(int num) { return skills[num-1]; } //��ų ������ �޾ƿ���
	PkData GetPKData() { return pInfo; }	// ���ϸ� hp �� ��ų����Ʈ �޾ƿ���
	Status* GetStat() { return stat; }
public:
	MonsterState* state;

private:
	PkData pInfo;
	SkillData skills[4];
	vector<SkillData*> learnSkills;
	Status* stat = nullptr;
	PokeDex* pDex = nullptr;
	Skill* pSkill = nullptr;
	Animator* animator = nullptr;
	AnimationRect* animRect = nullptr;
	bool levelup = false;
	int usingitemcount = 0;
	bool revolution = false;
	int revolutionLevel = 0;
	int revolutionIndexNo = 0;
	
};