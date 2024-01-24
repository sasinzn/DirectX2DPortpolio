#pragma once

class ExpBar
{
public:
	ExpBar(Vector3 position, Vector3 size);
	~ExpBar();

	void Update();
	void Render();
	void SetPercent(float percent);

private:
	class ProgressBar* EXP = nullptr;
	float percent = 0.0f;


};