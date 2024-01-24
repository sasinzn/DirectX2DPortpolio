#include "Framework.h"
#include "AttackState.h"

AttackState::AttackState(Pokemon* _pokemon)
	:MonsterState(_pokemon)
{
}

AttackState::~AttackState()
{
}

void AttackState::OnStateEnter()
{
}

void AttackState::OnStateUpdate()
{
}

void AttackState::OnStateExit()
{
}
