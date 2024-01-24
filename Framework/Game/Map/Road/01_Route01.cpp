#include "Framework.h"
#include "01_Route01.h"


Route01::Route01()
	:Map({ 640, 1920, 0.f }, { 100,100,0 }, TextureMapRoadPath + L"Route_01.png")
{
	
	srcTex = new Texture2D(TextureMapRoadPath + L"Route_01.png");
	size = { srcTex->GetWidth(),srcTex->GetHeight(),0.f };
	position = { 640, 1920, 0.f };
	srv = srcTex->GetSRV();
	stageName = L"Route_01";
	SetStageRoute(SOUTH, L"01_TaechoTown");
	SetStageRoute(NORTH, L"02_SangRokCity");
	mainMap->SetSize(size);

	// 배틀 지역 충돌박스 생성

	rBound.push_back(new BoundingBox({ 685,1080,0 }, { 90,240,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 330,1200,0 }, { 340,100,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 905,1200,0 }, { 250,100,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 425,1295,0 }, { 330,90,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 1000,1295,0 }, { 240,90,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 785,1600,0 }, { 290,240,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 975,2135,0 }, { 290,230,0 }, 0.f, { 1,0,0,1 }));
	rBound.push_back(new BoundingBox({ 825,2475,0 }, { 590,250,0 }, 0.f, { 1,0,0,1 }));
}

Route01::~Route01()
{
	for (BoundingBox* r : rBound)
		SAFE_DELETE(r);

	SAFE_DELETE(srcTex);
	
	
}

void Route01::Update()
{

	mainMap->Update();
	for (BoundingBox* r : rBound)
	{
		r->Update();
		r->UpdateCollisionData();
	}
	
}

void Route01::Render()
{
	
	mainMap->Render();
	
	for (BoundingBox* r : rBound)
	{
		r->Render();
	}
}

Direction Route01::ChangeMap(Vector3 playerPos)
{
	if (isPlaying)
	{
		if (playerPos.y >= size.y - 20 && playerPos.x >= WinMaxWidth / 2 && playerPos.x < WinMaxWidth / 2 + 100)
			return NORTH;

		if (playerPos.y <= 20 && playerPos.x >= WinMaxWidth - 50 / 2 && playerPos.x < WinMaxWidth / 2)
			return SOUTH;

	}
	else
		return STAY;

}

bool Route01::Battle(BoundingBox* player, bool isBattle)
{
	if(isBattle)
		return false;
	else
	{
		for (BoundingBox* r : rBound)
		{
			if (BoundingBox::AABB(player, r) == true ||
				BoundingBox::OBB(player, r) == true)
			{
				r->SetColor(Values::Black);
				if (rand() % 10 < 2 && deltaTime > 5)
				{
					deltaTime = 0;
					return true;
				}
				else
					deltaTime += TIME->Delta();
			}
			else
			{
				r->SetColor(Values::Blue);
			}

		}
	}
	

	return false;
}
