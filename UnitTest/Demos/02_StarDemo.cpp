#include "stdafx.h"
#include "02_StarDemo.h"

#include "GeoMetries/Star.h"

void StarDemo::Init()
{
	star = new Star(Vector3(800, 200, 0), Vector3(100, 100, 1), 0.0f);
}

void StarDemo::Destroy()
{
	SAFE_DELETE(star);
}

void StarDemo::Update()
{
	star->Update();
}

void StarDemo::Render()
{
	star->Render();
}

void StarDemo::PostRender()
{
}

void StarDemo::GUI()
{
	star->GUI();
}
