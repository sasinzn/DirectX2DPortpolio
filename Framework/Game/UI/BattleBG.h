#pragma once

class BattleBG
{
public:
	BattleBG(class Player* player, class Pokemon* enemyPokemon);
	~BattleBG();

	void Update();
	void Render();
	void PickMenu(int* selecSkill, bool* isBattle, BattleSequence* seq);
	SelectMove GetCurrentMenu() { return currentMenu; }
	int GetSelectSkill() { return selectSkill; }
	bool GetFight() { return fight; }
	void SkillRender();
	wstring ConvertPMtype(PmType type);
	void HpRender();
	void Reset();
	void EnemyTextRender();
	void EnemyTextRender(string skill, BattleSequence* seq);
	void PlayerTextRender();
	void PlayerTextRender(string skill, BattleSequence* seq);
	void PlayerTextRender(BattleSequence* seq);
	void PlayerIdleTextRender();
	void SetPlayerTurn() { playerturn = true; }
	void SetEnemyTurn() { playerturn = false; }
	void SetUsingPokeballReset() { usingPokeball = false; }
	void SetLevelUp() { levelUp = true; }
	void PlayerPokemonLvUp();
	void SetBattleEnd() { battleEnd = true; }
	void SetBattleStart() { battleEnd = false; }
	bool GetBattleEnd() { return battleEnd; }
	void SetPokemon(class Pokemon* enemyPokemon) { enemyData = enemyPokemon; }

private:
	class ProgressBar* battleMenu = nullptr;
	class ProgressBar* selectFIGHT = nullptr;
	class ProgressBar* selectBAG = nullptr;
	class ProgressBar* selectPOKEMON = nullptr;
	class ProgressBar* selectRUN = nullptr;
	class ProgressBar* fightMenu = nullptr;
	class ProgressBar* selectSkill1 = nullptr;
	class ProgressBar* selectSkill2 = nullptr;
	class ProgressBar* selectSkill3 = nullptr;
	class ProgressBar* selectSkill4 = nullptr;
	class SwitchPokemon* switchPokemon = nullptr;
	class ItemBag* bagpack = nullptr;
	class TextureRect* levelUpResult = nullptr;
	SelectMove currentMenu;
	bool selectMenu = false;
	bool fight = false;
	bool playerturn = false;
	bool enemyTextRendering;
	bool playerTextRendering;
	bool switching = false;
	bool result = false;
	bool usingPokeball = false;
	bool gotchaPokemon = false;
	bool levelUp = false;
	bool levelUpRendering = false;
	bool battleEnd = false;
	class Player* playerData = nullptr;
	class Pokemon* enemyData = nullptr;
	MenuTree* menu = nullptr;
	int selectSkill = 1;
	int* spacecount = nullptr;
	float DeltaTime = 0.0f;
	string enemySkillName;
	string playerSkillname;
};