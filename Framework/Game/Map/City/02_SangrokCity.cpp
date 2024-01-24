#include "Framework.h"
#include "02_SangrokCity.h"

SangrokCity::SangrokCity()
	:Map({ 665, 3840, 0.f }, { 100,100,0 }, TextureMapCityPath + L"02_SangRokCity.png")
{
	// 상록시티
	srcTex = new Texture2D(TextureMapCityPath + L"02_SangRokCity.png");
	size = { srcTex->GetWidth(),srcTex->GetHeight(),0.f };
	position = { 665, 3840, 0.f };
	srv = srcTex->GetSRV();
	stageName = L"02_SangRokCity";
	SetStageRoute(WEST, L"Route_22");
	SetStageRoute(NORTH, L"Route_02");
	SetStageRoute(SOUTH, L"Route_01");
	mainMap->SetSize(size);

	// 포켓몬 센터
	rBound.push_back(new BoundingBox({ 759,3635,0 }, { 230,170,0 }, 0.f, { 1,0,0,1 }));
	bGate.push_back(new BoundingBox({ 759,3525,0 }, { 50,50,0 }, 0.f, { 1,0,0,1 })); // 입구

}

SangrokCity::~SangrokCity()
{
	SAFE_DELETE(srcTex);
}

void SangrokCity::Update()
{


	mainMap->Update();
	for (BoundingBox* r : rBound)
	{
		r->Update();
		r->UpdateCollisionData();
	}

	for (BoundingBox* r : bGate)
	{
		r->Update();
		r->UpdateCollisionData();
	}
}

void SangrokCity::Render()
{

	mainMap->Render();

	for (BoundingBox* r : rBound)
	{
		r->Render();
	}
	for (BoundingBox* r : bGate)
	{
		r->Render();
	}
}

bool SangrokCity::MovingPMC(BoundingBox* player)
{
	for (BoundingBox* r : bGate)
	{
		if (BoundingBox::AABB(player, r) == true ||
			BoundingBox::OBB(player, r) == true)
		{
			r->SetColor(Values::Black);
			if ( deltaTime > 2)
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
		

	return false;
}



Direction SangrokCity::ChangeMap(Vector3 playerPos)
{
	if (isPlaying)
	{
		if (playerPos.y >= size.y - 100 && playerPos.x >= WinMaxWidth / 2 && playerPos.x < WinMaxWidth / 2 + 100)
			return NORTH;

		if (playerPos.y <= WinMaxHeight / 2 - size.y / 2 + 100 && playerPos.x >= WinMaxWidth - 50 / 2 && playerPos.x < WinMaxWidth / 2)
			return SOUTH;
	}
	else
		return STAY;

}
