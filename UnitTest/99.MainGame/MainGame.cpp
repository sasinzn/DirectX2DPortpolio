#include "stdafx.h"
#include "MainGame.h"

#include "01.Character/Player.h"
#include "02.Map/MainMap.h"


void MainGame::Init()
{
	map = new MainMap;
	map->Init();

	

	
}

void MainGame::Destroy()
{

	SAFE_DELETE(map);
}

void MainGame::Update()
{
	map->Update();
	
//	cout << "X : " << player->GetPos().x << "Y : " << player->GetPos().y << endl;

	
}

void MainGame::Render()
{
	map->Render();
	
}

void MainGame::PostRender()
{
}

void MainGame::GUI()
{
}
