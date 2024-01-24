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
	int level;			//����
	int indexNo;		//���� �ѹ�
	string indexName;
	StatusData stat = { 0 };	//���� ���ϸ� �ɷ�ġ ������,��ü��,���ġ �ݿ�
	StatusData tribeValue = { 0 }; // ������ �ش� ���ϸ��� ���� �⺻ �ɷ�ġ ������ 151���� ���� �ѹ� ����
	StatusData entityValue = { 0 }; // ��ü�� �������� �������� ������ 0~31
	StatusData effortValue = { 0 }; // ���ġ ������ ���� ������ �Ʒ����� �ö󰡴� ��ġ �ִ� 510���� �� �ɷ�ġ�� 252���� ����

	class PokeDex* tribe = nullptr;
};

/*
�ɷ�ġ ����

- HP
 �ɷ�ġ = [ { (������a x 2) + ��ü��b + (���ġc/4) + 100 } x ����Lv/100 ] + 10

- ATK, DEF, sATK, sDEF, SPD
 �ɷ�ġ = [ { (������a x 2) + ��ü��b + (���ġc/4) } x ����Lv/100 + 5 [10]] x ���ݺ���d
*/
