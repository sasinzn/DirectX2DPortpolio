#include "stdafx.h"
#include "04_ShadedDemo.h"

#include "GeoMetries/TextureRect.h"
#include "GeoMetries/ShadedTexture.h"

void ShadedDemo::Init()
{
	st = new ShadedTexture(Vector3(620, 360, 0), Vector3(500, 500, 1), .0f, TexturePath + L"asdf.jpg");
	st->SetShader(ShaderPath + L"TextureFilter.hlsl");
}

void ShadedDemo::Destroy()
{
	SAFE_DELETE(st);
}

void ShadedDemo::Update()
{
	st->Update();
}

void ShadedDemo::Render()
{
	st->Render();
}

void ShadedDemo::PostRender()
{
}

void ShadedDemo::GUI()
{
	st->GUI();
}
