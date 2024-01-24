#include "stdafx.h"
#include "09_AnimationDemo.h"

#include "GeoMetries/TextureRect.h"
#include "GeoMetries/AnimationRect.h"

void AnimationDemo::Init()
{
	ar = new AnimationRect({ 720,360,0 }, { 200,200,1 });
}

void AnimationDemo::Destroy()
{
	SAFE_DELETE(ar);
}

void AnimationDemo::Update()
{
	ar->Update();
}

void AnimationDemo::Render()
{
	ar->Render();
}

void AnimationDemo::PostRender()
{
}

void AnimationDemo::GUI()
{
}
