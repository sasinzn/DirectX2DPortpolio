#pragma once
#include "PokeDex.h"


class Status
{
public:
	Status(int indexNo, int level);
	~Status();
	void LevelUp();
	void LevelUp(int level);

	void SetStatus(int indexNo, int level);
	StatusData GetStatus() { return stat; }
	

private:
	int level;			//레벨
	int indexNo;		//도감 넘버
	string indexName;
	StatusData stat = { 0 };	//실제 포켓몬 능력치 종족값,개체값,노력치 반영
	StatusData tribeValue = { 0 }; // 종족값 해당 포켓몬의 종족 기본 능력치 데이터 151마리 도감 넘버 기준
	StatusData entityValue = { 0 }; // 개체값 생성직후 랜덤으로 정해짐 0~31
	StatusData effortValue = { 0 }; // 노력치 생성된 이후 전투나 훈련으로 올라가는 수치 최대 510까지 한 능력치당 252까지 가능

	class PokeDex* tribe = nullptr;
};

/*
능력치 계산법

- HP
 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) + 100 } x 레벨Lv/100 ] + 10

- ATK, DEF, sATK, sDEF, SPD
 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) } x 레벨Lv/100 + 5 [10]] x 성격보정d
*/
