#pragma once
#include "Game/AI/State/MonsterState.h"

class IdleState : protected MonsterState
{
public:
	IdleState();
	IdleState(Pokemon* pokemon);
	~IdleState();

	// BaseState을(를) 통해 상속됨
	void OnStateEnter() override;
	void OnStateUpdate() override;
	void OnStateExit() override;
};