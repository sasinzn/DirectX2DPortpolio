#pragma once

#include "GeoMetries\TextureRect.h"
#include "Stage.h"

class Map : public TextureRect
{
public:
	Map(Vector3 position, Vector3 size);
	~Map();
	
	virtual void Update();
	virtual void Render();

	void SetStage(wstring stage) { this->stage->SetCurrentStage(stage); TextureRect::SetSize(this->stage->GetSize(stage)); }
	void SetPosition(Vector3 pos) { TextureRect::SetPosition(pos); }

	void StateTrans() { if (isPlaying) isPlaying = false; else isPlaying = true; }
	
	bool GetPlaying() { return isPlaying; }
	Stage* GetStage() { return stage; }
private:
	class Stage* stage;
	bool isPlaying = true;
};
