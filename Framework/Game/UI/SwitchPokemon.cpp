#include "Framework.h"
#include "SwitchPokemon.h"

#include "Game\UI\ProgressBar.h"
#include "../UnitTest/01.Character/Player.h"
#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"
#include "GeoMetries\TextureRect.h"
#include "Game\Actor\Pokemon.h"
#include "Game\UI\HpBar.h"

SwitchPokemon::SwitchPokemon(Player* player)
{
	backGround = new TextureRect({ WinMaxWidth / 2,WinMaxHeight / 2,0.f }, { WinMaxWidth,WinMaxHeight,0.f }, 0.f, TextureMapMenuPath + L"pokemonMenuBG.png");
	// 포켓몬 1번 슬롯 ~ 6번
	pokemon01 = new TextureRect({ 320,620,0.f }, { 630,168,0 }, 0.f, TextureMapMenuPath + L"pokemonlist01.png");
	pokemon02 = new TextureRect({ 960,595,0.f }, { 630,168,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06).png");
	pokemon03 = new TextureRect({ 320,440,0.f }, { 630,168,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06).png");
	pokemon04 = new TextureRect({ 960,410,0.f }, { 630,168,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06).png");
	pokemon05 = new TextureRect({ 320,260,0.f }, { 630,168,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06).png");
	pokemon06 = new TextureRect({ 960,230,0.f }, { 630,168,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06).png");
	// 포켓몬 1번에서 6번 선택
	pokemon01select = new TextureRect({ 320,625,0.f }, { 630,184,0 }, 0.f, TextureMapMenuPath + L"pokemonlist01_select.png");
	pokemon02select = new TextureRect({ 960,600,0.f }, { 630,184,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06)_select.png");
	pokemon03select = new TextureRect({ 320,445,0.f }, { 630,184,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06)_select.png");
	pokemon04select = new TextureRect({ 960,415,0.f }, { 630,184,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06)_select.png");
	pokemon05select = new TextureRect({ 320,265,0.f }, { 630,184,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06)_select.png");
	pokemon06select = new TextureRect({ 960,235,0.f }, { 630,184,0 }, 0.f, TextureMapMenuPath + L"pokemonlist(02~06)_select.png");

	Hp01 = new HpBar({ -320,251,0 }, { 240,15,0 });
	Hp02 = new HpBar({ 320,226,0 }, { 240,15,0 });
	Hp03 = new HpBar({ -320,71,0 }, { 240,15,0 });
	Hp04 = new HpBar({ 320,41,0 }, { 240,15,0 });
	Hp05 = new HpBar({ -320,-109,0 }, { 240,15,0 });
	Hp06 = new HpBar({ 320,-139,0 }, { 240,15,0 });
	playerData = player;

	selectPokemon = 1;
	
	openPokemonMenu = false;
}

SwitchPokemon::~SwitchPokemon()
{
	SAFE_DELETE(Hp06);
	SAFE_DELETE(Hp05);
	SAFE_DELETE(Hp04);
	SAFE_DELETE(Hp03);
	SAFE_DELETE(Hp02);
	SAFE_DELETE(Hp01);
	SAFE_DELETE(pokemon06select);
	SAFE_DELETE(pokemon05select);
	SAFE_DELETE(pokemon04select);
	SAFE_DELETE(pokemon03select);
	SAFE_DELETE(pokemon02select);
	SAFE_DELETE(pokemon01select);
	SAFE_DELETE(pokemon06);
	SAFE_DELETE(pokemon05);
	SAFE_DELETE(pokemon04);
	SAFE_DELETE(pokemon03);
	SAFE_DELETE(pokemon02);
	SAFE_DELETE(pokemon01);
	SAFE_DELETE(backGround);
}

void SwitchPokemon::Update()
{
	backGround->Update();
	pokemon01->Update();
	pokemon02->Update();
	pokemon03->Update();
	pokemon04->Update();
	pokemon05->Update();
	pokemon06->Update();

	pokemon01select->Update();
	pokemon02select->Update();
	pokemon03select->Update();
	pokemon04select->Update();
	pokemon05select->Update();
	pokemon06select->Update();

	Hp01->Update();
	Hp02->Update();
	Hp03->Update();
	Hp04->Update();
	Hp05->Update();
	Hp06->Update(); 

	pokemonNum = playerData->GetPokemonNum();

	HpUpdate();
}

void SwitchPokemon::Render()
{
	if (openPokemonMenu)
	{
		backGround->Render();
		if (pokemonNum <= 6)
			pokemon01->Render();
		if (pokemonNum <= 6 && pokemonNum > 1)
			pokemon02->Render();
		if (pokemonNum <= 6 && pokemonNum > 2)
			pokemon03->Render();
		if (pokemonNum <= 6 && pokemonNum > 3)
			pokemon04->Render();
		if (pokemonNum <= 6 && pokemonNum > 4)
			pokemon05->Render();
		if (pokemonNum >= 6)
			pokemon06->Render();

		if (selectPokemon == 1)
			pokemon01select->Render();
		else if (selectPokemon == 2)
			pokemon02select->Render();
		else if (selectPokemon == 3)
			pokemon03select->Render();
		else if (selectPokemon == 4)
			pokemon04select->Render();
		else if (selectPokemon == 5)
			pokemon05select->Render();
		else if (selectPokemon == 6)
			pokemon06select->Render();

		if (pokemonNum <= 6)
			Hp01->Render();
		if (pokemonNum <= 6 && pokemonNum > 1)
			Hp02->Render();
		if (pokemonNum <= 6 && pokemonNum > 2)
			Hp03->Render();
		if (pokemonNum <= 6 && pokemonNum > 3)
			Hp04->Render();
		if (pokemonNum <= 6 && pokemonNum > 4)
			Hp05->Render();
		if (pokemonNum >= 6)
			Hp06->Render();

		PokemonInfoRender();
	}

}

void SwitchPokemon::PokemonInfoRender()
{
	Text::Get()->BeginDraw();
	{
		wstring pokemonName01 = String::ToWString(playerData->GetPokemonInfo(1)->GetPKData().name);
		wstring pokemonLevel01 = to_wstring(playerData->GetPokemonInfo(1)->GetPKData().level);
		wstring pokemonMaxHp01 = to_wstring(playerData->GetPokemonInfo(1)->GetPKData().maxHp);
		wstring pokemonCurrentHp01 = to_wstring(playerData->GetPokemonInfo(1)->GetPKData().currentHp);
		float sizeName = (float)Text::Get()->GetStringWidth(L"울트라네크로즈마", 4.0f);
		float sizeNum = (float)Text::Get()->GetStringWidth(L"1000", 10.0f);
		Vector2 posName01 = Vector2(390, 43);
		Vector2 posLevel01 = Vector2(110, 130);
		Vector2 posMaxHp01 = Vector2(480, 130);
		Vector2 posCurrenHp01 = Vector2(350, 130);
		Text::Get()->RenderText(pokemonName01, posName01, Color(255, 255, 255, 1), sizeName, false);
		Text::Get()->RenderText(pokemonLevel01, posLevel01, Color(255, 255, 255, 1), sizeNum, false);
		Text::Get()->RenderText(pokemonMaxHp01, posMaxHp01, Color(255, 255, 255, 1), sizeNum, false);
		Text::Get()->RenderText(pokemonCurrentHp01, posCurrenHp01, Color(255, 255, 255, 1), sizeNum, false);

		if (pokemonNum >= 2)
		{
			wstring pokemonName02 = String::ToWString(playerData->GetPokemonInfo(2)->GetPKData().name);
			wstring pokemonLevel02 = to_wstring(playerData->GetPokemonInfo(2)->GetPKData().level);
			wstring pokemonMaxHp02 = to_wstring(playerData->GetPokemonInfo(2)->GetPKData().maxHp);
			wstring pokemonCurrentHp02 = to_wstring(playerData->GetPokemonInfo(2)->GetPKData().currentHp);
			float sizeName = (float)Text::Get()->GetStringWidth(L"울트라네크로즈마", 4.0f);
			float sizeNum = (float)Text::Get()->GetStringWidth(L"1000", 10.0f);
			Vector2 posName02 = Vector2(1050, 70);
			Vector2 posLevel02 = Vector2(750, 155);
			Vector2 posMaxHp02 = Vector2(1130, 155);
			Vector2 posCurrenHp02 = Vector2(1000, 155);
			Text::Get()->RenderText(pokemonName02, posName02, Color(255, 255, 255, 1), sizeName, false);
			Text::Get()->RenderText(pokemonLevel02, posLevel02, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonMaxHp02, posMaxHp02, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonCurrentHp02, posCurrenHp02, Color(255, 255, 255, 1), sizeNum, false);
		}

		if (pokemonNum >= 3)
		{
			wstring pokemonName03 = String::ToWString(playerData->GetPokemonInfo(3)->GetPKData().name);
			wstring pokemonLevel03 = to_wstring(playerData->GetPokemonInfo(3)->GetPKData().level);
			wstring pokemonMaxHp03 = to_wstring(playerData->GetPokemonInfo(3)->GetPKData().maxHp);
			wstring pokemonCurrentHp03 = to_wstring(playerData->GetPokemonInfo(3)->GetPKData().currentHp);
			float sizeName = (float)Text::Get()->GetStringWidth(L"울트라네크로즈마", 4.0f);
			float sizeNum = (float)Text::Get()->GetStringWidth(L"1000", 10.0f);
			Vector2 posName03 = Vector2(390, 223);
			Vector2 posLevel03 = Vector2(110, 310);
			Vector2 posMaxHp03 = Vector2(480, 310);
			Vector2 posCurrenHp03 = Vector2(350, 310);
			Text::Get()->RenderText(pokemonName03, posName03, Color(255, 255, 255, 1), sizeName, false);
			Text::Get()->RenderText(pokemonLevel03, posLevel03, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonMaxHp03, posMaxHp03, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonCurrentHp03, posCurrenHp03, Color(255, 255, 255, 1), sizeNum, false);
		}

		if (pokemonNum >= 4)
		{
			wstring pokemonName04 = String::ToWString(playerData->GetPokemonInfo(4)->GetPKData().name);
			wstring pokemonLevel04 = to_wstring(playerData->GetPokemonInfo(4)->GetPKData().level);
			wstring pokemonMaxHp04 = to_wstring(playerData->GetPokemonInfo(4)->GetPKData().maxHp);
			wstring pokemonCurrentHp04 = to_wstring(playerData->GetPokemonInfo(4)->GetPKData().currentHp);
			float sizeName = (float)Text::Get()->GetStringWidth(L"울트라네크로즈마", 4.0f);
			float sizeNum = (float)Text::Get()->GetStringWidth(L"1000", 10.0f);
			Vector2 posName04 = Vector2(1050, 250);
			Vector2 posLevel04 = Vector2(750, 335);
			Vector2 posMaxHp04 = Vector2(1130, 335);
			Vector2 posCurrenHp04 = Vector2(1000, 335);
			Text::Get()->RenderText(pokemonName04, posName04, Color(255, 255, 255, 1), sizeName, false);
			Text::Get()->RenderText(pokemonLevel04, posLevel04, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonMaxHp04, posMaxHp04, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonCurrentHp04, posCurrenHp04, Color(255, 255, 255, 1), sizeNum, false);
		}

		if (pokemonNum >= 5)
		{
			wstring pokemonName05 = String::ToWString(playerData->GetPokemonInfo(5)->GetPKData().name);
			wstring pokemonLevel05 = to_wstring(playerData->GetPokemonInfo(5)->GetPKData().level);
			wstring pokemonMaxHp05 = to_wstring(playerData->GetPokemonInfo(5)->GetPKData().maxHp);
			wstring pokemonCurrentHp05 = to_wstring(playerData->GetPokemonInfo(5)->GetPKData().currentHp);
			float sizeName = (float)Text::Get()->GetStringWidth(L"울트라네크로즈마", 4.0f);
			float sizeNum = (float)Text::Get()->GetStringWidth(L"1000", 10.0f);
			Vector2 posName05 = Vector2(390, 403);
			Vector2 posLevel05 = Vector2(110, 490);
			Vector2 posMaxHp05 = Vector2(480, 490);
			Vector2 posCurrenHp05 = Vector2(350, 490);
			Text::Get()->RenderText(pokemonName05, posName05, Color(255, 255, 255, 1), sizeName, false);
			Text::Get()->RenderText(pokemonLevel05, posLevel05, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonMaxHp05, posMaxHp05, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonCurrentHp05, posCurrenHp05, Color(255, 255, 255, 1), sizeNum, false);
		}

		if (pokemonNum >= 6)
		{
			wstring pokemonName06 = String::ToWString(playerData->GetPokemonInfo(6)->GetPKData().name);
			wstring pokemonLevel06 = to_wstring(playerData->GetPokemonInfo(6)->GetPKData().level);
			wstring pokemonMaxHp06 = to_wstring(playerData->GetPokemonInfo(6)->GetPKData().maxHp);
			wstring pokemonCurrentHp06 = to_wstring(playerData->GetPokemonInfo(6)->GetPKData().currentHp);
			float sizeName = (float)Text::Get()->GetStringWidth(L"울트라네크로즈마", 4.0f);
			float sizeNum = (float)Text::Get()->GetStringWidth(L"1000", 10.0f);
			Vector2 posName06 = Vector2(1050, 430);
			Vector2 posLevel06 = Vector2(750, 515);
			Vector2 posMaxHp06 = Vector2(1130, 515);
			Vector2 posCurrenHp06 = Vector2(1000, 515);
			Text::Get()->RenderText(pokemonName06, posName06, Color(255, 255, 255, 1), sizeName, false);
			Text::Get()->RenderText(pokemonLevel06, posLevel06, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonMaxHp06, posMaxHp06, Color(255, 255, 255, 1), sizeNum, false);
			Text::Get()->RenderText(pokemonCurrentHp06, posCurrenHp06, Color(255, 255, 255, 1), sizeNum, false);
		}
		
	}
	Text::Get()->EndDraw();
}

void SwitchPokemon::HpUpdate()
{
	// no.1
	float playerCurrntHP01 = (float)(playerData->GetPokemonInfo(1)->GetPKData().currentHp);
	float playerMaxHP01 = (float)(playerData->GetPokemonInfo(1)->GetPKData().maxHp);

	HpPercent01 = playerCurrntHP01 / playerMaxHP01;
	Hp01->SetPercent(HpPercent01);
	// no.2
	if (pokemonNum >= 2)
	{
		float playerCurrntHP02 = (float)(playerData->GetPokemonInfo(2)->GetPKData().currentHp);
		float playerMaxHP02 = (float)(playerData->GetPokemonInfo(2)->GetPKData().maxHp);

		HpPercent02 = playerCurrntHP02 / playerMaxHP02;
		Hp02->SetPercent(HpPercent02);
	}

	// no.3
	if (pokemonNum >= 3)
	{
		float playerCurrntHP03 = (float)(playerData->GetPokemonInfo(3)->GetPKData().currentHp);
		float playerMaxHP03 = (float)(playerData->GetPokemonInfo(3)->GetPKData().maxHp);

		HpPercent03 = playerCurrntHP03 / playerMaxHP03;
		Hp03->SetPercent(HpPercent03);
	}

	// no.4
	if (pokemonNum >= 4)
	{
		float playerCurrntHP04 = (float)(playerData->GetPokemonInfo(4)->GetPKData().currentHp);
		float playerMaxHP04 = (float)(playerData->GetPokemonInfo(4)->GetPKData().maxHp);

		HpPercent04 = playerCurrntHP04 / playerMaxHP04;
		Hp04->SetPercent(HpPercent04);
	}

	// no.5
	if (pokemonNum >= 5)
	{
		float playerCurrntHP05 = (float)(playerData->GetPokemonInfo(5)->GetPKData().currentHp);
		float playerMaxHP05 = (float)(playerData->GetPokemonInfo(5)->GetPKData().maxHp);

		HpPercent05 = playerCurrntHP05 / playerMaxHP05;
		Hp05->SetPercent(HpPercent05);
	}

	// no.6
	if (pokemonNum >= 6)
	{
		float playerCurrntHP06 = (float)(playerData->GetPokemonInfo(6)->GetPKData().currentHp);
		float playerMaxHP06 = (float)(playerData->GetPokemonInfo(6)->GetPKData().maxHp);

		HpPercent06 = playerCurrntHP06 / playerMaxHP06;
		Hp06->SetPercent(HpPercent06);
	}



}