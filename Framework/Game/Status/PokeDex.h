#pragma once
#include "Utilities/Animator.h"

struct LearnSkill
{
	vector<int> skills; //레벨업으로 배우는 스킬목록
};

// 종족값. 도감번호, 포켓몬 이름, 스프라이트 (포켓몬 도감 기초정보)
class PokeDex
{
public:
	PokeDex();
	~PokeDex();
	
	void Load(string path);
	StatusData GetTribe(int indexNum) { return tribe[indexNum - 1]; }					// 종족값
	LearnSkill GetLearnSkills(int indexNum) { return studySkills[indexNum-1]; }
	string GetIndexName(int indexNum) { return indexName[indexNum - 1]; }			// 도감명
	AnimationClip* GetFrontAni(int indexNum) { return frontAni[indexNum - 1]; }		// 포켓몬 스프라이트 전면
	AnimationClip* GetBackAni(int indexNum) { return backAni[indexNum - 1]; }		// 포켓몬 스프라이트 후면
	PmType GetPMType(int indexNum) { return PokemonType[indexNum - 1]; }
	bool GetRevolution(int indexNum) { return revolution[indexNum - 1]; }
	int GetRevolutionLevel(int indexNum) { return revolutionLevel[indexNum - 1]; }
	int GetRevolutionIndexNo(int indexNum) { return nextIndexNo[indexNum - 1]; }


	PmType ConvertTypePM(int num);

private:

	StatusData tribe[151]; // 종족값
	PmType PokemonType[151]; // 포켓몬 타입
	bool revolution[151]; // 진화 가능 여부
	int revolutionLevel[151]; // 진화 가능 레벨
	int nextIndexNo[151]; //진화후 도감 번호
	LearnSkill studySkills[151]; //레벨업으로 배우는 스킬목록
	vector<string> indexName; // 포켓몬 도감명
	vector<Texture2D*> frontSrcTex;
	vector<Texture2D*> backSrcTex;
	AnimationClip* frontAni[151]; // 포켓몬 스프라이트 전면
	AnimationClip* backAni[151]; // 포켓몬 스프라이트 후면
	
};

/*
능력치 계산법
- HP
 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) + 100 } x 레벨Lv/100 ] + 10
- ATK, DEF, sATK, sDEF, SPD
 능력치 = [ { (종족값a x 2) + 개체값b + (노력치c/4) } x 레벨Lv/100 + 5 [10]] x 성격보정d
*/