#pragma once

class HUD
{
public:
	HUD();
	~HUD();

	void Update();
	void Render();

private:
	class ProgressBar* HP = nullptr;

	float percent = 1.0f;


};