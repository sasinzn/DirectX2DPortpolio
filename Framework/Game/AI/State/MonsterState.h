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

	virtual void OnStateEnter(); // state ó�� ���������� ȣ��Ǵ� �Լ�
	virtual void OnStateUpdate(); // �� frame���� ȣ��Ǵ� �Լ�
	virtual void OnStateExit(); // state ����� ȣ��Ǵ� �Լ�

protected:
	void SetPokemon(Pokemon* _pokemon) { pokemon = _pokemon; } // �⺻�����ڷ� ������ ���ϸ� ���� �Լ�

protected:
	Pokemon* pokemon;
};