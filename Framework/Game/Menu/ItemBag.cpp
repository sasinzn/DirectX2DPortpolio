#include "Framework.h"
#include "ItemBag.h"

#include "../UnitTest/01.Character/Player.h"
#include "GeoMetries\TextureRect.h"
#include "Game/Item/PokeBall.h"
#include "Game/Item/HealingItem.h"
#include "Game/Item/KeyItem.h"
#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"
#include "Game/UI/SwitchPokemon.h"

ItemBag::ItemBag(Player* player)
{
	backGround = new TextureRect({ WinMaxWidth / 2,WinMaxHeight / 2,0.f }, { WinMaxWidth,WinMaxHeight,0.f }, 0.f, TextureMapMenuPath + L"BagBG.png");
	bagLeft = new TextureRect({ 220,420,0 }, { 300,300,0 }, 0.f, TextureMapMenuPath + L"BagLeft.png");
	bagCenter = new TextureRect({ 220,420,0 }, { 300,300,0 }, 0.f, TextureMapMenuPath + L"BagCenter.png");
	bagRight = new TextureRect({ 220,420,0 }, { 300,300,0 }, 0.f, TextureMapMenuPath + L"BagRight.png");
	bagMenuItem = new TextureRect({ 222,650,0 }, { 411,131,0 }, 0.f, TextureMapMenuPath + L"BagMenu_Item.png");
	bagMenuKeyItem = new TextureRect({ 222,650,0 }, { 411,131,0 }, 0.f, TextureMapMenuPath + L"BagMenu_KeyItem.png");
	bagMenuPokeball = new TextureRect({ 222,650,0 }, { 411,131,0 }, 0.f, TextureMapMenuPath + L"BagMenu_Pokeball.png");

	selectItem1 = new TextureRect({ 500,640,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png");
	selectItem2 = new TextureRect({ 500,570,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png");
	selectItem3 = new TextureRect({ 500,500,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png");
	selectItem4 = new TextureRect({ 500,430,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png");
	selectItem5 = new TextureRect({ 500,360,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png");
	selectItem6 = new TextureRect({ 500,290,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png");
	
	playerData = player;
	balls = playerData->GetPlayerItem()->GetPokeballs();
	pokemonMenu = new SwitchPokemon(player);

	animator = new Animator();
	animRect = new AnimationRect({ 110,110,0 }, { 150,150,0 });
	animator->AddAnimClip(balls->GetBallClip());
	animator->AddAnimClip(playerData->GetPlayerItem()->GetHealingItems()->GetHealingItemClip());
	animator->AddAnimClip(playerData->GetPlayerItem()->GetKeyItems()->GetKeyitemClip());
	animator->SetLoopOff();
	animator->SetAniOff();
	animator->SetCurrentAnimClip(L"PokeBallClip");
	animRect->SetAnimation(animator);
}

ItemBag::~ItemBag()
{
	SAFE_DELETE(pokemonMenu);
	SAFE_DELETE(bagMenuPokeball);
	SAFE_DELETE(bagMenuKeyItem);
	SAFE_DELETE(bagMenuItem);
	SAFE_DELETE(bagRight);
	SAFE_DELETE(bagCenter);
	SAFE_DELETE(bagLeft);
	SAFE_DELETE(backGround);
}

void ItemBag::Update()
{
	backGround	   ->Update();
	bagLeft		   ->Update();
	bagCenter 	   ->Update();
	bagRight 	   ->Update();
	bagMenuItem    ->Update();
	bagMenuKeyItem ->Update();
	bagMenuPokeball->Update();

	selectItem1->Update();
	selectItem2->Update();
	selectItem3->Update();
	selectItem4->Update();
	selectItem5->Update();
	selectItem6->Update();

	animator->Update();
	animRect->Update();
	pokemonMenu->Update();

	if (playerData->GetItemMenuOpen())
	{
		
		PickMenu();
		if (currentMenu == BagPokeBalls)
		{
			pokeBallIndexNo = selectIndexNo + pokeBallindexCount;
			animator->SetCurrentAnimClip(L"PokeBallClip");
			animator->SetFrame(pokeBallIndexNo - 1);
		}
		else if (currentMenu == BagItem)
		{
			healingItemIndexNo = selectIndexNo + healingItemindexCount;
			animator->SetCurrentAnimClip(L"healingItemClip");
			animator->SetFrame(healingItemIndexNo - 1);
		}
		else if (currentMenu == BagKeyItem)
		{
			keyItemIndexNo = selectIndexNo + keyItemindexCount;
			animator->SetCurrentAnimClip(L"KeyitemClip");
			animator->SetFrame(keyItemIndexNo - 1);
		}
			
	}
	if (balls->BallGotCha())
		playerData->SetBattleSeq(GotchaPokemon);
}

void ItemBag::Render()
{
	if (playerData->GetItemMenuOpen())
	{
		backGround->Render();
		if (currentMenu == BagItem)
		{
			bagLeft->Render();
			bagMenuItem->Render();
		}
		else if (currentMenu == BagKeyItem)
		{
			bagCenter->Render();
			bagMenuKeyItem->Render();
		}
		else if (currentMenu == BagPokeBalls)
		{
			bagRight->Render();
			bagMenuPokeball->Render();
		}
		ItemExplanRender();
		animRect->Render();

		if(selectIndexNo == 1)
			selectItem1->Render();
		else if( selectIndexNo == 2)
			selectItem2->Render();
		else if (selectIndexNo == 3)
			selectItem3->Render();
		else if (selectIndexNo == 4)
			selectItem4->Render();
		else if (selectIndexNo == 5)
			selectItem5->Render();
		else if (selectIndexNo == 6)
			selectItem6->Render();
	}

	if(pokemonMenu->GetPokemonMenuOpen())
		pokemonMenu->Render();

}

void ItemBag::PickMenu()
{
	if (playerData->GetItemMenuOpen())
	{
		if (bagMenuTree == TopMenu)
		{
			switch (currentMenu)
			{
			case BagItem:
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					playerData->SetCloseItemMenu();
					playerData->ResetUsingItem();
					usingitemcount = false;
				}
				if (KEYBOARD->Down(VK_RIGHT))
				{
					currentMenu = BagKeyItem;
				}
				if (KEYBOARD->Down(VK_DOWN))
				{
					if (selectIndexNo >= 1 && selectIndexNo < 6)
						selectIndexNo++;
					else if (selectIndexNo == 6 && healingItemindexCount < 15)
						healingItemindexCount++;
				}
				if (KEYBOARD->Down(VK_UP))
				{
					if (selectIndexNo > 1 && selectIndexNo <= 6)
						selectIndexNo--;
					else if (selectIndexNo == 1 && healingItemindexCount > 0)
						healingItemindexCount--;
				}
				if (KEYBOARD->Down(VK_SPACE))
				{
					playerData->SetOpenPokemonMenu();
					pokemonMenu->OpenPokemonMenu();
					bagMenuTree = SubMenu;
				}
				break;
			case BagKeyItem:
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					playerData->SetCloseItemMenu();
				}
				if (KEYBOARD->Down(VK_LEFT))
				{
					currentMenu = BagItem;
				}
				if (KEYBOARD->Down(VK_RIGHT))
				{
					currentMenu = BagPokeBalls;
				}
				if (KEYBOARD->Down(VK_DOWN))
				{
					if (selectIndexNo >= 1 && selectIndexNo < 6)
						selectIndexNo++;
					else if (selectIndexNo == 6 && keyItemindexCount < 4)
						keyItemindexCount++;
				}
				if (KEYBOARD->Down(VK_UP))
				{
					if (selectIndexNo > 1 && selectIndexNo <= 6)
						selectIndexNo--;
					else if (selectIndexNo == 1 && keyItemindexCount > 0)
						keyItemindexCount--;
				}
				break;
			case BagPokeBalls:
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					playerData->SetCloseItemMenu();
					selectIndexNo = 1;
					pokeBallindexCount = 0;
				}
				if (KEYBOARD->Down(VK_LEFT))
				{
					currentMenu = BagKeyItem;
					selectIndexNo = 1;
					pokeBallindexCount = 0;
				}
				if (KEYBOARD->Down(VK_DOWN))
				{
					if (selectIndexNo >= 1 && selectIndexNo < 6)
						selectIndexNo++;
					else if (selectIndexNo == 6 && pokeBallindexCount < 10)
						pokeBallindexCount++;
				}
				if (KEYBOARD->Down(VK_UP))
				{
					if (selectIndexNo > 1 && selectIndexNo <= 6)
						selectIndexNo--;
					else if (selectIndexNo == 1 && pokeBallindexCount > 0)
						pokeBallindexCount--;
				}
				if (KEYBOARD->Down(VK_SPACE))
				{
					if (playerData->GetPlayerItem()->GetBallNums(pokeBallIndexNo) > 0)
					{
						balls->SetMonsterBall(pokeBallIndexNo);
						balls->ThrowBall();
						cout << "몬스터볼 던지기 완료" << endl;
						playerData->GetPlayerItem()->UseBalls(pokeBallIndexNo);
						selectIndexNo = 1;
						pokeBallindexCount = 0;
						playerData->SetCloseItemMenu();
						playerData->SetMenuTree(TopMenu);
						playerData->SetBattleSeq(UsingPokeball);
					}
					
				}
				break;
			default:
				break;
			}
		} // 탑 메뉴 트리
		else if (bagMenuTree == SubMenu)
		{
			switch (currentMenu)
			{
			case BagItem:
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					bagMenuTree = TopMenu;
					playerData->SetClosePokemonMenu();
					pokemonMenu->ClosePokemonMenu();
					pokemonMenu->SetSelectPokemon(1);
				}

				else if (KEYBOARD->Down(VK_UP))
				{
					switch (pokemonMenu->GetSelectPokemon())
					{
					case 1:
						if (pokemonMenu->GetPokemonNum() >= 5)
							pokemonMenu->SetSelectPokemon(5);
						else if (pokemonMenu->GetPokemonNum() < 3)
							pokemonMenu->SetSelectPokemon(1);
						else if (pokemonMenu->GetPokemonNum() < 5)
							pokemonMenu->SetSelectPokemon(3);
						break;
					case 2:
						if (pokemonMenu->GetPokemonNum() >= 6)
							pokemonMenu->SetSelectPokemon(6);
						else if (pokemonMenu->GetPokemonNum() < 4)
							pokemonMenu->SetSelectPokemon(2);
						else if (pokemonMenu->GetPokemonNum() < 6)
							pokemonMenu->SetSelectPokemon(4);
						break;
					case 3:
						pokemonMenu->SetSelectPokemon(1);
						break;
					case 4:
						pokemonMenu->SetSelectPokemon(2);
						break;
					case 5:
						pokemonMenu->SetSelectPokemon(3);
						break;
					case 6:
						pokemonMenu->SetSelectPokemon(4);
						break;
					}
				}
				else if (KEYBOARD->Down(VK_DOWN))
				{
					switch (pokemonMenu->GetSelectPokemon())
					{
					case 1:
						if (pokemonMenu->GetPokemonNum() >= 3)
							pokemonMenu->SetSelectPokemon(3);
						else
							pokemonMenu->SetSelectPokemon(1);
						break;
					case 2:
						if (pokemonMenu->GetPokemonNum() >= 4)
							pokemonMenu->SetSelectPokemon(4);
						else
							pokemonMenu->SetSelectPokemon(2);
						break;
					case 3:
						if (pokemonMenu->GetPokemonNum() >= 5)
							pokemonMenu->SetSelectPokemon(5);
						else
							pokemonMenu->SetSelectPokemon(1);
						break;
					case 4:
						if (pokemonMenu->GetPokemonNum() >= 6)
							pokemonMenu->SetSelectPokemon(6);
						else
							pokemonMenu->SetSelectPokemon(2);
						break;
					case 5:
						pokemonMenu->SetSelectPokemon(1);
						break;
					case 6:
						pokemonMenu->SetSelectPokemon(2);
						break;
					}
				}
				else if (KEYBOARD->Down(VK_LEFT) || KEYBOARD->Down(VK_RIGHT))
				{
					switch (pokemonMenu->GetSelectPokemon())
					{
					case 1:
						if (pokemonMenu->GetPokemonNum() >= 2)
							pokemonMenu->SetSelectPokemon(2);
						else
							pokemonMenu->SetSelectPokemon(1);
						break;
					case 2:
						pokemonMenu->SetSelectPokemon(1);
						break;
					case 3:
						if (pokemonMenu->GetPokemonNum() >= 4)
							pokemonMenu->SetSelectPokemon(4);
						else
							pokemonMenu->SetSelectPokemon(3);
						break;
					case 4:
						pokemonMenu->SetSelectPokemon(3);
						break;
					case 5:
						if (pokemonMenu->GetPokemonNum() >= 6)
							pokemonMenu->SetSelectPokemon(6);
						else
							pokemonMenu->SetSelectPokemon(5);
						break;
					case 6:
						pokemonMenu->SetSelectPokemon(5);
						break;
					}
				}
				if (KEYBOARD->Down(VK_SPACE))
				{
					if (!usingitemcount && playerData->GetPlayerItem()->GethealingNums(pokeBallIndexNo) > 0)
					{
						usingitemcount = true;
						playerData->UsingItem(pokemonMenu->GetSelectPokemon(), healingItemIndexNo);

						cout << "아이템 사용1" << endl;
					}

					playerData->SetClosePokemonMenu();
					pokemonMenu->ClosePokemonMenu();
					bagMenuTree = TopMenu;
					cout << "아이템 사용" << endl;

				}
				break;
			case BagKeyItem:
				break;
			case BagPokeBalls:
				break;
			default:
				break;
			}
			

		}

	}

}

void ItemBag::ItemExplanRender()
{
	switch (currentMenu)
	{
	case BagItem:
		HealRender();
		break;

	case BagKeyItem:
		KeyRender();
		break;

	case BagPokeBalls:
		BallRender();
		break;
	}

}

void ItemBag::HealRender()
{
	HealingItem* heal = playerData->GetPlayerItem()->GetHealingItems();

	Text::Get()->BeginDraw();
	{
		//도구 이름 출력
		wstring healname1 = String::ToWString(heal->GetName(healingItemindexCount + 1));
		float size = (float)Text::Get()->GetStringWidth(L"라이트닝드라이브", 5.0f);
		Vector2 pos1 = Vector2(515, 50);
		Text::Get()->RenderText(healname1, pos1, Color(1, 0, 1, 1), size, false);

		wstring healname2 = String::ToWString(heal->GetName(healingItemindexCount + 2));
		Vector2 pos2 = Vector2(515, 120);
		Text::Get()->RenderText(healname2, pos2, Color(1, 0, 1, 1), size, false);

		wstring healname3 = String::ToWString(heal->GetName(healingItemindexCount + 3));
		Vector2 pos3 = Vector2(515, 190);
		Text::Get()->RenderText(healname3, pos3, Color(1, 0, 1, 1), size, false);

		wstring healname4 = String::ToWString(heal->GetName(healingItemindexCount + 4));
		Vector2 pos4 = Vector2(515, 260);
		Text::Get()->RenderText(healname4, pos4, Color(1, 0, 1, 1), size, false);

		wstring healname5 = String::ToWString(heal->GetName(healingItemindexCount + 5));
		Vector2 pos5 = Vector2(515, 330);
		Text::Get()->RenderText(healname5, pos5, Color(1, 0, 1, 1), size, false);

		wstring healname6 = String::ToWString(heal->GetName(healingItemindexCount + 6));
		Vector2 pos6 = Vector2(515, 400);
		Text::Get()->RenderText(healname6, pos6, Color(1, 0, 1, 1), size, false);

		// 도구 수량 출력
		wstring healnum1 = to_wstring(playerData->GetPlayerItem()->GethealingNums(healingItemindexCount + 1));
		Vector2 pos7 = Vector2(1000, 50);
		Text::Get()->RenderText(healnum1, pos7, Color(1, 0, 1, 1), size, false);

		wstring healnum2 = to_wstring(playerData->GetPlayerItem()->GethealingNums(healingItemindexCount + 2));
		Vector2 pos8 = Vector2(1000, 120);
		Text::Get()->RenderText(healnum2, pos8, Color(1, 0, 1, 1), size, false);

		wstring healnum3 = to_wstring(playerData->GetPlayerItem()->GethealingNums(healingItemindexCount + 3));
		Vector2 pos9 = Vector2(1000, 190);
		Text::Get()->RenderText(healnum3, pos9, Color(1, 0, 1, 1), size, false);

		wstring healnum4 = to_wstring(playerData->GetPlayerItem()->GethealingNums(healingItemindexCount + 4));
		Vector2 pos10 = Vector2(1000, 260);
		Text::Get()->RenderText(healnum4, pos10, Color(1, 0, 1, 1), size, false);

		wstring healnum5 = to_wstring(playerData->GetPlayerItem()->GethealingNums(healingItemindexCount + 5));
		Vector2 pos11 = Vector2(1000, 330);
		Text::Get()->RenderText(healnum5, pos11, Color(1, 0, 1, 1), size, false);

		wstring healnum6 = to_wstring(playerData->GetPlayerItem()->GethealingNums(healingItemindexCount + 6));
		Vector2 pos12 = Vector2(1000, 400);
		Text::Get()->RenderText(healnum6, pos12, Color(1, 0, 1, 1), size, false);

		// 포켓볼 설명 출력
		wstring explan = String::ToWString(heal->GetExplan(healingItemIndexNo));
		Vector2 pos13 = Vector2(-50, 550);
		Text::Get()->RenderText(explan, pos13, Color(1, 0, 1, 1), size, false);
	}
	Text::Get()->EndDraw();
}

void ItemBag::KeyRender()
{
	Keyitem* key = playerData->GetPlayerItem()->GetKeyItems();

	Text::Get()->BeginDraw();
	{
		//도구 이름 출력
		wstring keyname1 = String::ToWString(key->GetName(keyItemindexCount + 1));
		float size = (float)Text::Get()->GetStringWidth(L"라이트닝드라이브", 5.0f);
		Vector2 pos1 = Vector2(515, 50);
		Text::Get()->RenderText(keyname1, pos1, Color(1, 0, 1, 1), size, false);

		wstring keyname2 = String::ToWString(key->GetName(keyItemindexCount + 2));
		Vector2 pos2 = Vector2(515, 120);
		Text::Get()->RenderText(keyname2, pos2, Color(1, 0, 1, 1), size, false);

		wstring keyname3 = String::ToWString(key->GetName(keyItemindexCount + 3));
		Vector2 pos3 = Vector2(515, 190);
		Text::Get()->RenderText(keyname3, pos3, Color(1, 0, 1, 1), size, false);

		wstring keyname4 = String::ToWString(key->GetName(keyItemindexCount + 4));
		Vector2 pos4 = Vector2(515, 260);
		Text::Get()->RenderText(keyname4, pos4, Color(1, 0, 1, 1), size, false);

		wstring keyname5 = String::ToWString(key->GetName(keyItemindexCount + 5));
		Vector2 pos5 = Vector2(515, 330);
		Text::Get()->RenderText(keyname5, pos5, Color(1, 0, 1, 1), size, false);

		wstring keyname6 = String::ToWString(key->GetName(keyItemindexCount + 6));
		Vector2 pos6 = Vector2(515, 400);
		Text::Get()->RenderText(keyname6, pos6, Color(1, 0, 1, 1), size, false);

		// 중요한 도구 설명 출력
		wstring explan = String::ToWString(key->GetExplan(keyItemIndexNo));
		Vector2 pos13 = Vector2(50, 550);
		Text::Get()->RenderText(explan, pos13, Color(1, 0, 1, 1), size, false);
	}
	Text::Get()->EndDraw();
}

void ItemBag::BallRender()
{
	Text::Get()->BeginDraw();
	{
		// 포켓볼 이름 출력
		wstring ballname1 = String::ToWString(balls->GetBallName(pokeBallindexCount + 1));
		float size = (float)Text::Get()->GetStringWidth(L"라이트닝드라이브", 5.0f);
		Vector2 pos1 = Vector2(515, 50);
		Text::Get()->RenderText(ballname1, pos1, Color(1, 0, 1, 1), size, false);

		wstring ballname2 = String::ToWString(balls->GetBallName(pokeBallindexCount + 2));
		Vector2 pos2 = Vector2(515, 120);
		Text::Get()->RenderText(ballname2, pos2, Color(1, 0, 1, 1), size, false);

		wstring ballname3 = String::ToWString(balls->GetBallName(pokeBallindexCount + 3));
		Vector2 pos3 = Vector2(515, 190);
		Text::Get()->RenderText(ballname3, pos3, Color(1, 0, 1, 1), size, false);

		wstring ballname4 = String::ToWString(balls->GetBallName(pokeBallindexCount + 4));
		Vector2 pos4 = Vector2(515, 260);
		Text::Get()->RenderText(ballname4, pos4, Color(1, 0, 1, 1), size, false);

		wstring ballname5 = String::ToWString(balls->GetBallName(pokeBallindexCount + 5));
		Vector2 pos5 = Vector2(515, 330);
		Text::Get()->RenderText(ballname5, pos5, Color(1, 0, 1, 1), size, false);

		wstring ballname6 = String::ToWString(balls->GetBallName(pokeBallindexCount + 6));
		Vector2 pos6 = Vector2(515, 400);
		Text::Get()->RenderText(ballname6, pos6, Color(1, 0, 1, 1), size, false);

		// 포켓볼 수량 출력
		wstring ballnum1 = to_wstring(playerData->GetPlayerItem()->GetBallNums(pokeBallindexCount + 1));
		Vector2 pos7 = Vector2(1000, 50);
		Text::Get()->RenderText(ballnum1, pos7, Color(1, 0, 1, 1), size, false);

		wstring ballnum2 = to_wstring(playerData->GetPlayerItem()->GetBallNums(pokeBallindexCount + 2));
		Vector2 pos8 = Vector2(1000, 120);
		Text::Get()->RenderText(ballnum2, pos8, Color(1, 0, 1, 1), size, false);

		wstring ballnum3 = to_wstring(playerData->GetPlayerItem()->GetBallNums(pokeBallindexCount + 3));
		Vector2 pos9 = Vector2(1000, 190);
		Text::Get()->RenderText(ballnum3, pos9, Color(1, 0, 1, 1), size, false);

		wstring ballnum4 = to_wstring(playerData->GetPlayerItem()->GetBallNums(pokeBallindexCount + 4));
		Vector2 pos10 = Vector2(1000, 260);
		Text::Get()->RenderText(ballnum4, pos10, Color(1, 0, 1, 1), size, false);

		wstring ballnum5 = to_wstring(playerData->GetPlayerItem()->GetBallNums(pokeBallindexCount + 5));
		Vector2 pos11 = Vector2(1000, 330);
		Text::Get()->RenderText(ballnum5, pos11, Color(1, 0, 1, 1), size, false);

		wstring ballnum6 = to_wstring(playerData->GetPlayerItem()->GetBallNums(pokeBallindexCount + 6));
		Vector2 pos12 = Vector2(1000, 400);
		Text::Get()->RenderText(ballnum6, pos12, Color(1, 0, 1, 1), size, false);

		// 포켓볼 설명 출력
		wstring ballexplan = String::ToWString(balls->GetBallExplan(pokeBallIndexNo));
		Vector2 pos13 = Vector2(-150, 550);
		Text::Get()->RenderText(ballexplan, pos13, Color(1, 0, 1, 1), size, false);
	}
	Text::Get()->EndDraw();
}
