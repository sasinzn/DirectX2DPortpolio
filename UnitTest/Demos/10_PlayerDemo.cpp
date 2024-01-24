#include "stdafx.h"
#include "10_PlayerDemo.h"

#include "01.Character/Player.h"
#include "98.UI\HUD.h"

void PlayerDemo::Init()
{
	player = new Player({ 100,100,0 }, { 100,100,1 });
	hud = new HUD;
//	Sounds::Get()->AddSound("BGM", SoundPath + L"lego.mp3");
//	Sounds::Get()->Play("BGM", 0.3f);

	
}

void PlayerDemo::Destroy()
{
	SAFE_DELETE(hud);
	SAFE_DELETE(player);
}

void PlayerDemo::Update()
{
	player->Update();
	hud->Update();

	auto key = Keyboard::Get();

	if (key->Down(VK_F2))
	{
		if (!Sounds::Get()->IsPaused("BGM"))
			Sounds::Get()->Pause("BGM");
		else
			Sounds::Get()->Resume("BGM");
	}
}

void PlayerDemo::Render()
{
	player->Render();
	hud->Render();
}

void PlayerDemo::PostRender()
{
	Text::Get()->BeginDraw();
	{
		wstring str = L"Å×½ºÆ® TEST &%";
		float size = (float)Text::Get()->GetStringWidth(str, 3.0f);
		Vector2 pos = Vector2(0, 0);
		Text::Get()->RenderText(str, pos, Color(1, 0, 1, 1), size, false);
	}
	Text::Get()->EndDraw();
}

void PlayerDemo::GUI()
{
}
