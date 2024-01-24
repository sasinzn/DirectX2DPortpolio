#pragma once
#include "Game/AI/State/MonsterState.h"

class IdleState : protected MonsterState
{
public:
	IdleState();
	IdleState(Pokemon* pokemon);
	~IdleState();

	// BaseState��(��) ���� ��ӵ�
	void OnStateEnter() override;
	void OnStateUpdate() override;
	void OnStateExit() override;
};