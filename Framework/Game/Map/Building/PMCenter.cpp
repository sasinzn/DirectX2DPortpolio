#include "Framework.h"
#include "PMCenter.h"

PMCenter::PMCenter()
	:Map({ 2500, 3840, 0.f }, { 100,100,0 }, TextureMapCityPath + L"PMCenterFloor1.png")
{
	// 포켓몬 센터
	srcTex = new Texture2D(TextureMapCityPath + L"PMCenterFloor1.png");
	size = { srcTex->GetWidth(),srcTex->GetHeight(),0.f };
	position = { 2500, 3840, 0.f };
	srv = srcTex->GetSRV();
	stageName = L"PMCenterFloor1";
	mainMap->SetSize(size);
	
	bGate.push_back(new BoundingBox({ 2500,3600,0 }, { 50,50,0 }, 0.f, { 1,0,0,1 })); // 입구
}

PMCenter::~PMCenter()
{
	SAFE_DELETE(srcTex);
}

void PMCenter::Update()
{


	mainMap->Update();

	for (BoundingBox* r : bGate)
	{
		r->Update();
		r->UpdateCollisionData();
	}
}

void PMCenter::Render()
{

	mainMap->Render();

	for (BoundingBox* r : bGate)
	{
		r->Render();
	}
}

bool PMCenter::OutPmc(BoundingBox* player)
{
	for (BoundingBox* r : bGate)
	{
		if (BoundingBox::AABB(player, r) == true ||
			BoundingBox::OBB(player, r) == true)
		{
			r->SetColor(Values::Black);
			if (deltaTime > 2)
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



Direction PMCenter::ChangeMap(Vector3 playerPos)
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
