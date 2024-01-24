#pragma once
#include "Utilities/Animator.h"

struct LearnSkill
{
	vector<int> skills; //���������� ���� ��ų���
};

// ������. ������ȣ, ���ϸ� �̸�, ��������Ʈ (���ϸ� ���� ��������)
class PokeDex
{
public:
	PokeDex();
	~PokeDex();
	
	void Load(string path);
	StatusData GetTribe(int indexNum) { return tribe[indexNum - 1]; }					// ������
	LearnSkill GetLearnSkills(int indexNum) { return studySkills[indexNum-1]; }
	string GetIndexName(int indexNum) { return indexName[indexNum - 1]; }			// ������
	AnimationClip* GetFrontAni(int indexNum) { return frontAni[indexNum - 1]; }		// ���ϸ� ��������Ʈ ����
	AnimationClip* GetBackAni(int indexNum) { return backAni[indexNum - 1]; }		// ���ϸ� ��������Ʈ �ĸ�
	PmType GetPMType(int indexNum) { return PokemonType[indexNum - 1]; }
	bool GetRevolution(int indexNum) { return revolution[indexNum - 1]; }
	int GetRevolutionLevel(int indexNum) { return revolutionLevel[indexNum - 1]; }
	int GetRevolutionIndexNo(int indexNum) { return nextIndexNo[indexNum - 1]; }


	PmType ConvertTypePM(int num);

private:

	StatusData tribe[151]; // ������
	PmType PokemonType[151]; // ���ϸ� Ÿ��
	bool revolution[151]; // ��ȭ ���� ����
	int revolutionLevel[151]; // ��ȭ ���� ����
	int nextIndexNo[151]; //��ȭ�� ���� ��ȣ
	LearnSkill studySkills[151]; //���������� ���� ��ų���
	vector<string> indexName; // ���ϸ� ������
	vector<Texture2D*> frontSrcTex;
	vector<Texture2D*> backSrcTex;
	AnimationClip* frontAni[151]; // ���ϸ� ��������Ʈ ����
	AnimationClip* backAni[151]; // ���ϸ� ��������Ʈ �ĸ�
	
};

/*
�ɷ�ġ ����
- HP
 �ɷ�ġ = [ { (������a x 2) + ��ü��b + (���ġc/4) + 100 } x ����Lv/100 ] + 10
- ATK, DEF, sATK, sDEF, SPD
 �ɷ�ġ = [ { (������a x 2) + ��ü��b + (���ġc/4) } x ����Lv/100 + 5 [10]] x ���ݺ���d
*/