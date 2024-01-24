#include "Framework.h"
#include "NPCBattle.h"

NPCBattle::NPCBattle(Player* player, BattleNPC* npc)
{
	BackGround = new TextureRect({ WinMaxWidth / 2,WinMaxHeight / 2,0.f }, { WinMaxWidth,WinMaxHeight,0.f }, 0.f, TextureMapBattlePath + L"background2.png");
	BackGroundTp = new TextureRect({ WinMaxWidth / 2,456,0.f }, { 1200,448,0 }, 0.f, TextureMapBattlePath + L"battleBag.png");
	BackGroundBt = new TextureRect({ WinMaxWidth / 2,136,0.f }, { 1200,192,0 }, 0.f, TextureMapBattlePath + L"battleBag2.png");
	pHp = new HpBar({ 382,-63,0 }, { 139,8,0 });	// 플레이어 HP바
	eHp = new HpBar({ -332,195,0 }, { 144,9,0 });	// 적몬스터 HP바
	exp = new ExpBar({ 335,-100,0 }, { 192,5,0 });	// 플레이어 경험치바
	battlebackground = new BattleBG(player, npc->GetcurrentPokemon()); // 배틀 메뉴클래스

	UI.push_back(new TextureRect({ 340,568,0 }, { 300,87,0 }, 0.f, TextureMapBattlePath + L"enemyHP.png"));
	UI.push_back(new TextureRect({ 1034,297,0 }, { 300,87,0 }, 0.f, TextureMapBattlePath + L"playerHP.png"));


	btPlayer = player;
	btNPC = npc;
	NPCPokemon = npc->GetcurrentPokemon();

	int currentExp = btPlayer->GetcurrentPokemon()->GetPKData().exp;
	int nextLevel = btPlayer->GetcurrentPokemon()->GetPKData().level + 1;

	if (btPlayer->GetcurrentPokemon()->GetPKData().exp == 0)
	{
		int percent = 0;
		exp->SetPercent(percent);
	}
	else
	{
		int percent = currentExp / ((4 * nextLevel * nextLevel * nextLevel) / 5);
		exp->SetPercent(percent);
	}

	battleSeq = btPlayer->GetBattleSeq();
	npcPokemonNum = npc->GetPokemonNum();
	playerPokemonNum = btPlayer->GetPokemonNum();
	currentnpcPokemonNum = 1;
	currentPlayerPokemonNum = 1;



}

NPCBattle::~NPCBattle()
{



	for (TextureRect* r : UI)
		SAFE_DELETE(r);

	SAFE_DELETE(battlebackground);
	SAFE_DELETE(exp);
	SAFE_DELETE(eHp);
	SAFE_DELETE(pHp);
	SAFE_DELETE(BackGroundBt);
	SAFE_DELETE(BackGroundTp);
	SAFE_DELETE(BackGround);
}

void NPCBattle::Update()
{
	BackGround->Update();
	BackGroundTp->Update();
	BackGroundBt->Update();
	for (TextureRect* r : UI)
		r->Update();

	pHp->Update();
	eHp->Update();
	exp->Update();
	battlebackground->Update();

	if (battleOn)
		BattlePhase();

//	NPCPokemon->Update();
//	btPlayer->GetcurrentPokemon()->Update();

}

void NPCBattle::Render()
{
	BackGround->Render();
	BackGroundTp->Render();
	BackGroundBt->Render();

	for (TextureRect* r : UI)
		r->Render();

	pHp->Render();
	eHp->Render();
	exp->Render();
	battlebackground->Render();

	if (!btPlayer->GetItemMenuOpen() && !btPlayer->GetPokemonMenuOpen())
	{
		NPCPokemon->Render();
		btPlayer->GetcurrentPokemon()->Render();
	}
	
}

void NPCBattle::PlayerTurn() //플레이어의 턴 시작
{
	if (battleover == false && *battleSeq == SelectSkill) // 스킬 선택
	{
		battlebackground->SetPlayerTurn();
		cout << "플레이어 스킬 선택 시작" << endl;
		battlebackground->PickMenu(&selectSkill, &battleOn, battleSeq);

	}

	if (btPlayer->GetPlayerItem()->GetPokeballs()->BallThrowing())
	{
		textrendering = true;
		*battleSeq = UsingPokeball;
	}




	if (btPlayer->GetPlayerItem()->GetPokeballs()->GetPokemonGetRender())
	{
		*battleSeq = GotchaPokemon;
		textrendering = true;
	}

	if (battlebackground->GetFight() == true && *battleSeq == DamageCalc) // 데미지 계산 및 반영
	{
		battlebackground->SetEnemyTurn();
		cout << "플레이어 데미지 계산 시작" << endl;
		Damage(selectSkill);
		HpUpdate();
	}

	if (textrendering && playerturn) // 텍스트 출력
	{

		switch (*battleSeq)
		{
		case ResultPop:
			battlebackground->PlayerTextRender(battleSeq);
			break;
		case SwitchingPokemon:
			break;
		case UsingPokeball:
			battlebackground->PlayerTextRender(battleSeq);
			break;
		case GotchaPokemon:
			battlebackground->PlayerTextRender(battleSeq);
			break;
		case TextRendering:
			battlebackground->PlayerTextRender(btPlayer->GetcurrentPokemon()->GetSkillData(selectSkill).name, battleSeq);
			break;

		default:
			break;
		}

	}

}

void NPCBattle::EnemyTurn()
{


	if (enemyBattleSeq == SelectSkill)
	{
		cout << "몬스터 스킬선택 시작" << endl;
		enemySelect = (rand() % 4) + 1;
		if (NPCPokemon->GetSkillData(enemySelect).ptype != TypeNull)
		{
			cout << "몬스터 스킬선택 완료" << endl;
			enemyBattleSeq = DamageCalc;
		}

	}

	if (battleover == false && enemyBattleSeq == DamageCalc)
	{
		cout << "몬스터 데미지 계산 시작" << endl;
		Damage(enemySelect);
		HpUpdate();
	}

	if (textrendering && !playerturn) // 텍스트 출력
	{
		battlebackground->EnemyTextRender(NPCPokemon->GetSkillData(enemySelect).name, &enemyBattleSeq);
	}

}

/*
(데미지 = (((((((레벨 × 2 ÷ 5) + 2) × 위력 × 특수공격 ÷ 50) ÷ 특수방어) × Mod1) + 2) × [[급소]] × Mod2) × 자속보정 × 타입상성1 × 타입상성2 × 랜덤수 ÷ 100)
*/

void NPCBattle::Damage(int selectSkill)
{
	if (playerturn)
	{
		int power = 0, level = 0, atk = 0, def = 0, damage = 0, random = 0;
		SkillType skilltype;
		power = btPlayer->GetcurrentPokemon()->GetSkillData(selectSkill).power;
		level = btPlayer->GetcurrentPokemon()->GetPKData().level;
		skilltype = btPlayer->GetcurrentPokemon()->GetSkillData(selectSkill).stype;
		random = ((217 + (rand() % 39)) * 100) / 255;
		switch (skilltype)
		{
		case PhysicsType:
			atk = btPlayer->GetcurrentPokemon()->GetStat()->GetStatus().atk;
			def = NPCPokemon->GetStat()->GetStatus().def;
			break;
		case SpecialType:
			atk = btPlayer->GetcurrentPokemon()->GetStat()->GetStatus().sAtk;
			def = NPCPokemon->GetStat()->GetStatus().sDef;
			break;
		case ChangeType:
			atk = 1;
			def = 1;
			break;
		default:
			break;
		}

		damage = ((((((level * 2 / 5) + 2) * power * atk / 50) / def) + 2) * random / 100) + 1;
		cout << damage << endl;
		if (NPCPokemon->GetPKData().currentHp > damage)
		{
			NPCPokemon->SetDamage(damage);
			*battleSeq = TextRendering;
			textrendering = true;
			cout << "플레이어 데미지 계산 완료" << endl;
		}
		else if (NPCPokemon->GetPKData().currentHp <= damage)
		{
			if (npcPokemonNum == currentnpcPokemonNum)
			{
				NPCPokemon->SetDamage(damage);
				*battleSeq = ResultPop;
				textrendering = true;
				btPlayer->GetcurrentPokemon()->EarnExp(5000);
				CalcExpPercent();
				if (btPlayer->GetcurrentPokemon()->GetLevelUp())
				{
					battlebackground->SetLevelUp();
				}
			}
			else
			{
				NPCPokemon->SetDamage(damage);
				*battleSeq = TextRendering;
				textrendering = true;
				cout << "플레이어 데미지 계산 완료" << endl;
				currentnpcPokemonNum += 1;
				btNPC->SetcurrentPokemon(currentnpcPokemonNum);
				NPCPokemon = btNPC->GetcurrentPokemon();
				battlebackground->SetPokemon(NPCPokemon);
			}
			
		}

	}
	else if (playerturn == false)
	{
		int power = 0, level = 0, atk = 0, def = 0, damage = 0, random = 0;
		SkillType skilltype;
		power = NPCPokemon->GetSkillData(selectSkill).power;
		level = NPCPokemon->GetPKData().level;
		skilltype = NPCPokemon->GetSkillData(selectSkill).stype;
		random = ((217 + (rand() % 39)) * 100) / 255;
		switch (skilltype)
		{
		case PhysicsType:
			atk = NPCPokemon->GetStat()->GetStatus().atk;
			def = btPlayer->GetcurrentPokemon()->GetStat()->GetStatus().def;
			break;
		case SpecialType:
			atk = NPCPokemon->GetStat()->GetStatus().sAtk;
			def = btPlayer->GetcurrentPokemon()->GetStat()->GetStatus().sDef;
			break;
		case ChangeType:
			atk = 1;
			def = 1;
			break;
		default:
			break;
		}

		damage = ((((((level * 2 / 5) + 2) * power * atk / 50) / def) + 2) * random / 100) + 1;
		cout << damage << endl;
		if (btPlayer->GetcurrentPokemon()->GetPKData().currentHp > damage)
		{
			btPlayer->GetcurrentPokemon()->SetDamage(damage);
			enemyBattleSeq = TextRendering;
			textrendering = true;
			cout << "몬스터 데미지 계산 완료" << endl;
		}
		else if (btPlayer->GetcurrentPokemon()->GetPKData().currentHp <= damage)
		{
			if (playerPokemonNum == currentPlayerPokemonNum)
			{
				btPlayer->GetcurrentPokemon()->SetDamage(damage);
				battleover = true;
				NPCBattleEnd();
				btPlayer->SetNPCBattleEnd();
				battlebackground->Reset();
				cout << "enemy win" << endl;
			}
			else
			{
				btPlayer->GetcurrentPokemon()->SetDamage(damage);
				enemyBattleSeq = TextRendering;
				textrendering = true;
				cout << "몬스터 데미지 계산 완료" << endl;
				currentPlayerPokemonNum += 1;
				btPlayer->SetSwitchPokemon(currentPlayerPokemonNum);
			}
			
		}

	}

}

void NPCBattle::BattlePhase()
{
	if (*battleSeq == Wait)
	{
		battlebackground->SetBattleStart();

	}
	else if (battlebackground->GetBattleEnd())
	{
		*battleSeq = Wait;
		turncount = 2;
		battleover = true;
		textrendering = false;
		battlebackground->Reset();
		cout << "player Win" << endl;
		NPCBattleEnd();
		btPlayer->SetNPCBattleEnd();
	}

	if (battleOn)
	{
		if (turncount == 2)
		{
			if (btPlayer->GetcurrentPokemon()->GetStat()->GetStatus().spd >= NPCPokemon->GetStat()->GetStatus().spd) // 플레이어의 스피드가 빠르거나 같을때 플레이어 선턴
			{
				playerturn = true;
				turncount = 0;
				*battleSeq = TurnStart;
				textrendering = false;
				cout << "플레이어 턴 부터 시작!" << endl;
			}
			else if (btPlayer->GetcurrentPokemon()->GetStat()->GetStatus().spd < NPCPokemon->GetStat()->GetStatus().spd)
			{
				playerturn = false;
				battlebackground->SetEnemyTurn();
				turncount = 0;
				enemyBattleSeq = TurnStart;
				textrendering = false;
				cout << "몬스터 턴 부터 시작" << endl;

			}

		}

		if (playerturn == true)
		{
			if (!textrendering)
			{
				cout << "플레이어 턴 시작" << endl;
				*battleSeq = SelectSkill;
			}

			PlayerTurn();

			if (*battleSeq == TurnEnd) // 턴 종료
			{
				turncount += 1;
				cout << "턴카운트 : " << turncount << endl;
				playerturn = false;
				battlebackground->SetEnemyTurn();
				textrendering = false;
				cout << "player turn end" << endl;

			}
		}
		if (playerturn == false)
		{
			if (!textrendering)
			{
				cout << "몬스터 턴 시작" << endl;
				enemyBattleSeq = SelectSkill;
			}

			EnemyTurn();

			if (enemyBattleSeq == TurnEnd)
			{
				turncount += 1;
				cout << "턴카운트 : " << turncount << endl;
				playerturn = true;
				battlebackground->SetPlayerTurn();
				textrendering = false;
				cout << "Enemy turn end" << endl;
			}
		}

	}




}

void NPCBattle::HpUpdate()
{
	float playerCurrntHP = (float)(btPlayer->GetcurrentPokemon()->GetPKData().currentHp);
	float playerMaxHP = (float)(btPlayer->GetcurrentPokemon()->GetPKData().maxHp);

	playerHpPer = playerCurrntHP / playerMaxHP;
	pHp->SetPercent(playerHpPer);

	float enemycurrntHp = (float)(NPCPokemon->GetPKData().currentHp);
	float enemymaxHp = (float)(NPCPokemon->GetPKData().maxHp);
	enemyHpPer = enemycurrntHp / enemymaxHp;
	eHp->SetPercent(enemyHpPer);

}

void NPCBattle::CalcExpPercent()
{
	int currentExp = btPlayer->GetcurrentPokemon()->GetPKData().exp;
	int nextLevel = btPlayer->GetcurrentPokemon()->GetPKData().level + 1;

	if (btPlayer->GetcurrentPokemon()->GetPKData().exp == 0)
	{
		float percent = 0.0f;
		exp->SetPercent(percent);
	}
	else
	{
		float percent = (float)currentExp / (float)((4 * nextLevel * nextLevel * nextLevel) / 5);
		exp->SetPercent(percent);
	}
}

