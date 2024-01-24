#include "Framework.h"
#include "HpBar.h"

#include "Game\UI\ProgressBar.h"

HpBar::HpBar(Vector3 position, Vector3 size)
{
	
	playerHpGreen	= new ProgressBar(position, size, 0.0f, TextureMapBattlePath + L"HPGREEN.png", UI::LEFT_TO_RIGHT);
	playerHpYellow	= new ProgressBar(position, size, 0.0f, TextureMapBattlePath + L"HPYELLOW.png", UI::LEFT_TO_RIGHT);
	playerHpRed		= new ProgressBar(position, size, 0.0f, TextureMapBattlePath + L"HPRED.png", UI::LEFT_TO_RIGHT);

	playerHpGreen->UpdateProgressBar(percent);
	playerHpYellow->UpdateProgressBar(percent);
	playerHpRed->UpdateProgressBar(percent);
}

HpBar::~HpBar()
{
	SAFE_DELETE(playerHpRed);
	SAFE_DELETE(playerHpYellow);
	SAFE_DELETE(playerHpGreen);
}

void HpBar::Update()
{
	playerHpGreen->Update();
	playerHpYellow->Update();
	playerHpRed->Update();
}

void HpBar::Render()
{

	if(percent > 0.5f)
		playerHpGreen->Render();
	else if(percent <= 0.5f && percent > 0.2f)
		playerHpYellow->Render();
	else
		playerHpRed->Render();

}

void HpBar::SetPercent(float percent)
{
	this->percent = percent;

	playerHpGreen->UpdateProgressBar(this->percent);
	playerHpYellow->UpdateProgressBar(this->percent);
	playerHpRed->UpdateProgressBar(this->percent);
}
