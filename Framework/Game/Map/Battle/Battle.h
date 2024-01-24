#pragma once

#include "GeoMetries\TextureRect.h"
#include "Game\Actor\Pokemon.h"
#include "../UnitTest/01.Character/Player.h"
#include "Game\UI\HpBar.h"
#include "Game\UI\ExpBar.h"
#include "Game\UI\BattleBG.h"
#include "Game/Item/PokeBall.h"


class Battle
{
public:
	Battle(Player* player, Pokemon* enemyPokemon);
	~Battle();
	
	void Update();
	void Render();

	void SetBattle() { battleOn = true; battleover = false; }
	void BattleEnd() { battleOn = false; }
	bool IsBattle() { return battleOn; }

	void PlayerTurn();
	void EnemyTurn();

	void Damage(int selectSkill);
	void BattlePhase();
	void HpUpdate();
	void CalcExpPercent();

private:
	bool battleOn = false;
	TextureRect* BackGround = nullptr;
	TextureRect* BackGroundTp = nullptr;
	TextureRect* BackGroundBt = nullptr;
	unordered_map<wstring, TextureRect*> battleBack;
	vector<TextureRect*> UI;

	class HpBar* pHp = nullptr;
	class HpBar* eHp = nullptr;
	class ExpBar* exp = nullptr;
	class BattleBG* battlebackground = nullptr;
	class Player* btPlayer = nullptr;
	class Pokemon* enemyPM = nullptr;
	int selectSkill = 0;
	bool playerturn = false;							//�÷��̾� ������ �˻� ture�� �÷��̾��� false�� ����
	bool battleover = false;							//���� ����
	bool textrendering = false;
	float playerHpPer = 1.0;
	float enemyHpPer = 1.0;
	int turncount = 2;
	int enemySelect = 0;
	BattleSequence enemyBattleSeq = Wait;
	BattleSequence* battleSeq = nullptr;

	int playerRound = 0; // player �� ���� ���� �ൿ�� +1
	int enemyRound = 0; // enemy �� ���� ���� �ൿ�� +1
	int round = 1; // ���� �� ����
	
};