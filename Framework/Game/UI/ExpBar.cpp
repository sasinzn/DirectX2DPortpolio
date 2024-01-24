#include "Framework.h"
#include "ExpBar.h"

#include "Game\UI\ProgressBar.h"

ExpBar::ExpBar(Vector3 position, Vector3 size)
{
	EXP = new ProgressBar(position, size, 0.0f, TextureMapBattlePath + L"PLAYEREXP.png", UI::LEFT_TO_RIGHT);
}

ExpBar::~ExpBar()
{
	SAFE_DELETE(EXP);
}

void ExpBar::Update()
{

	EXP->Update();
}

void ExpBar::Render()
{
	EXP->Render();
}

void ExpBar::SetPercent(float percent)
{
	this->percent = percent; 
	EXP->UpdateProgressBar(percent);
}
