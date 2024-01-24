#include "Framework.h"
#include "BattleOpening.h"

BattleOpening::BattleOpening()
{
	BackGround = new TextureRect({ WinMaxWidth / 2,WinMaxHeight / 2,0.f }, { WinMaxWidth,WinMaxHeight,0.f }, 0.f, TextureMapBattlePath + L"background2.png");
	BackGroundTp = new TextureRect({ WinMaxWidth / 2,456,0.f }, { 1200,448,0 }, 0.f, TextureMapBattlePath + L"battleBag.png");
	BackGroundBt = new TextureRect({ WinMaxWidth / 2,136,0.f }, { 1200,192,0 }, 0.f, TextureMapBattlePath + L"battleBag2.png");
	Encounter_NPC = new TextureRect({ 0,500,0 }, { 200,200,0 }, 0.f, TextureMapBattlePath + L"Traner1.png");
	Encounter_Player = new TextureRect({ 1280,300,0 }, { 200,200,0 }, 0.f, TextureMapBattlePath + L"Player.png");
	Dialog = new TextureRect({ WinMaxWidth / 2,136,0.f }, { 1200,192,0 }, 0.f, TextureNPCDialogPath + L"BattleNPCDialog1.png");


	Texture2D* srcTex_Player = new Texture2D(TextureMapBattlePath + L"PlayerThrowBall.png");
	Vector2 texSize_Player = Vector2(srcTex_Player->GetWidth(), srcTex_Player->GetHeight());
	AnimationClip* battleEncount_Player = new AnimationClip(L"BattleEncount_Player", srcTex_Player, 5, { 0,0 }, { texSize_Player.x, texSize_Player.y },false,0.2f);

	animator_Player = new Animator();
	animRect_Player = new AnimationRect({ 340,300,0 }, { 200,200,0 });
	animator_Player->AddAnimClip(battleEncount_Player);
	animator_Player->SetCurrentAnimClip(L"BattleEncount_Player");
	animator_Player->SetLoopOff();
	animRect_Player->SetAnimation(animator_Player);

	PlayerPos[0] = { 1190, 300, 0};
	PlayerPos[1] = { 1100, 300, 0 };
	PlayerPos[2] = { 1000, 300, 0 };
	PlayerPos[3] = { 910, 300, 0 };
	PlayerPos[4] = { 820, 300, 0 };
	PlayerPos[5] = { 730, 300, 0 };
	PlayerPos[6] = { 640, 300, 0 };
	PlayerPos[7] = { 550, 300, 0 };
	PlayerPos[8] = { 450, 300, 0 };
	PlayerPos[9] = { 340, 300, 0 };

	NPCPos[0] = { 90,500,0 };
	NPCPos[1] = { 180,500,0 };
	NPCPos[2] = { 270,500,0 };
	NPCPos[3] = { 360,500,0 };
	NPCPos[4] = { 450,500,0 };
	NPCPos[5] = { 540,500,0 };
	NPCPos[6] = { 630,500,0 };
	NPCPos[7] = { 720,500,0 };
	NPCPos[8] = { 810,500,0 };
	NPCPos[9] = { 900,500,0 };
}

BattleOpening::~BattleOpening()
{
	SAFE_DELETE(Dialog);
	SAFE_DELETE(Encounter_Player);
	SAFE_DELETE(Encounter_NPC);
	SAFE_DELETE(BackGroundBt);
	SAFE_DELETE(BackGroundTp);
	SAFE_DELETE(BackGround);
}

void BattleOpening::Update()
{
	BackGround->Update();
	BackGroundTp->Update();
	BackGroundBt->Update();
	Encounter_NPC->Update();
	Encounter_Player->Update();
	Dialog->Update();

	if (moving && !SummonBall)
	{
		PosMoving();
		cout << "플레이어, NPC 위치 조정중" << endl;
	}
	
	if(SummonBall)
	{
		animRect_Player->Update();
		cout << "플레이어 몬스터 소환중" << endl;
	}
	

	if (animator_Player->GetAniEnd())
	{
		endPlaying = true;
		moving = false;
		SummonBall = false;
	}
}

void BattleOpening::Render()
{
	BackGround->Render();
	BackGroundTp->Render();
	BackGroundBt->Render();

	if (moving && !SummonBall)
	{
		Dialog->Render();
		Encounter_NPC->Render();
		Encounter_Player->Render();
	}

	if (SummonBall)
	{
		Dialog->Render();
		Encounter_NPC->Render();
		animRect_Player->Render();
	}
}

void BattleOpening::Reset()
{
	if (!moving && !SummonBall)
	{
		animator_Player->SetAniReset();
		endPlaying = false;
		SummonBall = false;
		moving = false;
		deltaTime = 0.f;
		num = 0;
	}
}

void BattleOpening::PosMoving()
{

	if (num > 27)
	{
		SummonBall = true;
		moving = false;
		animator_Player->SetAniReset();
		cout << deltaTime << endl;
	}
	else
	{
		num++;
		Encounter_NPC->SetPosition(NPCPos[num/3]);
		Encounter_Player->SetPosition(PlayerPos[num/3]);
		
	}
		
	


	
	
}
