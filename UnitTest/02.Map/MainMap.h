#pragma once

#pragma region City include
#include "Game/Map/City/01_TaechoTown.h"
#include "Game/Map/City/02_SangrokCity.h"
#include "Game/Map/Building/PMCenter.h"

#pragma endregion


#pragma region Road include
#include "Game/Map/Road/01_Route01.h"

#pragma endregion

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"
#include "01.Character\Player.h"
#include "01.Character/PMCenterNPC.h"
#include "01.Character/BattleNPC.h"
#include "Game\Map\Battle\Battle.h"
#include "Game/Map/Battle/NPCBattle.h"
#include "Game\Actor\Pokemon.h"
#include "Game\Item\PokeBall.h"
#include "Game/Menu/ItemBag.h"
#include "Game/Map/Battle/BattleOpening.h"


class MainMap : public IObject
{
public:
	virtual void Init()	override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

	bool CurrentBattleZone(BoundingBox* player);
	void MovingPMC(BoundingBox* player);
	void InteractionNPC(BoundingBox* player);
	void CameraMove();
	void BattleWithNPC();

private:
	TaechoTown* taechoTown = nullptr;
	SangrokCity* sangrokCity = nullptr;
	PMCenter* pmCenter = nullptr;
	Route01* route01 = nullptr;
	Battle* battle = nullptr;
	NPCBattle* npcBattle = nullptr;
	class Player* player = nullptr;
	class PMCenterNPC* pmcNPC = nullptr;
	class BattleNPC* battleNPC1 = nullptr;
	BattleOpening* npcBattleOp = nullptr;
//	vector<class BattleNPC*> battleNPCList;
	Pokemon* enemyPm = nullptr;

	class PokeBall* ball = nullptr;
	class ItemBag* bagpack = nullptr;

	Animator* animator = nullptr;
	AnimationRect* animRect = nullptr;
};


