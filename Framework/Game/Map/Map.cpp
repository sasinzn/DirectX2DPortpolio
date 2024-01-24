#include "Framework.h"
#include "Map.h"

Map::Map(Vector3 position, Vector3 size, wstring path)
{
	mainMap = new TextureRect(position, size, 0.f, path);
}

Map::~Map()
{
	SAFE_DELETE(mainMap);
}

wstring Map::GetStageRoute(int dir)
{
	if (isNextStage[dir])
		return nextStage[dir];

	return L"";
}

void Map::MovePMCenter(Character* player)
{
	player->SetCurrentPos();
	player->SetPos({ 2500,3660,0 });
	
}

void Map::MoveReRoll(Character* player)
{
	player->SetPos(player->GetCurrnetPos() - Vector3(0,50,0));
}
