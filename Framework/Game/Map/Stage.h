#pragma once

class StageClip
{

public:
	friend class Stage;
	StageClip(wstring stageName, Texture2D* srcTex, Vector3 size);
	void SetStageRoute(int dir, wstring stageName) { isNextStage[dir] = true; nextStage[dir] = stageName; }
	wstring GetStageRoute(int dir);
	bool ISStageRoute(int dir) { return isNextStage[dir]; }

protected:
	wstring stageName = L"";
	ID3D11ShaderResourceView* srv = nullptr;
	Vector3 size;
	wstring nextStage[4] = { L" " };
	bool isNextStage[4] = { false };
};

class Stage
{
public:
	Stage();
	~Stage();

	void Update();
	void AddStage(StageClip* stage);
	void SetCurrentStage(wstring stageName);
	Vector3 GetSize(wstring stageName);

	ID3D11ShaderResourceView* GetCurrentSRV() { return currentStage->srv; }
	StageClip* GetCurrentStage() { return currentStage; }
private:
	bool CheckExist(wstring clipName) { return stageLibrary.find(clipName) != stageLibrary.end(); }

private:


	unordered_map<wstring, StageClip*> stageLibrary;

	StageClip* currentStage = nullptr;


};