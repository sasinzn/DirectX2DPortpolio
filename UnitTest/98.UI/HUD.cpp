#include "stdafx.h"
#include "HUD.h"

#include "Game\UI\ProgressBar.h"

HUD::HUD()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;
	HP = new ProgressBar({ width, height, 0 }, { 200,30,1 }, 0.0f, Color(1, 0, 0, 1), UI::LEFT_TO_RIGHT);

}

HUD::~HUD()
{
	SAFE_DELETE(HP);
}

void HUD::Update()
{
	if (KEYBOARD->Down(VK_F3))
	{
		percent -= 0.1f;
		HP->UpdateProgressBar(percent);
	}


	HP->Update();
}

void HUD::Render()
{
	HP->Render();
}
