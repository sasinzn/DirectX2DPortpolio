#pragma once

class HpBar
{
public:
	HpBar(Vector3 position, Vector3 size);
	~HpBar();

	void Update();
	void Render();
	void SetPercent(float percent);

private:
	class ProgressBar* playerHpGreen = nullptr;
	class ProgressBar* playerHpYellow = nullptr;
	class ProgressBar* playerHpRed = nullptr;
	

	float percent = 1.0f;


};