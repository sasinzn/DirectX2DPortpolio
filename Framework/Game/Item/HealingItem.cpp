#include "Framework.h"
#include "HealingItem.h"

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

HealingItem::HealingItem()
{
	Texture2D* srcTex = new Texture2D(TextureMapMenuPath + L"HealingItem.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	healingItemClip = new AnimationClip(L"healingItemClip", srcTex, 23, { 0,0 }, texSize);

#pragma region Item name explain 

	// 1. 해독제
	name.push_back("해독제");
	explain.push_back("스프레이식의 약.\n 포켓몬 1마리의 독상태를 회복한다");

	name.push_back("화상치료제");
	explain.push_back("스프레이식의 약.\n 포켓몬 1마리의 화상 상태를 회복한다.");

	name.push_back("얼음상태치료제");
	explain.push_back("스프레이식의 약.\n 포켓몬 1마리의 얼음 상태를 회복한다.");

	name.push_back("잠깨는약");
	explain.push_back("스프레이식의 약.\n 포켓몬 1마리의 잠듦 상태를 회복한다.");

	name.push_back("마비치료제");
	explain.push_back("스프레이식의 약.\n 포켓몬 1마리의 마비 상태를 회복한다.");

	name.push_back("회복약");
	explain.push_back("스프레이식의 상처약.\n 포켓몬 1마리의 HP와 상태이상을 모두 회복한다.");

	name.push_back("풀회복약");
	explain.push_back("스프레이식의 상처약.\n 포켓몬 1마리의 HP를 모두 회복한다.");

	name.push_back("상처약");
	explain.push_back("스프레이식의 상처약.\n 포켓몬 1마리의 HP를 20만큼 회복한다.");

	name.push_back("고급상처약");
	explain.push_back("스프레이식의 상처약.\n 포켓몬 1마리의 HP를 120만큼 회복한다.");

	name.push_back("좋은상처약");
	explain.push_back("스프레이식의 상처약.\n 포켓몬 1마리의 HP를 60만큼 회복한다.");

	name.push_back("만병통치제");
	explain.push_back("스프레이식의 약.\n 포켓몬 1마리의 상태 이상을 모두 회복한다.");

	name.push_back("기력의조각");
	explain.push_back("기절해 버린 포켓몬 1마리를\n 건강하게 하고 HP를 절반까지 회복한다.");

	name.push_back("기력의덩어리");
	explain.push_back("기절해 버린 포켓몬 1마리를\n 건강하게 하고 HP를 모두 회복한다.");

	name.push_back("맛있는물");
	explain.push_back("미네랄이 가득한 물.\n 포켓몬 1마리의 HP를 30만큼 회복한다.");

	name.push_back("미네랄사이다");
	explain.push_back("싸하고 톡 쏘는 사이다.\n 포켓몬 1마리의 HP를 50만큼 회복한다.");

	name.push_back("후르츠밀크");
	explain.push_back("매우 달콤한 쥬스.\n 포켓몬 1마리의 HP를 70만큼 회복한다.");

	name.push_back("PP에이드");
	explain.push_back("포켓몬이 기억하고 있는\n 기술 중 하나의 PP를 10회복한다.");

	name.push_back("PP회복");
	explain.push_back("포켓몬이 기억하고 있는\n 기술 중 하나의 PP를 모두 회복한다.");

	name.push_back("PP에이더");
	explain.push_back("포켓몬이 기억하고 있는\n 모든 기술의 PP를 10회복한다.");

	name.push_back("PP맥스");
	explain.push_back("포켓몬이 기억하고 있는\n 모든 기술의 PP를 모두 회복한다.");

	name.push_back("이상한사탕");
	explain.push_back("에너지가 가득한 사탕.\n 먹이면 포켓몬 1마리의 레벨이 1만큼 올라간다.");

#pragma endregion

}

HealingItem::~HealingItem()
{
}

int HealingItem::HealingNum(int indexNo)
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

	switch (indexNo)
	{
	case 1:
		return 11199; //회복-상태이상-해독제
		break;

	case 2:
		return 11299; //회복-상태이상-화상치료제
		break;
	case 3:
		return 11399; //회복-상태이상-얼음상태치료제
		break;

	case 4:
		return 11499; //회복-상태이상-잠깨는약
		break;
	case 5:
		return 11599; //회복-상태이상-마비치료제
		break;

	case 6:
		return 16999; //회복-상태이상&HP-풀회복약
		break;

	case 7:
		return 12999; //회복-HP-회복약
		break;

	case 8:
		return 12020; //회복-HP-상처약
		break;

	case 9:
		return 12120; //회복-HP-고급상처약
		break;

	case 10:
		return 12060; //회복-HP-좋은상처약
		break;
	case 11:
		return 11699; //회복-상태이상-만병통치제
		break;

	case 12:
		return 17000; // 기력의조각 기절회복 및 50%회복
		break;
	case 13:
		return 17999; // 기력의덩어리 기절회복 및 풀회복
		break;

	case 14:
		return 12030;
		break;
	case 15:
		return 12050;
		break;

	case 16:
		return 12070;
		break;
	case 17:
		return 13010;
		break;

	case 18:
		return 13999;
		break;
	case 19:
		return 14010;
		break;

	case 20:
		return 14999;
		break;
	case 21:
		return 35001;
		break;
	
	}

	return 0;



}
