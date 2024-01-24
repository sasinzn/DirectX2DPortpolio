#pragma once

#include "GeoMetries/TextureRect.h"
#include "GeoMetries/Rect.h"
#include "Utilities\BoundingBox.h"
#include "Game/Actor/Character.h"


class Map
{
public:
	Map(Vector3 position, Vector3 size, wstring path);
	virtual ~Map();

	virtual void Update() = 0;
	virtual void Render() = 0;

	wstring GetStageRoute(int dir);
	Vector3 GetSize() { return size; }
	Vector3 GetPos() { return position; }
	Vector3* GetPosRef() { return &position; }
	wstring GetStageName() { return stageName; }
	bool GetPlaying() { return isPlaying; }
	bool GetMapChange() { return isMapChange; }
	vector<class BoundingBox*> GetBattleZone() { return rBound; }
	vector<class BoundingBox*> GetMoveZone() { return bGate; }
	void MovePMCenter(class Character* player);
	void MoveReRoll(class Character* player);

	bool ISStageRoute(int dir) { return isNextStage[dir]; }
	void SetStageRoute(int dir, wstring stageName) { isNextStage[dir] = true; nextStage[dir] = stageName; }
	void SetPlaying() { if (!isPlaying) isPlaying = true; }
	void SetNonPlaying() { if (isPlaying) isPlaying = false; }
	void SetMapChange() { if (!isMapChange) isMapChange = true; }
	void SetNonChange() { if (isMapChange) isMapChange = false; }
	void SetPos(Vector3 pos) { mainMap->SetPosition(pos); this->position = pos; }

protected:
	TextureRect* mainMap;
	wstring stageName = L"";
	Vector3 position;
	Vector3 size;
	wstring nextStage[4] = { L" " };
	bool isNextStage[4] = { false };
	bool isPlaying = false;
	bool isMapChange = false;
	vector<class BoundingBox*> rBound;
	vector<class BoundingBox*> bGate;
	float deltaTime = 0;
};