#include "stdafx.h"
#include "PMCenterNPC.h"

PMCenterNPC::PMCenterNPC(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TextureNPCPath + L"PMCenterNPCFront.png");
	Texture2D* srcTex2 = new Texture2D(TextureNPCPath + L"PMCenterNPCLeft.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	AnimationClip* front = new AnimationClip(L"Front", srcTex, 1, { 0,0 }, texSize, true);
	AnimationClip* Left = new AnimationClip(L"Left", srcTex2, 1, {0,0}, texSize, true);

	animator->AddAnimClip(front);
	animator->AddAnimClip(Left);
	animator->SetCurrentAnimClip(L"Front");

	animRect->SetAnimation(animator);
	SAFE_DELETE(srcTex);

	collision = new BoundingBox(position, size + Vector3(50,50,1), 0.f, Color(0, 1, 0, 0.35f));
	holding = true;
	interaction = false;
	textrending = false;
	selectHealing = false;
	healing = false;
	textnum = 0;
	deltatime = 0;
	selectArrow = true;
	

	select 		= new ProgressBar({ 440,-100,0 }, { 150,100,0 }, 0.0f, TextureNPCDialogPath + L"DialogSelect.png", UI::LEFT_TO_RIGHT);
	dialog		= new ProgressBar({ -640,-264,0 }, { 1280,192,0 }, 0.0f, TextureNPCDialogPath + L"PMCenterDIALOG1.png", UI::LEFT_TO_RIGHT);
	dialogN1	= new ProgressBar({ -640,-264,0 }, { 1280,192,0 }, 0.0f, TextureNPCDialogPath + L"PMCenterDIALOG(SelectN).png", UI::LEFT_TO_RIGHT);
	dialogY1	= new ProgressBar({ -640,-264,0 }, { 1280,192,0 }, 0.0f, TextureNPCDialogPath + L"PMCenterDIALOG(SelectY).png", UI::LEFT_TO_RIGHT);
	dialogY2	= new ProgressBar({ -640,-264,0 }, { 1280,192,0 }, 0.0f, TextureNPCDialogPath + L"PMCenterDIALOG2.png", UI::LEFT_TO_RIGHT);
	dialogY3	= new ProgressBar({ -640,-264,0 }, { 1280,192,0 }, 0.0f, TextureNPCDialogPath + L"PMCenterDIALOG3.png", UI::LEFT_TO_RIGHT);
	selectY		= new ProgressBar({ 490,-80,0 }, { 20,30,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	selectN		= new ProgressBar({ 490,-120,0 }, { 20,30,0 }, 0.0f, TextureMapBattlePath + L"Select.png", UI::LEFT_TO_RIGHT);
	
	monsterBall1 = new TextureRect({ 2420, 3980, 0.f }, { 20,20,0 }, 0.f, TextureMapMenuPath + L"pokeball.png");
	monsterBall2 = new TextureRect({ 2438, 3980, 0.f }, { 20,20,0 }, 0.f, TextureMapMenuPath + L"pokeball.png");
	monsterBall3 = new TextureRect({ 2420, 3967, 0.f }, { 20,20,0 }, 0.f, TextureMapMenuPath + L"pokeball.png");
	monsterBall4 = new TextureRect({ 2438, 3967, 0.f }, { 20,20,0 }, 0.f, TextureMapMenuPath + L"pokeball.png");
	monsterBall5 = new TextureRect({ 2420, 3954, 0.f }, { 20,20,0 }, 0.f, TextureMapMenuPath + L"pokeball.png");
	monsterBall6 = new TextureRect({ 2438, 3954, 0.f }, { 20,20,0 }, 0.f, TextureMapMenuPath + L"pokeball.png");
	ballLight = new TextureRect({ 2430,3967,0.f }, { 30,40,0 }, 0.f, TextureMapMenuPath + L"ballLight.png");
}

PMCenterNPC::~PMCenterNPC()
{
	SAFE_DELETE(ballLight);
	SAFE_DELETE(monsterBall6);
	SAFE_DELETE(monsterBall5);
	SAFE_DELETE(monsterBall4);
	SAFE_DELETE(monsterBall3);
	SAFE_DELETE(monsterBall2);
	SAFE_DELETE(monsterBall1);
	SAFE_DELETE(selectN);
	SAFE_DELETE(selectY);
	SAFE_DELETE(dialogY3);
	SAFE_DELETE(dialogY2);
	SAFE_DELETE(dialogY1);
	SAFE_DELETE(dialogN1);
	SAFE_DELETE(dialog);
	SAFE_DELETE(select);
	SAFE_DELETE(collision);
}

void PMCenterNPC::Update()
{
	Question();
	select	->Update();
	dialog	->Update();
	dialogN1->Update();
	dialogY1->Update();
	dialogY2->Update();
	dialogY3->Update();
	selectY	->Update();
	selectN	->Update();

	monsterBall1->Update();
	monsterBall2->Update();
	monsterBall3->Update();
	monsterBall4->Update();
	monsterBall5->Update();
	monsterBall6->Update();
	ballLight->Update();

	animRect->Move(holding);
	collision->Update();

	animRect->Update();
	animator->Update();
}

void PMCenterNPC::Render()
{
	animRect->Render();
	collision->Render();

	if (textrending)
	{
		if (textnum == 0)
		{
			select->Render();
			dialog->Render();

			if(selectArrow)
				selectY->Render();
			else
				selectN->Render();
		}
		
		else if (textnum == 1 && selectHealing)
		{
			dialogY1->Render();

			if (deltatime > 0.5f)
			{
				monsterBall1->Render();
			}
			if (deltatime > 1.f)
			{
				monsterBall2->Render();
			}
			if (deltatime > 1.5f)
			{
				monsterBall3->Render();
			}
			if (deltatime > 2.f)
			{
				monsterBall4->Render();
			}
			if (deltatime > 2.5f)
			{
				monsterBall5->Render();
			}
			if (deltatime >= 3.f)
			{
				monsterBall6->Render();
			}
			if ((deltatime >= 3.1f && deltatime <= 3.3f)|| (deltatime >= 3.5f && deltatime <= 3.7f))
			{
				ballLight->Render();
			}
		}
		else if (textnum == 1 && !selectHealing)
		{
			dialogN1->Render();
		}

		else if (textnum == 2 && selectHealing)
		{
			dialogY2->Render();
		}
		else if (textnum == 3 && selectHealing)
		{
			dialogY3->Render();
		}
		

	}
	

	
	
}

bool PMCenterNPC::InterActionNPC(BoundingBox* player)
{
	if (BoundingBox::AABB(player, collision) == true ||
		BoundingBox::OBB(player, collision) == true)
	{
		collision->SetColor(Color(1, 0, 0, 0.35f));
		interaction = true;
	}
	else
	{
		collision->SetColor(Color(0, 1, 0, 0.35f));
	}

	if (interaction && KEYBOARD->Down(VK_SPACE))
		textrending = true;
	
	if (healing)
	{
		Reset();
		return true;
	}
	else
		return false;
}

void PMCenterNPC::Question()
{
	if (textrending)
	{
		if (textnum == 0)
		{
			if (KEYBOARD->Down(VK_UP))
				selectArrow = true;
			if (KEYBOARD->Down(VK_DOWN))
				selectArrow = false;

			if (KEYBOARD->Down(VK_SPACE))
			{
				if (selectArrow)
				{
					selectHealing = true;
					textnum = 1;
				}
				else if (!selectArrow)
				{
					selectHealing = false;
					textnum = 1;
				}
			}
		}
		else if (textnum == 1 && selectHealing)
		{
			if (deltatime > 4)
			{
				textnum = 2;
				deltatime = 0;
				animator->SetCurrentAnimClip(L"Front");

			}
			else
			{
				animator->SetCurrentAnimClip(L"Left");
				deltatime += Time::Delta();
			}
				
		}
		else if (textnum == 1 && !selectHealing)
		{
			if (deltatime > 1)
			{
				Reset();
			}
			else
				deltatime += Time::Delta();
		}
		else if (textnum == 2)
		{
			if (deltatime > 2)
			{
				textnum = 3;
				deltatime = 0;
			}
			else
				deltatime += Time::Delta();
		}
		else if (textnum == 3)
		{
			if (deltatime > 2)
			{
				healing = true;
				deltatime = 0;
			}
			else
				deltatime += Time::Delta();
		}
	}
}

void PMCenterNPC::Reset()
{
	interaction = false;
	textrending = false;
	selectHealing = false;
	healing = false;
	textnum = 0;
	deltatime = 0;
	selectArrow = true;
}
