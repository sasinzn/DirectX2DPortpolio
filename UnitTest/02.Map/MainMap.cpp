#include "stdafx.h"
#include "MainMap.h"


void MainMap::Init()
{
	taechoTown = new TaechoTown();
	sangrokCity = new SangrokCity();
	pmCenter = new PMCenter();
	taechoTown->SetPlaying();
	route01 = new Route01();
	player = new Player({ 665, 3000, 0.f }, { 66,66,1 }); // 605,465,0
	pmcNPC = new PMCenterNPC({ 2500, 3960, 0.f }, { 66,66,1 });
	battleNPC1 = new BattleNPC({ 580,2840,0.f }, { 66,66,1 });
	npcBattleOp = new BattleOpening();
	battleNPC1->SetNPC(1, WEST);
	battleNPC1->AddPokemon();
	enemyPm = new Pokemon(2, 5);
	battle = new Battle(player,enemyPm);
	npcBattle = new NPCBattle(player,battleNPC1);
	bagpack = new ItemBag(player);
	ball = player->GetPlayerItem()->GetPokeballs();
	Texture2D* srcTex = new Texture2D(TextureMapBattlePath + L"battleencounter.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	AnimationClip* battleEncount = new AnimationClip(L"BattleEncount", srcTex, 39, { 0,0 }, { texSize.x, texSize.y });

	animator = new Animator();
	animRect = new AnimationRect({ WinMaxWidth / 2,WinMaxHeight / 2,0 }, { WinMaxWidth,WinMaxHeight,0 });
	animator->AddAnimClip(battleEncount);
	animator->SetCurrentAnimClip(L"BattleEncount");
	animator->SetLoopOff();
	animRect->SetAnimation(animator);

	SAFE_DELETE(srcTex);


	Sounds::Get()->AddSound("TaeChoBGM", SoundPath + L"01-Taecho Town Theme.mp3");
	Sounds::Get()->AddSound("BattleVsTrainer", SoundPath + L"11-Battle VS Trainer.mp3");
	Sounds::Get()->Play("TaeChoBGM", 0.3f);
}

void MainMap::Destroy()
{
	SAFE_DELETE(animRect);
	SAFE_DELETE(animator);
	SAFE_DELETE(bagpack);
	SAFE_DELETE(battle);
	SAFE_DELETE(enemyPm);
	SAFE_DELETE(battleNPC1);
	SAFE_DELETE(pmcNPC);
	SAFE_DELETE(player);
	SAFE_DELETE(route01);
	SAFE_DELETE(pmCenter);
	SAFE_DELETE(sangrokCity);
	SAFE_DELETE(taechoTown);
}

void MainMap::Update()
{
	taechoTown->Update();
	sangrokCity->Update();
	route01->Update();
	bagpack->Update();
	pmCenter->Update();
	

	player->Update();
	player->GetCollision()->UpdateCollisionData();
	pmcNPC->Update();
	pmcNPC->GetCollision()->UpdateCollisionData();
	battleNPC1->Update();
	battleNPC1->GetCollision()->UpdateCollisionData();
	battle->Update();
	npcBattle->Update();
	animRect->SetPosition(player->GetPos());

	CameraMove();
	if (!battle->IsBattle() && !player->GetNPCBattle())
	{
		animator->SetAniReset();
		player->SetMove();
		npcBattleOp->Reset();
	}
	else if (battle->IsBattle() || player->GetNPCBattle())
	{
		player->SetHold();
	}
		

	if (CurrentBattleZone(player->GetCollision()))
	{
		int indexNo = rand() % 3 + 10;
		enemyPm->SetPokemon(indexNo, rand() % 5 + 1);
		battle->HpUpdate();
		battle->SetBattle();
		
	}

	MovingPMC(player->GetCollision());
	InteractionNPC(player->GetCollision());
	BattleWithNPC();

	if (player->GetNPCBattle() && npcBattleOp->GetEndPlaying())
	{
		npcBattle->SetNPCBattle();
		npcBattle->HpUpdate();
	}

	enemyPm->Update();

	if (KEYBOARD->Down(VK_F2))
	{
		if (!Sounds::Get()->IsPaused("TaeChoBGM"))
			Sounds::Get()->Pause("TaeChoBGM");
		else
			Sounds::Get()->Resume("BGM");
	}

	if (KEYBOARD->Down(VK_F3))
		player->AddPokemon(4, 9);

	if (KEYBOARD->Down(VK_F4))
		player->AddPokemon(7, 8);


	ball->Update();


	if (KEYBOARD->Down('I'))
		player->SetOpenItemMenu();

	if (KEYBOARD->Down('P'))
		player->GetPokemonMenu()->OpenPokemonMenu();

	if(KEYBOARD->Down(VK_ESCAPE))
		player->GetPokemonMenu()->ClosePokemonMenu();
	
	if(player->GetItemMenuOpen() || player->GetPokemonMenu()->GetPokemonMenuOpen())
	{
		player->SetHold();
	}

	animator->Update();
	animRect->Update();
	if (!npcBattleOp->GetEndPlaying() && player->GetNPCBattle())
		npcBattleOp->Update();
}

void MainMap::Render()
{
	taechoTown->Render();
	sangrokCity->Render();
	pmCenter->Render();
	route01->Render();
	player->Render();
	pmcNPC->Render();
	battleNPC1->Render();

	if (battle->IsBattle() || player->GetNPCBattle())
		animRect->Render();

	if (animator->GetAniEnd())
	{
		npcBattleOp->SetMoving();
	}
	

	if (animator->GetAniEnd())
	{
		if (battle->IsBattle())
		{
			battle->Render();
			if (!player->GetPokemonMenuOpen() && !player->GetItemMenuOpen())
			{
				if (!player->GetPlayerItem()->GetPokeballs()->BallGotCha() && !player->GetPlayerItem()->GetPokeballs()->GetPlayerPokemonGotcha())
					enemyPm->Render();
				player->GetcurrentPokemon()->Render();
			}
		}
		else if (player->GetNPCBattle() && npcBattleOp->GetEndPlaying())
		{
			npcBattle->Render();
			if (!player->GetPokemonMenuOpen() && !player->GetItemMenuOpen())
			{
				//				player->GetcurrentPokemon()->Render();
				//				battleNPC1->GetcurrentPokemon()->Render();
			}
		}
	}

	

	if(!npcBattleOp->GetEndPlaying() && player->GetNPCBattle())
		npcBattleOp->Render();
	
	bagpack->Render();
	ball->Render();
}

void MainMap::PostRender()
{
}

void MainMap::GUI()
{
}


bool MainMap::CurrentBattleZone(BoundingBox* player) // 각 맵의 포켓몬 출현구역에서 충돌박스 검사 및 몬스터 출현 검사
{
	return route01->Battle(player, battle->IsBattle());
}

void MainMap::MovingPMC(BoundingBox* player)
{
	if (sangrokCity->MovingPMC(player))
	{
		sangrokCity->MovePMCenter(this->player);
		this->player->EnterPMCenter();
	}
	
	if (pmCenter->OutPmc(player))
	{
		pmCenter->MoveReRoll(this->player);
		this->player->OutPMCenter();
	}
}

void MainMap::InteractionNPC(BoundingBox* player)
{
	if (pmcNPC->InterActionNPC(player))
	{
		this->player->AllPokemonHealing();
	}
}

void MainMap::CameraMove()
{
	if (!battle->IsBattle())
	{
	//	CAMERA->CameraPick(player->GetPos());
	}
	if (player->GetItemMenuOpen() || player->GetPokemonMenu()->GetPokemonMenuOpen())
	{
		CAMERA->CameraPick({ WinMaxWidth / 2, WinMaxHeight / 2,0 });
	}
	else if (animator->GetAniEnd())
	{
		CAMERA->CameraPick({ WinMaxWidth / 2, WinMaxHeight / 2,0 });
	}
	/*else if (npcBattleOp->GetEndPlaying())
	{
		CAMERA->CameraPick({ WinMaxWidth / 2, WinMaxHeight / 2,0 });
	}*/
	else if (player->GetVisitPMC())
	{
		CAMERA->CameraPick({ 2500, 3840, 0.f });
	}
	else
	{
		CAMERA->CameraPick(player->GetPos());
	}

}

void MainMap::BattleWithNPC()
{
	if (battleNPC1->InterActionNPC(player->GetCollision()))
	{
		player->SetNPCBattle();
		battleNPC1->SetInterActionOFF();
		Sounds::Get()->Stop("TaeChoBGM");
		Sounds::Get()->Play("BattleVsTrainer", 0.3f);
	}
		
}





