#include "stdafx.h"
#include "07_CollisionDemo.h"

#include "GeoMetries/Rect.h"
#include "GeoMetries\TextureRect.h"


void CollisionDemo::Init()
{
	r1 = new Rect({ 100, 100, 0 }, { 100, 100, 1 }, .0f);
	r2 = new Rect({ 300, 300, 0 }, { 100, 100, 1 }, .0f);
}

void CollisionDemo::Destroy()
{
	SAFE_DELETE(r2);
	SAFE_DELETE(r1);
}

void CollisionDemo::Update()
{
	r1->Update();
	r1->Move();

	r2->Update();

	if (BoundingBox::AABB(r1->GetCollision(), r2->GetCollision()) == true ||
		BoundingBox::OBB(r1->GetCollision(), r2->GetCollision()) == true)
		r2->SetColor(Values::Black);
	else
		r2->SetColor(Values::Blue);
}

void CollisionDemo::Render()
{
	r1->Render();
	r2->Render();
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI()
{
	r2->GUI();
}


/*
void CollisionDemo::Init()
{
	r1 = new Rect({ WinMaxWidth / 2, WinMaxHeight / 2, 0 }, { 33, 33, 1 }, .0f);
	r2 = new Rect({ 300, 300, 0 }, { 100, 100, 1 }, .0f);

	r1->SetColor(Values::Red);
	r2->SetColor(Values::Black);

	map = new Texture2D(TextureMapCityPath + L"test.png");
//	map = new Texture2D(TextureMapCityPath + L"01_TaechoTown.png");
	TaechoTown_01 = new TextureRect(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(map->GetWidth(), map->GetHeight(), 1), 0.f, TextureMapCityPath + L"01_TaechoTown_MASK.png");


	map->ReadPixel(&map->resultPixel);

//	map->ReadPixel(texture, &map->resultPixel);

}

void CollisionDemo::Destroy()
{
	SAFE_DELETE(TaechoTown_01);
	SAFE_DELETE(map);
	SAFE_DELETE(r2);
	SAFE_DELETE(r1);

}

void CollisionDemo::Update()
{
	r1->Update();
	r1->Move();
	r2->Update();

	r1->GetCollision()->UpdateCollisionData();
	r2->GetCollision()->UpdateCollisionData();

	TaechoTown_01->Update();

	if (BoundingBox::AABB(r1->GetCollision(), r2->GetCollision()) == true ||
		BoundingBox::OBB(r1->GetCollision(), r2->GetCollision()) == true)
		r2->SetColor(Values::Black);
	else
		r2->SetColor(Values::Blue);
	int result = 0;

	result = BoundingBox::ColorBounding(r1->GetCollision(), &map->resultPixel, map->GetWidth(), map->GetHeight());



	cout << result << endl;
}

void CollisionDemo::Render()
{
	TaechoTown_01->Render();
	r1->Render();
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI()
{
	r2->GUI();
}


*/
