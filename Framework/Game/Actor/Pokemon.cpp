#include "Framework.h"
#include "Pokemon.h"

#include "Game\Status\Skills.h"
#include "Game\Status\Status.h"
#include "Game\Status\PkType.h"

Pokemon::Pokemon(int indexNo, int level, bool playerPokemon)
{
	pDex = new PokeDex;
	pSkill = new Skill;
	stat = new Status(indexNo, level);

	revolution = pDex->GetRevolution(indexNo);
	revolutionLevel = pDex->GetRevolutionLevel(indexNo);
	revolutionIndexNo = pDex->GetRevolutionIndexNo(indexNo);

	skills[0] = *pSkill->GetSkillData(0);
	skills[1] = *pSkill->GetSkillData(0);
	skills[2] = *pSkill->GetSkillData(0);
	skills[3] = *pSkill->GetSkillData(0);

	int temp = 0;
	int size = pDex->GetLearnSkills(indexNo).skills.size();

	for (int i = 0; i< size; i++)
	{
		temp = pDex->GetLearnSkills(indexNo).skills[i];
		learnSkills.push_back(pSkill->GetSkillData(temp));
	}
	SetSkill(level);
	pInfo.indexNo = indexNo;
	pInfo.indexName = pDex->GetIndexName(indexNo);
	pInfo.level = level;
	pInfo.exp = 0;
	pInfo.name = pInfo.indexName;
	pInfo.maxHp = stat->GetStatus().hp;
	pInfo.currentHp = stat->GetStatus().hp;
	pInfo.skill1PP = skills[0].pp;
	pInfo.skill1currentPP = skills[0].pp;
	pInfo.skill2PP = skills[1].pp;
	pInfo.skill2currentPP = skills[1].pp;
	pInfo.skill3PP = skills[2].pp;
	pInfo.skill3currentPP = skills[2].pp;
	pInfo.skill4PP = skills[3].pp;
	pInfo.skill4currentPP = skills[3].pp;

	if (playerPokemon)
	{
		animator = new Animator();
		animRect = new AnimationRect({ 340,300,0 }, { 200,200,0 });
		animator->AddAnimClip(pDex->GetBackAni(indexNo));
		wstring clipname = String::ToWString(pDex->GetIndexName(indexNo));
		animator->SetCurrentAnimClip(clipname);
		animRect->SetAnimation(animator);
	}
	else
	{
		animator = new Animator();
		animRect = new AnimationRect({ 900,500,0 }, { 200,200,0 });

		animator->AddAnimClip(pDex->GetFrontAni(indexNo));
		wstring clipname = String::ToWString(pDex->GetIndexName(indexNo));
		animator->SetCurrentAnimClip(clipname);
		animRect->SetAnimation(animator);
	}
	
}

Pokemon::~Pokemon()
{
	SAFE_DELETE(stat);
	SAFE_DELETE(pSkill);
	SAFE_DELETE(pDex);
}

void Pokemon::Update()
{
	animRect->Update();
	animator->Update();


}

void Pokemon::Render()
{
	animRect->Render();
}

void Pokemon::SetPokemon(int indexNo, int level, bool playerPokemon)
{
	skills[0] = *pSkill->GetSkillData(0);
	skills[1] = *pSkill->GetSkillData(0);
	skills[2] = *pSkill->GetSkillData(0);
	skills[3] = *pSkill->GetSkillData(0);

	learnSkills.clear();
	int temp = 0;
	int size = pDex->GetLearnSkills(indexNo).skills.size();

	for (int i = 0; i < size; i++)
	{
		temp = pDex->GetLearnSkills(indexNo).skills[i];
		learnSkills.push_back(pSkill->GetSkillData(temp));
	}

	stat->SetStatus(indexNo, level);
	SetSkill(level);
	pInfo.indexNo = indexNo;
	pInfo.indexName = pDex->GetIndexName(indexNo);
	pInfo.level = level;
	pInfo.exp = 0;
	pInfo.name = pInfo.indexName;
	pInfo.maxHp = stat->GetStatus().hp;
	pInfo.currentHp = stat->GetStatus().hp;
	pInfo.skill1PP = skills[0].pp;
	pInfo.skill1currentPP = skills[0].pp;
	pInfo.skill2PP = skills[1].pp;
	pInfo.skill2currentPP = skills[1].pp;
	pInfo.skill3PP = skills[2].pp;
	pInfo.skill3currentPP = skills[2].pp;
	pInfo.skill4PP = skills[3].pp;
	pInfo.skill4currentPP = skills[3].pp;


	if (playerPokemon)
	{
		animator->AddAnimClip(pDex->GetBackAni(indexNo));
		wstring clipname = String::ToWString(pDex->GetIndexName(indexNo));
		animator->SetCurrentAnimClip(clipname);
		animRect->SetAnimation(animator);
	}
	else
	{
		animator->AddAnimClip(pDex->GetFrontAni(indexNo));
		wstring clipname = String::ToWString(pDex->GetIndexName(indexNo));
		animator->SetCurrentAnimClip(clipname);
		animRect->SetAnimation(animator);
	}


	
}

void Pokemon::SetSkill(int level)
{
	if (learnSkills.size() > 4)
	{
		skills[0] = *learnSkills[0];
		skills[1] = *learnSkills[1];

		if (level > 0)
			skills[2] = *learnSkills[2];

		if (level > 0)
			skills[3] = *learnSkills[3];
	}
	else if (learnSkills.size() == 3)
	{
		skills[0] = *learnSkills[0];
		skills[1] = *learnSkills[1];

		if (level > 0)
			skills[2] = *learnSkills[2];
	}
	else if (learnSkills.size() == 2)
	{
		skills[0] = *learnSkills[0];
		skills[1] = *learnSkills[1];
	}
	else if (learnSkills.size() == 1)
	{
		skills[0] = *learnSkills[0];
	}


}



void Pokemon::SetDamage(int damage)
{
	if (pInfo.currentHp > damage)
		pInfo.currentHp -= damage;
	else if (pInfo.currentHp <= damage)
		pInfo.currentHp = 0;

}

void Pokemon::VisitPMCenter()
{
	pInfo.currentHp = pInfo.maxHp;
	pInfo.skill1currentPP = pInfo.skill1PP;
	pInfo.skill2currentPP = pInfo.skill2PP;
	pInfo.skill3currentPP = pInfo.skill3PP;
	pInfo.skill4currentPP = pInfo.skill4PP;
}

void Pokemon::EarnExp(int exp)
{
	int nextLevel = pInfo.level + 1;
	int expNext = (4 * nextLevel * nextLevel * nextLevel) / 5;

	int currentExp = pInfo.exp + exp;
	pInfo.exp = 0;
	if (currentExp < expNext)
		pInfo.exp += currentExp;
	else if (currentExp > expNext)
	{
		LevelUp();
		EarnExp(currentExp - expNext);
	}
		
}

void Pokemon::LevelUp()
{
	stat->LevelUp();
	pInfo.level++;
	pInfo.maxHp = stat->GetStatus().hp;
//	pInfo.currentHp = stat->GetStatus().hp;
	levelup = true;
}

void Pokemon::StrangeCandyEat()
{
	stat->LevelUp();
	pInfo.level++;
	pInfo.maxHp = stat->GetStatus().hp;
	usingitemcount++;
	cout << "이상한 사탕 사용" << endl;
}

void Pokemon::UsingSkill(int skillnum)
{
	switch (skillnum)
	{
	case 1:
		if (pInfo.skill1currentPP == 0)
			break;
		pInfo.skill1currentPP--;
		break;
	case 2:
		if (pInfo.skill2currentPP == 0)
			break;
		pInfo.skill2currentPP--;

		break;

	case 3:
		if (pInfo.skill3currentPP == 0)
			break;
		pInfo.skill3currentPP--;
		break;

	case 4:
		if (pInfo.skill4currentPP == 0)
			break;
		pInfo.skill4currentPP--;

		break;
	}

}

bool Pokemon::NotEnoughPP(int skillnum)
{
	switch (skillnum)
	{
	case 1:
		if (pInfo.skill1currentPP == 0)
			return false;
		break;
	case 2:
		if (pInfo.skill2currentPP == 0)
			return false;
		break;

	case 3:
		if (pInfo.skill3currentPP == 0)
			return false;
		break;

	case 4:
		if (pInfo.skill4currentPP == 0)
			return false;
		break;
	}

	return true;
}

void Pokemon::UsingItem(int itemcode)
{

	/*
	x0000 - 아이템 카테고리
	1xxxx - 회복
	2xxxx - 상태이상
	3xxxx - 능력치
	4xxxx -
	5xxxx -
	6xxxx -
	7xxxx -
	8xxxx -
	9xxxx -

	0x000 - 아이템적용범위
	x1000 - 상태이상
	x2000 - HP
	x3000 - PP 1개
	x4000 - PP 전체
	x5000 - LV
	x6000 - 상태이상&HP
	x7000 - 기절&HP
	x8000 -
	x9000 -
	*/

	int code1 = itemcode / 10000; // 아이템 분류
	int code2 = (itemcode % 10000) / 1000; // 2차 아이템 분류


	switch (code1)
	{
	case 1:	// 회복

		break;

	case 2: // 상태이상

		break;

	case 3: // 능력치

		break;


	default:
		break;
	}


}

void Pokemon::Healing(int num)
{
	if (pInfo.currentHp + num > pInfo.maxHp)
		pInfo.currentHp = pInfo.maxHp;
	else
		pInfo.currentHp += num;


}


