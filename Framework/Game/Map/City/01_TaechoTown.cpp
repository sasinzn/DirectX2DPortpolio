#include "Framework.h"
#include "01_TaechoTown.h"

TaechoTown::TaechoTown()
	:Map({640, 480, 0.f },{100,100,0}, TextureMapCityPath + L"01_TaechoTown.png")
{
	// 태초마을
	srcTex = new Texture2D(TextureMapCityPath + L"01_TaechoTown.png");
	size = { srcTex->GetWidth(),srcTex->GetHeight(),0.f };
	position = { 640, 480, 0.f };
	srv = srcTex->GetSRV();
	stageName = L"01_TaechoTown";
	SetStageRoute(NORTH, L"Route_01");
	SetStageRoute(SOUTH, L"Route_21");
	mainMap->SetSize(size);
}

TaechoTown::~TaechoTown()
{
	SAFE_DELETE(srcTex);
}

void TaechoTown::Update()
{

	
	mainMap->Update();
	
	
}

void TaechoTown::Render()
{
	
	mainMap->Render();
	
}



Direction TaechoTown::ChangeMap(Vector3 playerPos)
{
	if (isPlaying)
	{
		if (playerPos.y >= size.y - 100 && playerPos.x >= WinMaxWidth / 2 && playerPos.x < WinMaxWidth / 2 + 100)
			return NORTH;

		if (playerPos.y <= WinMaxHeight/2 - size.y/2 + 100 && playerPos.x >= WinMaxWidth - 50 / 2 && playerPos.x < WinMaxWidth / 2)
			return SOUTH;
	}
	else
		return STAY;
	
}
