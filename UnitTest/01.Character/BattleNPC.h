#pragma once

#include "Game/Actor/Character.h"
#include "Game\Actor\Pokemon.h"


class BattleNPC : public Character
{
public:
	BattleNPC(Vector3 position, Vector3 size);
	~BattleNPC();

	virtual void Update() override;
	virtual void Render() override;

	Vector3 GetPos() { return animRect->GetPosition(); }
	Direction GetDir() { return npcDir; }
	BoundingBox* GetCollision() { return collision; }
	Pokemon* GetcurrentPokemon() { return currentBattlePokemon; }
	Pokemon* GetPokemon(int indexNum) { return pPokemon[indexNum - 1]; }
	void SetcurrentPokemon(int indexNum) { currentBattlePokemon = pPokemon[indexNum-1]; }
	int GetPokemonNum() { return pPokemon.size(); }
	bool InterActionNPC(BoundingBox* player);
	void SetNPC(int NPCindexNum, Direction dir);

	void SetHold() { holding = true; }
	void SetMove() { holding = false; }
	void SetInterActionOFF() { activeNPC = false; interaction = false; }
	void AddPokemon();


private:
	BoundingBox* collision;
	vector<Pokemon*> pPokemon;
	Pokemon* currentBattlePokemon = nullptr;
	bool holding;								// 플레이어 이동불가 판별
	bool interaction;
	bool activeNPC;
	float deltaTime;
	Direction npcDir;
	Vector3 pos;
	wstring npcU[8];
	wstring npcD[8];
	wstring npcL[8];
	wstring npcR[8];
};
