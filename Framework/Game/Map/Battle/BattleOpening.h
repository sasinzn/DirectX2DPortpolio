#pragma once
#include "GeoMetries\TextureRect.h"
#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

class BattleOpening
{
public:
	BattleOpening();
	~BattleOpening();

	void Update();
	void Render();

	bool GetEndPlaying() { return endPlaying; }
	void SetMoving() { moving = true; }
	void Reset();

	void PosMoving();

private:

	TextureRect* BackGround = nullptr;
	TextureRect* BackGroundTp = nullptr;
	TextureRect* BackGroundBt = nullptr;
	TextureRect* Dialog = nullptr;
	
	Animator* animator_Player = nullptr;
	AnimationRect* animRect_Player = nullptr;

	TextureRect* Encounter_NPC = nullptr;
	TextureRect* Encounter_Player = nullptr;

	bool SummonBall = false;
	bool moving = false;
	bool endPlaying = false;
	float deltaTime = 0.f;
	int num = 0;

	Vector3 PlayerPos[10];
	Vector3 NPCPos[10];
};