#include "Framework.h"
#include "Stage.h"



StageClip::StageClip(wstring stageName, Texture2D* srcTex, Vector3 size)
	:stageName(stageName), size(size)
{
	srv = srcTex->GetSRV();
}

wstring StageClip::GetStageRoute(int dir)
{
	if(isNextStage[dir])
		return nextStage[dir];
}

Stage::Stage()
{
}

Stage::~Stage()
{
	for (auto clip : stageLibrary)
		SAFE_DELETE(clip.second);
}

void Stage::Update()
{
}

void Stage::AddStage(StageClip* stage)
{
	stageLibrary.insert(make_pair(stage->stageName, stage));
}


void Stage::SetCurrentStage(wstring stageName)
{
	if (currentStage == nullptr && CheckExist(stageName) == true)
		currentStage = stageLibrary.find(stageName)->second;
	else if (currentStage != nullptr && currentStage->stageName == stageName)
		return;

	if (CheckExist(stageName))
	{
		currentStage = stageLibrary.find(stageName)->second;
	}
}

Vector3 Stage::GetSize(wstring stageName)
{
	if (CheckExist(stageName))
		return stageLibrary.find(stageName)->second->size;

	return Vector3();
}
