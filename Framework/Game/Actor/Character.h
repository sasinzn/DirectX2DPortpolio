#pragma once

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

class Character
{
public:
	Character(Vector3 position, Vector3 size);
	virtual ~Character();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetPos(Vector3 pos) { animRect->SetPosition(pos); }
	void SetCurrentPos() { currentPos = animRect->GetPosition(); }
	Vector3 GetCurrnetPos() { return currentPos; }
protected:
	Animator* animator;
	AnimationRect* animRect;
	Vector3 currentPos;
};
