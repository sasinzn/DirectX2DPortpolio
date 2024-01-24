#include "stdafx.h"
#include "08_RectGameDemo.h"

#include "GeoMetries\RectGame.h"

void RectGameDemo::Init()
{
	
	pPlayer = new RectGame({500,500,0}, {100,100,0},0.f);
	pPlayer->SetPlayer();

	// 화면 좌측 생성
	for (int i = 0; i < 8; i++)
	{
		rEnemy.push_back(new RectGame({ (float)(rand() % (WinMaxWidth / 2)) + 100*i, WinMaxHeight , 0 }, { 100, 20, 0 }, i+1.f));
	}
	
}

void RectGameDemo::Destroy()
{
	for (RectGame* r : rEnemy)
		SAFE_DELETE(r);

	SAFE_DELETE(pPlayer);
}

void RectGameDemo::Update()
{
	for (RectGame* r : rEnemy)
		r->Update();

	pPlayer->Update();
	pPlayer->Move();

	for (RectGame* r : rEnemy)
	{
		if (BoundingBox::AABB(pPlayer->GetCollision(), r->GetCollision()) == true ||
			BoundingBox::OBB(pPlayer->GetCollision(), r->GetCollision()) == true)
			r->SetColor(Values::Red);
		else
			r->SetColor(Values::Blue);
	}
	
}

void RectGameDemo::Render()
{
	for (RectGame* r : rEnemy)
		r->Render();

	pPlayer->Render();
}

void RectGameDemo::PostRender()
{
}

void RectGameDemo::GUI()
{

}
