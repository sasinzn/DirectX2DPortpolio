#include "Framework.h"
#include "Keyitem.h"

#include "GeoMetries/AnimationRect.h"
#include "Utilities/Animator.h"

Keyitem::Keyitem()
{
	Texture2D* srcTex = new Texture2D(TextureMapMenuPath + L"KeyItem.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	KeyitemClip = new AnimationClip(L"KeyitemClip", srcTex, 10, { 0,0 }, texSize);

#pragma region Item name explain 

	// 1. 실프스코프
	name.push_back("실프스코프");
	explain.push_back("       포켓몬 타워에서 사용되는 도구이다.      ");

	name.push_back("금틀니");
	explain.push_back("         누군가가 잃어버린 틀니.           ");

	name.push_back("차");
	explain.push_back("약간 씁쓸하고 구수한 향기가 나는 차.\n 말랐던 목이 촉촉해진다.");

	name.push_back("마티스의 사인");
	explain.push_back("     갈색시티 체육관 관장 마티스의 사인.     ");

	name.push_back("타운맵");
	explain.push_back("          관동지역의 지도이다.       ");

	name.push_back("승선티켓");
	explain.push_back("쾌속선 상트앙느호에 탈 때 필요한 승선티켓.\n 배 그림이 그려져 있다.");

	name.push_back("전해줄물건");
	explain.push_back("상록시티 프렌들리샵 점원에게서\n 오박사에게 건네주도록 부탁받은 물건.");

	name.push_back("비밀의 열쇠");
	explain.push_back("홍련체육관에 들어가기 위해\n 필요한 열쇠이다.");

	name.push_back("카드키");
	explain.push_back("실프주식회사에서 사용하는\n 직원용 카드키.");

	name.push_back("엘리베이터 키");
	explain.push_back("로켓단 아지트의 엘리베이터를\n 이용할수 있는 열쇠이다.");



#pragma endregion

}

Keyitem::~Keyitem()
{
}
