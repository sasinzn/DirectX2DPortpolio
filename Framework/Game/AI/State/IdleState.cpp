#include "Framework.h"
#include "Game/Actor/Pokemon.h"

IdleState::IdleState(Pokemon* _pokemon)
	:MonsterState(_pokemon)
{
}

IdleState::~IdleState()
{
}

void IdleState::OnStateEnter()
{
}

void IdleState::OnStateUpdate()
{
}

void IdleState::OnStateExit()
{
}
