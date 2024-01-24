#include "Framework.h"
#include "BattleBG.h"

#include "GeoMetries\TextureRect.h"
#include "Game\UI\ProgressBar.h"
#include "Game\UI\SwitchPokemon.h"
#include "../UnitTest/01.Character/Player.h"
#include "Game/Menu/ItemBag.h"
#include "Game/Item/PokeBall.h"

BattleBG::BattleBG(Player* player, Pokemon* enemyPokemon)
{
	battleMenu = new ProgressBar({ 120,-224,0 }, { 480,192,0 }, 0.0f, TextureMapBattlePath + L"BattleMenu.png", UI::LEFT_TO_RIGHT);
	selectFIGHT = new ProgressBar({ 150,-200,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectBAG = new ProgressBar({ 370,-200,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectPOKEMON = new ProgressBar({ 150,-265,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectRUN = new ProgressBar({ 370,-265,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	fightMenu = new ProgressBar({ -600,-224,0 }, { 1200,192,0 }, 0.0f, TextureMapBattlePath + L"FightMenu.png", UI::LEFT_TO_RIGHT);


	selectSkill1 = new ProgressBar({ -540,-190,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectSkill2 = new ProgressBar({ -130,-190,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectSkill3 = new ProgressBar({ -540,-260,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectSkill4 = new ProgressBar({ -130,-260,0 }, { 30,40,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	
	switchPokemon = new SwitchPokemon(player);
	bagpack = new ItemBag(player);
	levelUpResult = new TextureRect({ 1050,280,0.f }, { 200,200,0 }, 0.f, TextureMapBattlePath + L"LevelupResult.png");

	playerData = player;
	enemyData = enemyPokemon;
	currentMenu = FIGHT;
	enemyTextRendering = false;
	playerTextRendering = false;
	menu = playerData->GetMenuTree();
	spacecount = playerData->GetSpaceCount();
}

BattleBG::~BattleBG()
{
	SAFE_DELETE(levelUpResult);
	SAFE_DELETE(bagpack);
	SAFE_DELETE(switchPokemon);
	SAFE_DELETE(selectSkill4);
	SAFE_DELETE(selectSkill3);
	SAFE_DELETE(selectSkill2);
	SAFE_DELETE(selectSkill1);

	SAFE_DELETE(fightMenu);
	SAFE_DELETE(selectRUN);
	SAFE_DELETE(selectPOKEMON);
	SAFE_DELETE(selectBAG);
	SAFE_DELETE(selectFIGHT);
	SAFE_DELETE(battleMenu);
}

void BattleBG::Update()
{
	battleMenu->Update();
	
	selectFIGHT->Update();
	selectBAG->Update();
	selectPOKEMON->Update();
	selectRUN->Update();
	fightMenu->Update();
	switchPokemon->Update();
	
	selectSkill1->Update();
	selectSkill2->Update();
	selectSkill3->Update();
	selectSkill4->Update();
	levelUpResult->Update();
	bagpack->Update();


	if (playerData->GetPlayerItem()->GetPokeballs()->BallThrowing())
	{
		Reset();
		playerData->SetCloseItemMenu();
	}
}

void BattleBG::Render()
{

	HpRender();

	if (playerturn)
	{
		battleMenu->Render();
		if (currentMenu == FIGHT)
			selectFIGHT->Render();
		else if (currentMenu == BAG)
			selectBAG->Render();
		else if (currentMenu == POKEMON)
			selectPOKEMON->Render();
		else if (currentMenu == RUN)
			selectRUN->Render();

		if (currentMenu == FIGHT && *menu == SubMenu)
		{
			fightMenu->Render();
			SkillRender();
			if (selectSkill == 1)
				selectSkill1->Render();
			else if (selectSkill == 2)
				selectSkill2->Render();
			else if (selectSkill == 3)
				selectSkill3->Render();
			else if (selectSkill == 4)
				selectSkill4->Render();
		}
		else if (currentMenu == POKEMON && *menu == SubMenu)
		{
			switchPokemon->Render();
		}
		else if (currentMenu == BAG && *menu == SubMenu)
		{
			bagpack->Render();
		}
	}

	if (enemyTextRendering && !playerTextRendering)
	{
		EnemyTextRender();
	}
	if (playerTextRendering && !enemyTextRendering)
	{
		PlayerTextRender();
	}
	if (*menu == TopMenu && !enemyTextRendering && !playerTextRendering)
		PlayerIdleTextRender();

	if (levelUpRendering)
	{
		levelUpResult->Render();
		PlayerPokemonLvUp();
	}


		
}

void BattleBG::Reset()
{
	playerData->SetMenuTree(TopMenu);
	currentMenu = FIGHT;
	selectSkill = 1;
	*spacecount = 0;
	fight = false;
}


void BattleBG::PickMenu(int* selecSkill, bool* isBattle, BattleSequence* seq)
{
	if (isBattle)
	{
		if (*menu == SubMenu)
		{
			switch (currentMenu)
			{
			case FIGHT:
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					Reset();
				//	playerData->SetCloseBattleMenu();
				}
				else if (KEYBOARD->Down(VK_UP) || KEYBOARD->Down(VK_DOWN))
				{
					switch (selectSkill)
					{
					case 1:
						selectSkill = 3;
						break;
					case 2:
						selectSkill = 4;
						break;
					case 3:
						selectSkill = 1;
						break;
					case 4:
						selectSkill = 2;
						break;
					}
				}
				else if (KEYBOARD->Down(VK_LEFT) || KEYBOARD->Down(VK_RIGHT))
				{
					switch (selectSkill)
					{
					case 1:
						selectSkill = 2;
						break;
					case 2:
						selectSkill = 1;
						break;
					case 3:
						selectSkill = 4;
						break;
					case 4:
						selectSkill = 3;
						break;
					}
				}
				if (KEYBOARD->Down(VK_SPACE) && *spacecount == 1)
				{
					if (playerData->GetcurrentPokemon()->NotEnoughPP(selectSkill))
					{
						*selecSkill = selectSkill;
						playerData->GetcurrentPokemon()->UsingSkill(selectSkill);
						fight = true;
						*seq = DamageCalc;
						playerData->SetMenuTree(TopMenu);
						currentMenu = FIGHT;
						selectSkill = 1;
						*spacecount = 0;
						cout << "플레이어 스킬선택 완료" << endl;
					}
					
				}
				break;
			case BAG:
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					Reset();
					playerData->SetCloseItemMenu();
				}

				break;
			case POKEMON:
				
				if (KEYBOARD->Down(VK_ESCAPE))
				{
					Reset();
					playerData->SetClosePokemonMenu();
					switchPokemon->ClosePokemonMenu();
					switchPokemon->SetSelectPokemon(1);
				}
				else if (KEYBOARD->Down(VK_UP))
				{
					switch (switchPokemon->GetSelectPokemon())
					{
					case 1:
						if (switchPokemon->GetPokemonNum() >= 5)
							switchPokemon->SetSelectPokemon(5);
						else if (switchPokemon->GetPokemonNum() < 3)
							switchPokemon->SetSelectPokemon(1);
						else if (switchPokemon->GetPokemonNum() < 5)
							switchPokemon->SetSelectPokemon(3);
						break;
					case 2:
						if (switchPokemon->GetPokemonNum() >= 6)
							switchPokemon->SetSelectPokemon(6);
						else if (switchPokemon->GetPokemonNum() < 4)
							switchPokemon->SetSelectPokemon(2);
						else if (switchPokemon->GetPokemonNum() < 6)
							switchPokemon->SetSelectPokemon(4);
						break;
					case 3:
						switchPokemon->SetSelectPokemon(1);
						break;
					case 4:
						switchPokemon->SetSelectPokemon(2);
						break;
					case 5:
						switchPokemon->SetSelectPokemon(3);
						break;
					case 6:
						switchPokemon->SetSelectPokemon(4);
						break;
					}
				}
				else if (KEYBOARD->Down(VK_DOWN))
				{
					switch (switchPokemon->GetSelectPokemon())
					{
					case 1:
						if (switchPokemon->GetPokemonNum() >= 3)
							switchPokemon->SetSelectPokemon(3);
						else 
							switchPokemon->SetSelectPokemon(1);						
						break;
					case 2:
						if (switchPokemon->GetPokemonNum() >= 4)
							switchPokemon->SetSelectPokemon(4);
						else 
							switchPokemon->SetSelectPokemon(2);
						break;
					case 3:
						if (switchPokemon->GetPokemonNum() >= 5)
							switchPokemon->SetSelectPokemon(5);
						else
							switchPokemon->SetSelectPokemon(1);
						break;
					case 4:
						if (switchPokemon->GetPokemonNum() >= 6)
							switchPokemon->SetSelectPokemon(6);
						else
							switchPokemon->SetSelectPokemon(2);
						break;
					case 5:
						switchPokemon->SetSelectPokemon(1);
						break;
					case 6:
						switchPokemon->SetSelectPokemon(2);
						break;
					}
				}
				else if (KEYBOARD->Down(VK_LEFT) || KEYBOARD->Down(VK_RIGHT))
				{
					switch (switchPokemon->GetSelectPokemon())
					{
					case 1:
						if (switchPokemon->GetPokemonNum() >= 2)
							switchPokemon->SetSelectPokemon(2);
						else
							switchPokemon->SetSelectPokemon(1);
						break;
					case 2:
						switchPokemon->SetSelectPokemon(1);
						break;
					case 3:
						if (switchPokemon->GetPokemonNum() >= 4)
							switchPokemon->SetSelectPokemon(4);
						else
							switchPokemon->SetSelectPokemon(3);
						break;
					case 4:
						switchPokemon->SetSelectPokemon(3);
						break;
					case 5:
						if (switchPokemon->GetPokemonNum() >= 6)
							switchPokemon->SetSelectPokemon(6);
						else
							switchPokemon->SetSelectPokemon(5);
						break;
					case 6:
						switchPokemon->SetSelectPokemon(5);
						break;
					}
				}
				if (KEYBOARD->Down(VK_SPACE) && *spacecount == 1)
				{
					playerData->SetSwitchPokemon(switchPokemon->GetSelectPokemon());
					playerData->SetClosePokemonMenu();
					*seq = TurnEnd;
					Reset();
				}
									
				break;
			
			default:
				break;
			}


			
		}

		else if (*menu == TopMenu)
		{
			
			if (KEYBOARD->Down(VK_UP) || KEYBOARD->Down(VK_DOWN))
			{
				playerData->SetSpaceCountReset();
				switch (currentMenu)
				{
				case FIGHT:
					currentMenu = POKEMON;
					break;
				case BAG:
					currentMenu = RUN;
					break;
				case POKEMON:
					currentMenu = FIGHT;
					break;
				case RUN:
					currentMenu = BAG;
					break;
				}
			}
			else if (KEYBOARD->Down(VK_LEFT) || KEYBOARD->Down(VK_RIGHT))
			{
				playerData->SetSpaceCountReset();
				switch (currentMenu)
				{
				case FIGHT:
					currentMenu = BAG;
					break;
				case BAG:
					currentMenu = FIGHT;
					break;
				case POKEMON:
					currentMenu = RUN;
					break;
				case RUN:
					currentMenu = POKEMON;
					break;
				}
			}
			else if (KEYBOARD->Down(VK_SPACE) && *spacecount == 0)
			{
				switch (currentMenu)
				{
				case FIGHT:
					playerData->SetMenuTree(SubMenu);
					*spacecount = 1;
					break;
				case BAG:
					playerData->SetOpenItemMenu();
					playerData->SetMenuTree(SubMenu);
					*spacecount = 1;
					if (playerData->GetPlayerItem()->GetPokeballs()->BallThrowing())
					{
						Reset();
						playerData->SetCloseItemMenu();
						playerData->SetBattleSeq(UsingPokeball);
					}
					break;
				case POKEMON:
					playerData->SetMenuTree(SubMenu);
					*spacecount = 1;
					playerData->SetOpenPokemonMenu();
					switchPokemon->OpenPokemonMenu();
					break;
				case RUN:
					Reset();
					playerData->SetSwitchPokemon(1);
					battleEnd = true;
					break;
				}
			}

		}
	}


	
	/*else if (selectMenu == true && currentMenu == FIGHT && KEYBOARD->Down(VK_SPACE))
	{
		*selecSkill = selectSkill;
		fight = true;


		if (battleMenuTree == SubMenu && KEYBOARD->Down(VK_ESCAPE))
		battleMenuTree = TopMenu;
	}*/
	
}

void BattleBG::SkillRender()
{
	Text::Get()->BeginDraw();
	{
		// 스킬 이름 출력
		wstring skillname1 = String::ToWString(playerData->GetcurrentPokemon()->GetSkillData(1).name);
		float size = (float)Text::Get()->GetStringWidth(L"라이트닝드라이브", 5.0f);
		Vector2 pos1 = Vector2(140, 525);
		Text::Get()->RenderText(skillname1, pos1, Color(1, 0, 1, 1), size, false);

		wstring skillname2 = String::ToWString(playerData->GetcurrentPokemon()->GetSkillData(2).name);
		Vector2 pos2 = Vector2(550, 525);
		Text::Get()->RenderText(skillname2, pos2, Color(1, 0, 1, 1), size, false);

		wstring skillname3 = String::ToWString(playerData->GetcurrentPokemon()->GetSkillData(3).name);
		Vector2 pos3 = Vector2(140, 595);
		Text::Get()->RenderText(skillname3, pos3, Color(1, 0, 1, 1), size, false);

		wstring skillname4 = String::ToWString(playerData->GetcurrentPokemon()->GetSkillData(4).name);
		Vector2 pos4 = Vector2(550, 595);
		Text::Get()->RenderText(skillname4, pos4, Color(1, 0, 1, 1), size, false);

		// pp 및 기술 타입 출력
		if (selectSkill == 1)
		{
			wstring skill1CurrentPP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().skill1currentPP));
			Vector2 skill1CurrentPPpos = Vector2(1030, 525);
			Text::Get()->RenderText(skill1CurrentPP, skill1CurrentPPpos, Color(1, 0, 1, 1), size, false);

			wstring skill1PP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetSkillData(1).pp));
			Vector2 skill1PPpos = Vector2(1130, 525);
			Text::Get()->RenderText(skill1PP, skill1PPpos, Color(1, 0, 1, 1), size, false);

			Vector2 skill1Typepos = Vector2(1060, 590);
			Text::Get()->RenderText(ConvertPMtype(playerData->GetcurrentPokemon()->GetSkillData(1).ptype), skill1Typepos, Color(1, 0, 1, 1), size, false);
		}
		else if (selectSkill == 2)
		{
			wstring skill2CurrentPP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().skill2currentPP));
			Vector2 skill2CurrentPPpos = Vector2(1030, 525);
			Text::Get()->RenderText(skill2CurrentPP, skill2CurrentPPpos, Color(1, 0, 1, 1), size, false);

			wstring skill2PP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetSkillData(2).pp));
			Vector2 skill2PPpos = Vector2(1130, 525);
			Text::Get()->RenderText(skill2PP, skill2PPpos, Color(1, 0, 1, 1), size, false);

			Vector2 skill2Typepos = Vector2(1060, 590);
			Text::Get()->RenderText(ConvertPMtype(playerData->GetcurrentPokemon()->GetSkillData(2).ptype), skill2Typepos, Color(1, 0, 1, 1), size, false);
		}
		else if (selectSkill == 3)
		{
			wstring skill3CurrentPP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().skill3currentPP));
			Vector2 skill3CurrentPPpos = Vector2(1030, 525);
			Text::Get()->RenderText(skill3CurrentPP, skill3CurrentPPpos, Color(1, 0, 1, 1), size, false);

			wstring skill3PP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetSkillData(3).pp));
			Vector2 skill3PPpos = Vector2(1130, 525);
			Text::Get()->RenderText(skill3PP, skill3PPpos, Color(1, 0, 1, 1), size, false);

			Vector2 skill3Typepos = Vector2(1060, 590);
			Text::Get()->RenderText(ConvertPMtype(playerData->GetcurrentPokemon()->GetSkillData(3).ptype), skill3Typepos, Color(1, 0, 1, 1), size, false);
		}
		else if (selectSkill == 4)
		{
			wstring skill4CurrentPP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().skill4currentPP));
			Vector2 skill4CurrentPPpos = Vector2(1030, 525);
			Text::Get()->RenderText(skill4CurrentPP, skill4CurrentPPpos, Color(1, 0, 1, 1), size, false);

			wstring skill4PP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetSkillData(4).pp));
			Vector2 skill4PPpos = Vector2(1130, 525);
			Text::Get()->RenderText(skill4PP, skill4PPpos, Color(1, 0, 1, 1), size, false);

			Vector2 skill4Typepos = Vector2(1060, 590);
			Text::Get()->RenderText(ConvertPMtype(playerData->GetcurrentPokemon()->GetSkillData(4).ptype), skill4Typepos, Color(1, 0, 1, 1), size, false);
		}

	}
	Text::Get()->EndDraw();


}

wstring BattleBG::ConvertPMtype(PmType type)
{
	switch (type)
	{
	case TypeNull:
		return L"NULL";
		break;
	case NormalType:
		return L"노멀";
		break;
	case FireType:
		return L"불";
		break;
	case WaterType:
		return L"물";
		break;
	case LeafType:
		return L"풀";
		break;
	case ElectricType:
		return L"전기";
		break;
	case IceType:
		return L"얼음";
		break;
	case FightingType:
		return L"격투";
		break;
	case PoisonType:
		return L"독";
		break;
	case GroundType:
		return L"땅";
		break;
	case FlyingType:
		return L"비행";
		break;
	case PsychicType:
		return L"에스퍼";
		break;
	case BugType:
		return L"벌래";
		break;
	case RockType:
		return L"바위";
		break;
	case GhostType:
		return L"고스트";
		break;
	case DragonType:
		return L"드래곤";
		break;
	case DarkType:
		return L"악";
		break;
	case SteelType:
		return L"강철";
		break;
	case FairyType:
		return L"페어리";
		break;
	default:
		break;
	}



	return wstring();
}

void BattleBG::HpRender()
{

	Text::Get()->BeginDraw();
	{
		wstring playercurrentHP = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().currentHp));
		float size = (float)Text::Get()->GetStringWidth(L"1000", 5.0f);
		Vector2 pos1 = Vector2(1085, 432);
		Text::Get()->RenderText(playercurrentHP, pos1, Color(1, 0, 1, 1), size, false);

		wstring playeMaxHP = L" / " + String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().maxHp));
		Vector2 pos2 = Vector2(1100, 432);
		Text::Get()->RenderText(playeMaxHP, pos2, Color(1, 0, 1, 1), size, false);

		wstring playeLevel = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().level));
		float size2 = (float)Text::Get()->GetStringWidth(L"1000", 6.0f);
		Vector2 pos3 = Vector2(1142, 390);
		Text::Get()->RenderText(playeLevel, pos3, Color(1, 0, 1, 1), size2, false);

		wstring playePmName = String::ToWString(playerData->GetcurrentPokemon()->GetPKData().indexName);
		float size3 = (float)Text::Get()->GetStringWidth(L"라이트닝블레이드", 3.0f);
		Vector2 pos4 = Vector2(930, 385);
		Text::Get()->RenderText(playePmName, pos4, Color(1, 0, 1, 1), size3, false);


		wstring enemyLevel = String::ToWString(to_string(enemyData->GetPKData().level));
		Vector2 pos5 = Vector2(435, 123);
		Text::Get()->RenderText(enemyLevel, pos5, Color(1, 0, 1, 1), size2, false);

		wstring enemyPmName = String::ToWString(enemyData->GetPKData().indexName);
		Vector2 pos6 = Vector2(220, 120);
		Text::Get()->RenderText(enemyPmName, pos6, Color(1, 0, 1, 1), size3, false);
	}
	Text::Get()->EndDraw();
}


void BattleBG::EnemyTextRender()
{

	Text::Get()->BeginDraw();
	{
		wstring pokemonName = String::ToWString(enemyData->GetPKData().name) + L" 의";
		wstring skillName = String::ToWString(enemySkillName);
		float size = (float)Text::Get()->GetStringWidth(L"야생 울트라네크로즈마의", 3.0f);
		Vector2 pos1 = Vector2(150, 530);
		Vector2 pos2 = Vector2(200, 600);
		Text::Get()->RenderText(pokemonName, pos1, Color(255, 255, 255, 1), size, false);
		Text::Get()->RenderText(skillName, pos2, Color(255, 255, 255, 1), size, false);
	}
	Text::Get()->EndDraw();

	
}

void BattleBG::EnemyTextRender(string skill, BattleSequence* seq)
{
	enemySkillName = skill;

	if (DeltaTime > 2)
	{
		*seq = TurnEnd;
		cout << "몬스터 턴 종료" << endl;
		DeltaTime = 0;
		enemyTextRendering = false;
	}
	else
	{
		enemyTextRendering = true;
		DeltaTime += Time::Delta();
	}
		
}

void BattleBG::PlayerTextRender()
{
	Text::Get()->BeginDraw();
	{

		if (result)
		{
			wstring pokemonName = String::ToWString(playerData->GetcurrentPokemon()->GetPKData().name) + L" 은(는)";
			wstring expUp = L"5000 경험치를 받았다";
			float size = (float)Text::Get()->GetStringWidth(L"야생 울트라네크로즈마의", 3.0f);
			Vector2 pos1 = Vector2(200, 530);
			Vector2 pos2 = Vector2(200, 600);
			Text::Get()->RenderText(pokemonName, pos1, Color(255, 255, 255, 1), size, false);
			Text::Get()->RenderText(expUp, pos2, Color(255, 255, 255, 1), size, false);
		}
		else if (gotchaPokemon)
		{
			wstring pokemonName = String::ToWString(enemyData->GetPKData().name) + L" 을(를)";
			wstring expUp = L"잡았다!";
			float size = (float)Text::Get()->GetStringWidth(L"야생 울트라네크로즈마의", 3.0f);
			Vector2 pos1 = Vector2(200, 530);
			Vector2 pos2 = Vector2(200, 600);
			Text::Get()->RenderText(pokemonName, pos1, Color(255, 255, 255, 1), size, false);
			Text::Get()->RenderText(expUp, pos2, Color(255, 255, 255, 1), size, false);
		}
		else if (usingPokeball)
		{
			wstring pokeballName = String::ToWString("플레이어는 " + playerData->GetPlayerItem()->GetPokeballs()->GetBallName()) + L" 을(를)";
			wstring expUp = L"던졌다.";
			float size = (float)Text::Get()->GetStringWidth(L"야생 울트라네크로즈마의", 3.0f);
			Vector2 pos1 = Vector2(200, 530);
			Vector2 pos2 = Vector2(200, 600);
			Text::Get()->RenderText(pokeballName, pos1, Color(255, 255, 255, 1), size, false);
			Text::Get()->RenderText(expUp, pos2, Color(255, 255, 255, 1), size, false);
		}
		else
		{
			wstring pokemonName = String::ToWString(playerData->GetcurrentPokemon()->GetPKData().name) + L" 의";
			wstring skillName = String::ToWString(playerSkillname);
			float size = (float)Text::Get()->GetStringWidth(L"야생 울트라네크로즈마의", 3.0f);
			Vector2 pos1 = Vector2(200, 530);
			Vector2 pos2 = Vector2(200, 600);
			Text::Get()->RenderText(pokemonName, pos1, Color(255, 255, 255, 1), size, false);
			Text::Get()->RenderText(skillName, pos2, Color(255, 255, 255, 1), size, false);
		}
	}
	Text::Get()->EndDraw();

}

void BattleBG::PlayerTextRender(string skill, BattleSequence* seq)
{
	playerSkillname = skill;

	if (DeltaTime > 2)
	{
		cout << "플레이어 턴 종료" << endl;
		*seq = TurnEnd;
		DeltaTime = 0;
		playerTextRendering = false;
	}
	else
	{
		DeltaTime += Time::Delta();
		playerTextRendering = true;
	}
		
}

void BattleBG::PlayerTextRender(BattleSequence* seq)
{
	if (*seq == SwitchingPokemon)
	{
		switching = true;
		playerTextRendering = true;
		cout << "플레이어 포켓몬 스위칭" << endl;

		if (DeltaTime > 2)
		{
			cout << "플레이어 포켓몬 스위칭 종료" << endl;
			switching = false;
			playerTextRendering = false;
			DeltaTime = 0;
			*seq = TurnEnd;
		}
		else
		{
			DeltaTime += Time::Delta();
		}

	}

	if (*seq == ResultPop)
	{
		result = true;
		playerTextRendering = true;
		cout << "플레이어 경험치 획득" << endl;


		if (DeltaTime > 2 && !levelUp)
		{
			cout << "배틀 종료" << endl;
			result = false;
			playerTextRendering = false;
			DeltaTime = 0;
			battleEnd = true;
			*seq = BattleEnd;
		}
		else if (DeltaTime > 2 && levelUp)
		{
			levelUpRendering = true;
		}
		if (DeltaTime > 4)
		{
			levelUpRendering = false;
			levelUp = false;
			playerData->GetcurrentPokemon()->SetLevelupEnd();
			cout << "배틀 종료" << endl;
			result = false;
			playerTextRendering = false;
			DeltaTime = 0;
			battleEnd = true;
			*seq = BattleEnd;
		}
		else
		{
			DeltaTime += Time::Delta();
		}
	}

	if (*playerData->GetBattleSeq() == UsingPokeball)
	{
		usingPokeball = true;
		playerTextRendering = true;
		cout << "플레이어 포켓볼 사용" << endl;

		if (DeltaTime > 2)
		{
			cout << "플레이어 포켓볼 던지기 종료" << endl;
			usingPokeball = false;
			playerTextRendering = false;
			DeltaTime = 0;
		}
		else
		{
			DeltaTime += Time::Delta();
		}
	}
	
	
	if (*seq == GotchaPokemon)
	{
		SetUsingPokeballReset();
		gotchaPokemon = true;
		playerTextRendering = true;
		cout << "플레이어 포켓몬 포획 완료" << endl;


		if (DeltaTime > 2)
		{
			cout << "배틀 종료" << endl;
			gotchaPokemon = false;
			playerTextRendering = false;
			DeltaTime = 0;
			battleEnd = true;
			playerData->GetPlayerItem()->GetPokeballs()->SetPlayerPokemonGotchaReset();
			playerData->GetPlayerItem()->GetPokeballs()->PokemonGetRenderReset();
		}
		else
		{
			DeltaTime += Time::Delta();
		}
	}
	


}

void BattleBG::PlayerIdleTextRender()
{
	Text::Get()->BeginDraw();
	{
		wstring pokemonName = String::ToWString(playerData->GetcurrentPokemon()->GetPKData().name) + L" 은(는) ";
		wstring action = L" 무엇을 할까?";
		float size = (float)Text::Get()->GetStringWidth(L"야생 울트라네크로즈마의", 3.0f);
		Vector2 pos1 = Vector2(200, 530);
		Vector2 pos2 = Vector2(200, 600);
		Text::Get()->RenderText(pokemonName, pos1, Color(255, 255, 255, 1), size, false);
		Text::Get()->RenderText(action, pos2, Color(255, 255, 255, 1), size, false);
	}
	Text::Get()->EndDraw();
}

void BattleBG::PlayerPokemonLvUp()
{
	Text::Get()->BeginDraw();
	{
		wstring maxHp = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetPKData().maxHp));
		wstring atk = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetStat()->GetStatus().atk));
		wstring def = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetStat()->GetStatus().def));
		wstring satk = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetStat()->GetStatus().sAtk));
		wstring sdef = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetStat()->GetStatus().sDef));
		wstring spd = String::ToWString(to_string(playerData->GetcurrentPokemon()->GetStat()->GetStatus().spd));
		float size = (float)Text::Get()->GetStringWidth(L"1000", 5.0f);

		// 능력치 목록
		Text::Get()->RenderText(L"최대HP", Vector2(980, 355), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(L"공격", Vector2(980, 385), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(L"방어", Vector2(980, 415), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(L"특수공격", Vector2(980, 445), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(L"특수방어", Vector2(980, 475), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(L"스피드", Vector2(980, 505), Color(1, 1, 1, 1), size, false);
		// 실제 수치
		Text::Get()->RenderText(maxHp, Vector2(1090, 355), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(atk, Vector2(1090, 385), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(def, Vector2(1090, 415), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(satk, Vector2(1090, 445), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(sdef, Vector2(1090, 475), Color(1, 1, 1, 1), size, false);
		Text::Get()->RenderText(spd, Vector2(1090, 505), Color(1, 1, 1, 1), size, false);

	}
	Text::Get()->EndDraw();



}

