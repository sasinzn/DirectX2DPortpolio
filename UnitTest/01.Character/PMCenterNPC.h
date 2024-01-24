#pragma once

#include "Game/Actor/Character.h"
#include "Game\UI\ProgressBar.h"
#include "GeoMetries\TextureRect.h"





class PMCenterNPC : public Character
{
public:
	PMCenterNPC(Vector3 position, Vector3 size);
	~PMCenterNPC();

	virtual void Update() override;
	virtual void Render() override;

	Vector3 GetPos() { return animRect->GetPosition(); }
	BoundingBox* GetCollision() { return collision; }
	bool InterActionNPC(BoundingBox* player);
	void Question();
	void Reset();
	
	void SetHold() { holding = true; }
	void SetMove() { holding = false; }


private:
	BoundingBox* collision;
	class ProgressBar* select = nullptr;		// 선택창 Y or N
	class ProgressBar* dialog = nullptr;		// 기본 인사창
	class ProgressBar* dialogN1 = nullptr;		// 선택창에서 N 선택시
	class ProgressBar* dialogY1 = nullptr;		// 선택창에서 Y 선택시
	class ProgressBar* dialogY2 = nullptr;		// Y선택후 일정시간후
	class ProgressBar* dialogY3 = nullptr;		// Y선택후 일정시간후
	class ProgressBar* selectN = nullptr;		// N선택 화살표
	class ProgressBar* selectY = nullptr;		// Y선택 화살표
	class TextureRect* monsterBall1 = nullptr;
	class TextureRect* monsterBall2 = nullptr;
	class TextureRect* monsterBall3 = nullptr;
	class TextureRect* monsterBall4 = nullptr;
	class TextureRect* monsterBall5 = nullptr;
	class TextureRect* monsterBall6 = nullptr;
	class TextureRect* ballLight = nullptr;



	bool holding;								// 플레이어 이동불가 판별
	bool interaction;	// NPC상호작용 여부
	bool textrending;	// 텍스트 출력 여부
	bool healing;		// 체력회복 여부
	int textnum;		// 텍스트 순서
	bool selectArrow;	// 선택화살표
	bool selectHealing;	// 회복 선택
	float deltatime;

};
