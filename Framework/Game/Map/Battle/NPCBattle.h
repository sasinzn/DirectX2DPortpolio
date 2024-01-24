#pragma once

#include "GeoMetries\TextureRect.h"
#include "Game\Actor\Pokemon.h"
#include "../UnitTest/01.Character/Player.h"
#include "../UnitTest/01.Character/BattleNPC.h"
#include "Game\UI\HpBar.h"
#include "Game\UI\ExpBar.h"
#include "Game\UI\BattleBG.h"
#include "Game/Item/PokeBall.h"


class NPCBattle
{
public:
	NPCBattle(Player* player, BattleNPC* npc);
	~NPCBattle();

	void Update();
	void Render();

	void SetNPCBattle() { battleOn = true; battleover = false; }
	void NPCBattleEnd() { battleOn = false; }
	bool IsNPCBattle() { return battleOn; }

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
	BattleNPC* btNPC = nullptr;
	class Pokemon* NPCPokemon = nullptr;
	int playerPokemonNum;
	int currentPlayerPokemonNum;
	int npcPokemonNum;
	int selectSkill = 0;
	int currentnpcPokemonNum;
	bool playerturn = false;							//플레이어 턴인지 검사 ture시 플레이어턴 false시 적턴
	bool battleover = false;							//전투 종료
	bool textrendering = false;
	float playerHpPer = 1.0;
	float enemyHpPer = 1.0;
	int turncount = 2;
	int enemySelect = 0;
	BattleSequence enemyBattleSeq = Wait;
	BattleSequence* battleSeq = nullptr;

};