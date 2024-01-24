#pragma once

#include "Game/Actor/Character.h"
#include "Game\Actor\Pokemon.h"
#include "Game/Item/Item.h"
#include "Game/UI/SwitchPokemon.h"

class Player : public Character
{
public:
	Player(Vector3 position, Vector3 size);
	~Player();

	virtual void Update() override;
	virtual void Render() override;

	Vector3 GetPos() { return animRect->GetPosition(); }
	BoundingBox* GetCollision() { return collision; }
	Pokemon* GetcurrentPokemon() { return currentBattlePokemon; }
	int GetPokemonNum() { return pPokemon.size(); }
	Item* GetPlayerItem() { return playerItem; }
	SwitchPokemon* GetPokemonMenu() { return pokemonMenu; }
	bool GetBattle() { return battleOn; }
	bool GetNPCBattle() { return npcBattleOn; }
	void SetHold() { holding = true; }
	void SetMove() { holding = false; }
	void SetBattle() { battleOn = true; }
	void SetBattelEnd() { battleOn = false; }
	void SetNPCBattle() { npcBattleOn = true; }
	void SetNPCBattleEnd() { npcBattleOn = false; }
	void SetOpenPokemonMenu() { openPokemonMenu = true; }
	void SetClosePokemonMenu() { openPokemonMenu = false; }
	void SetOpenItemMenu() { openItemMenu = true; }
	void SetCloseItemMenu() { openItemMenu = false; }
	void SetBattleSeq(BattleSequence seq) { battleSeq = seq; }
	BattleSequence* GetBattleSeq() { return &battleSeq; }
	bool GetPokemonMenuOpen() { return openPokemonMenu; }
	bool GetItemMenuOpen() { return openItemMenu; }
	MenuTree* GetMenuTree() { return &menuTree; }
	int* GetSpaceCount() { return &spaceCount; }
	void SetSpaceCountReset() { spaceCount = 0; }
	void SetMenuTree(MenuTree menu) { menuTree = menu; }
	void SetSwitchPokemon(int pokemonindexNum) { currentBattlePokemon = pPokemon[pokemonindexNum-1]; }
	void GotchaPokemon(int indexNum, int level, int currentHP);
	void AddPokemon(int indexNum, int level);
	void AllPokemonHealing();
	void EnterPMCenter() { enterPMCenter = true; }
	void OutPMCenter() { enterPMCenter = false; }
	bool GetVisitPMC() { return enterPMCenter; }
	void UsingItem(int PokemonIndexNum, int ItemindexNum);
	void ResetUsingItem() { usingitem = false; }
	void SetCollisionDirection(Direction dir) { coldir = dir; }
	void Revolution();
	
	Pokemon* GetPokemonInfo(int indexNum) { return pPokemon[indexNum - 1]; }
private:
	BoundingBox* collision;
	bool holding;								// 플레이어 이동불가 판별
	bool battleOn = false;						// 야생 포켓몬배틀중인지 판별
	bool openPokemonMenu = false;				// 포켓몬 교체 메뉴 열림 판별
	bool openItemMenu = false;					// 아이템 가방 열림 판별
	bool enterPMCenter = false;
	bool npcBattleOn = false;
	Pokemon* currentBattlePokemon = nullptr;
	vector<Pokemon*> pPokemon;
	class Item* playerItem = nullptr;
	class SwitchPokemon* pokemonMenu = nullptr;
	MenuTree menuTree = TopMenu;				// 메뉴트리 위치
	bool usingitem = false;
	
	int spaceCount = 0;							// 스페이스 누른 횟수
	BattleSequence battleSeq = Wait;
	Direction coldir = STAY;						// 충돌방향 
};
