#include "stdafx.h"
#include "03_TextureDemo.h"

#include "GeoMetries/Rect.h"
#include "GeoMetries/TextureRect.h"

void TextureDemo::Init()
{
	rect = new Rect(Vector3(500, 200, 0), Vector3(100, 100, 1), 0.0f);
	trs.push_back(new TextureRect(Vector3(WinMaxWidth/2, WinMaxHeight/2, 0), Vector3(384, 365, 1), 0.f, TexturePath + L"01_Taecho Town.png"));
}

void TextureDemo::Destroy()
{
	for (TextureRect* r : trs)
		SAFE_DELETE(r);

	SAFE_DELETE(rect);
}

void TextureDemo::Update()
{
	
//	if (Mouse::Get()->Down(0))
//		trs.push_back(new TextureRect(Vector3(0, 0, 0), Vector3(384, 365, 1), 0.f, TexturePath + L"01_Taecho Town.png"));
	for (TextureRect* r : trs)
		r->Update();

	rect->Update();
}

void TextureDemo::Render()
{
	for (TextureRect* r : trs)
		r->Render();

	rect->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
	rect->GUI();
}
