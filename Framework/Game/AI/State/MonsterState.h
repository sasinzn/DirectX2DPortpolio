#pragma once

class MonsterState
{
public:
	static IdleState idle;
	static AttackState attack;

public:
	MonsterState();
	MonsterState(Pokemon* _pokemon)
	{
		pokemon = _pokemon;
	}
	~MonsterState();

	virtual void OnStateEnter(); // state 처음 진입했을떄 호출되는 함수
	virtual void OnStateUpdate(); // 매 frame마다 호출되는 함수
	virtual void OnStateExit(); // state 변경시 호출되는 함수

protected:
	void SetPokemon(Pokemon* _pokemon) { pokemon = _pokemon; } // 기본생성자로 생성시 포켓몬 세팅 함수

protected:
	Pokemon* pokemon;
};