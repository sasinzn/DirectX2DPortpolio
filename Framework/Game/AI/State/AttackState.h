#pragma once

#include "Game/AI/State/MonsterState.h"
#include "Game/Actor/Pokemon.h"

class AttackState : protected MonsterState
{
public:
	AttackState();
	AttackState(Pokemon* pokemon);
	~AttackState();


	// BaseState을(를) 통해 상속됨
	void OnStateEnter() override;
	void OnStateUpdate() override;
	void OnStateExit() override;

};