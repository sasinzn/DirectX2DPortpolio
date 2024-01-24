#include "Framework.h"
#include "PokeBall.h"

#include "GeoMetries\TextureRect.h"
#include "GeoMetries/AnimationRect.h"
#include "Utilities/animator.h"

PokeBall::PokeBall()
{
	Texture2D* srcTex = new Texture2D(TextureMapMenuPath + L"ballThrow.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	Texture2D* srcTex2 = new Texture2D(TextureMapMenuPath + L"pokeballMiss.png");
	Vector2 texSize2 = Vector2(srcTex2->GetWidth(), srcTex2->GetHeight());

	Texture2D* srcTex3 = new Texture2D(TextureMapMenuPath + L"pokeballGet.png");
	Vector2 texSize3 = Vector2(srcTex3->GetWidth(), srcTex3->GetHeight());

	Texture2D* srcTex4 = new Texture2D(TextureMapMenuPath + L"pokeballs.png");
	Vector2 texSize4 = Vector2(srcTex4->GetWidth(), srcTex4->GetHeight());

	Vector2 monsterBallThrow_startPos[17];
	Vector2 monsterBallThrow_endPos[17];
	Vector2 monsterballGetMiss_startPos[17];
	Vector2 monsterballGetMiss_endPos[17];
	Vector2 monsterballGet_startPos[17];
	Vector2 monsterballGet_endPos[17];

	for (int i = 0; i < 17; i++)
	{
		monsterBallThrow_startPos[i] = Vector2(0, (texSize.y / 17.0) * (i));
		monsterBallThrow_endPos[i] = Vector2(texSize.x, (texSize.y / 17.0) * (i + 1));
		monsterballGetMiss_startPos[i] = Vector2(0, (texSize2.y / 17.0) * (i));
		monsterballGetMiss_endPos[i] = Vector2(texSize2.x, (texSize2.y / 17.0) * (i + 1));
		monsterballGet_startPos[i] = Vector2(0, (texSize3.y / 17.0) * (i));
		monsterballGet_endPos[i] = Vector2(texSize3.x, (texSize3.y / 17.0) * (i + 1));

		indexNo[i] = i + 1;
	}
	/*
#pragma region Clip Monsterball size



	//몬스터볼
	Vector2 monsterBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 13.0);
	Vector2 monsterBallThrow_endPos = Vector2(texSize.x, (texSize.y / 17.0) * 14.0);
	Vector2 monsterballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 13.0);
	Vector2 monsterballGetMiss_endPos = Vector2(texSize2.x, (texSize2.y / 17.0) * 14.0);
	Vector2 monsterballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 13.0);
	Vector2 monsterballGet_endPos = Vector2(texSize3.x, (texSize3.y / 17.0) * 14.0);
	//슈퍼볼
	Vector2 superBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 14.0);
	Vector2 superBallThrow_endPos = Vector2(texSize.x, (texSize.y / 17.0) * 15.0);
	Vector2 superballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 14.0);
	Vector2 superballGetMiss_endPos = Vector2(texSize2.x, (texSize2.y / 17.0) * 15.0);
	Vector2 superballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 14.0);
	Vector2 superballGet_endPos = Vector2(texSize3.x, (texSize3.y / 17.0) * 15.0);
	//하이퍼볼
	Vector2 hyperBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 15.0);
	Vector2 hyperBallThrow_endPos = Vector2(texSize.x, (texSize.y / 17.0) * 16.0);
	Vector2 hyperballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 15.0);
	Vector2 hyperballGetMiss_endPos = Vector2(texSize2.x, (texSize2.y / 17.0) * 16.0);
	Vector2 hyperballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 15.0);
	Vector2 hyperballGet_endPos = Vector2(texSize3.x, (texSize3.y / 17.0) * 16.0);
	//마스터볼
	Vector2 masterBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 16.0);
	Vector2 masterBallThrow_endPos = Vector2(texSize.x, texSize.y);
	Vector2 masterballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 16.0);
	Vector2 masterballGetMiss_endPos = Vector2(texSize2.x, texSize2.y);
	Vector2 masterballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 16.0);
	Vector2 masterballGet_endPos = Vector2(texSize3.x, texSize3.y);
	//사파리볼 
	Vector2 safariBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 12.0);
	Vector2 safariBallThrow_endPos = Vector2(texSize.x, (texSize.y / 17.0) * 13.0);
	Vector2 safariballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 12.0);
	Vector2 safariballGetMiss_endPos = Vector2(texSize2.x, (texSize2.y / 17.0) * 13.0);
	Vector2 safariballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 12.0);
	Vector2 safariballGet_endPos = Vector2(texSize3.x, (texSize3.y / 17.0) * 13.0);
	//네트볼
	Vector2 netBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 11.0);
	Vector2 netBallThrow_endPos = Vector2(texSize.x, (texSize.y / 17.0) * 12.0);
	Vector2 netballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 11.0);
	Vector2 netballGetMiss_endPos = Vector2(texSize2.x, (texSize2.y / 17.0) * 12.0);
	Vector2 netballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 11.0);
	Vector2 netballGet_endPos = Vector2(texSize3.x, (texSize3.y / 17.0) * 12.0);
	//다이브볼
	Vector2 diveBallThrow_startPos = Vector2(0, (texSize.y / 17.0) * 10.0);
	Vector2 diveBallThrow_endPos = Vector2(texSize.x, (texSize.y / 17.0) * 11.0);
	Vector2 diveballGetMiss_startPos = Vector2(0, (texSize2.y / 17.0) * 10.0);
	Vector2 diveballGetMiss_endPos = Vector2(texSize2.x, (texSize2.y / 17.0) * 11.0);
	Vector2 diveballGet_startPos = Vector2(0, (texSize3.y / 17.0) * 10.0);
	Vector2 diveballGet_endPos = Vector2(texSize3.x, (texSize3.y / 17.0) * 11.0);


#pragma endregion
	*/


	// 01 몬스터볼 로드
	ballThrow[0] = new AnimationClip(L"MonsterBallThrow", srcTex, 11, monsterBallThrow_startPos[13], monsterBallThrow_endPos[13]);
	ballGetMiss[0] = new AnimationClip(L"MonsterballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[13], monsterballGetMiss_endPos[13]);
	ballGet[0] = new AnimationClip(L"MonsterballGet", srcTex3, 26, monsterballGet_startPos[13], monsterballGet_endPos[13]);
	indexName.push_back("몬스터볼");
	indexBallExplan.push_back("야생 포켓몬에게 던져서\n 잡기위한 볼.\n캡슐식으로 되어있다.");
	
	ballThrowClipName[0] = L"MonsterBallThrow";
	ballMissClipName[0] = L"MonsterballGetMiss";
	ballGetClipName[0] = L"MonsterballGet";

	// 02 슈퍼볼 로드
	ballThrow[1] = new AnimationClip(L"SuperBallThrow", srcTex, 11, monsterBallThrow_startPos[14], monsterBallThrow_endPos[14]);
	ballGetMiss[1] = new AnimationClip(L"SuperballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[14], monsterballGetMiss_endPos[14]);
	ballGet[1] = new AnimationClip(L"SuperballGet", srcTex3, 26, monsterballGet_startPos[14], monsterballGet_endPos[14]);
	indexName.push_back("슈퍼볼");
	indexBallExplan.push_back("몬스터볼보다도\n더욱 포켓몬을 잡기 쉬워진\n 약간 성능이 좋은 볼.");
	
	ballThrowClipName[1] = L"SuperBallThrow";
	ballMissClipName[1] = L"SuperballGetMiss";
	ballGetClipName[1] = L"SuperballGet";

	// 03 하이퍼볼 로드
	ballThrow[2] = new AnimationClip(L"HyperBallThrow", srcTex, 11, monsterBallThrow_startPos[15], monsterBallThrow_endPos[15]);
	ballGetMiss[2] = new AnimationClip(L"HyperballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[15], monsterballGetMiss_endPos[15]);
	ballGet[2] = new AnimationClip(L"HyperballGet", srcTex3, 26, monsterballGet_startPos[15], monsterballGet_endPos[15]);
	indexName.push_back("하이퍼볼");
	indexBallExplan.push_back("수퍼볼보다도\n더욱 포켓몬을 잡기 쉬워진\n 매우 성능이 좋은 볼.");

	ballThrowClipName[2] = L"HyperBallThrow";
	ballMissClipName[2] = L"HyperballGetMiss";
	ballGetClipName[2] = L"HyperballGet";

	// 04 마스터볼 로드
	ballThrow[3] = new AnimationClip(L"MasterBallThrow", srcTex, 11, monsterBallThrow_startPos[16], monsterBallThrow_endPos[16]);
	ballGetMiss[3] = new AnimationClip(L"MasterballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[16], monsterballGetMiss_endPos[16]);
	ballGet[3] = new AnimationClip(L"MasterballGet", srcTex3, 26, monsterballGet_startPos[16], monsterballGet_endPos[16]);
	indexName.push_back("마스터볼");
	indexBallExplan.push_back("야생 포켓몬을\n 반드시 잡을 수 있는\n 최고 성능의 볼.");

	ballThrowClipName[3] = L"MasterBallThrow";
	ballMissClipName[3] = L"MasterballGetMiss";
	ballGetClipName[3] = L"MasterballGet";

	// 05 사파리볼 로드
	ballThrow[4] = new AnimationClip(L"SafariBallThrow", srcTex, 11, monsterBallThrow_startPos[12], monsterBallThrow_endPos[12]);
	ballGetMiss[4] = new AnimationClip(L"SafariballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[12], monsterballGetMiss_endPos[12]);
	ballGet[4] = new AnimationClip(L"SafariballGet", srcTex3, 26, monsterballGet_startPos[12], monsterballGet_endPos[12]);
	indexName.push_back("사파리볼");
	indexBallExplan.push_back("대습초원 안에서만\n 쓰는 특별한 볼.\n 얼룩무늬로 되어 있다.");

	ballThrowClipName[4] = L"SafariBallThrow";
	ballMissClipName[4] = L"SafariballGetMiss";
	ballGetClipName[4] = L"SafariballGet";

	// 06 네트볼 로드
	ballThrow[5] = new AnimationClip(L"NetBallThrow", srcTex, 11, monsterBallThrow_startPos[11], monsterBallThrow_endPos[11]);
	ballGetMiss[5] = new AnimationClip(L"NetballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[11], monsterballGetMiss_endPos[11]);
	ballGet[5] = new AnimationClip(L"NetballGet", srcTex3, 26, monsterballGet_startPos[11], monsterballGet_endPos[11]);
	indexName.push_back("네트볼");
	indexBallExplan.push_back("물 타입과 벌레 타입의\n 포켓몬을 잡기 쉬운\n 조금 특이한 볼.");

	ballThrowClipName[5] = L"NetBallThrow";
	ballMissClipName[5] = L"NetballGetMiss";
	ballGetClipName[5] = L"NetballGet";

	// 07 다이브볼 로드
	ballThrow[6] = new AnimationClip(L"DiveBallThrow", srcTex, 11, monsterBallThrow_startPos[10], monsterBallThrow_endPos[10]);
	ballGetMiss[6] = new AnimationClip(L"DiveballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[10], monsterballGetMiss_endPos[10]);
	ballGet[6] = new AnimationClip(L"DiveballGet", srcTex3, 26, monsterballGet_startPos[10], monsterballGet_endPos[10]);
	indexName.push_back("다이브볼");
	indexBallExplan.push_back("물의 세계에서 사는\n 포켓몬을 잡기 쉬운\n 조금 특이한 볼.");

	ballThrowClipName[6] = L"DiveBallThrow";
	ballMissClipName[6] = L"DiveballGetMiss";
	ballGetClipName[6] = L"DiveballGet";

	// 08 네스트볼 로드
	ballThrow[7] = new AnimationClip(L"NestBallThrow", srcTex, 11, monsterBallThrow_startPos[9], monsterBallThrow_endPos[9]);
	ballGetMiss[7] = new AnimationClip(L"NestballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[9], monsterballGetMiss_endPos[9]);
	ballGet[7] = new AnimationClip(L"NestballGet", srcTex3, 26, monsterballGet_startPos[9], monsterballGet_endPos[9]);
	indexName.push_back("네스트볼");
	indexBallExplan.push_back("잡으려는 야생 포켓몬이\n 약할수록 잡기 쉬운\n 조금 특이한 볼.");

	ballThrowClipName[7] = L"NestBallThrow";
	ballMissClipName[7] = L"NestballGetMiss";
	ballGetClipName[7] = L"NestballGet";

	// 09 리피트볼 로드
	ballThrow[8] = new AnimationClip(L"RepeatBallThrow", srcTex, 11, monsterBallThrow_startPos[8], monsterBallThrow_endPos[8]);
	ballGetMiss[8] = new AnimationClip(L"RepeatballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[8], monsterballGetMiss_endPos[8]);
	ballGet[8] = new AnimationClip(L"RepeatballGet", srcTex3, 26, monsterballGet_startPos[8], monsterballGet_endPos[8]);
	indexName.push_back("리피트볼");
	indexBallExplan.push_back("잡은 적이 있는\n 포켓몬을 잡기 쉬운\n 조금 특이한 볼.");

	ballThrowClipName[8] = L"RepeatBallThrow";
	ballMissClipName[8] = L"RepeatballGetMiss";
	ballGetClipName[8] = L"RepeatballGet";

	// 10 타이머볼 로드
	ballThrow[9] = new AnimationClip(L"TimerBallThrow", srcTex, 11, monsterBallThrow_startPos[7], monsterBallThrow_endPos[7]);
	ballGetMiss[9] = new AnimationClip(L"TimerballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[7], monsterballGetMiss_endPos[7]);
	ballGet[9] = new AnimationClip(L"TimerballGet", srcTex3, 26, monsterballGet_startPos[7], monsterballGet_endPos[7]);
	indexName.push_back("타이머볼");
	indexBallExplan.push_back("턴 수가 길어지면 길어질수록\n 포켓몬을 잡기 쉬운\n 조금 특이한 볼.");

	ballThrowClipName[9] = L"TimerBallThrow";
	ballMissClipName[9] = L"TimerballGetMiss";
	ballGetClipName[9] = L"TimerballGet";

	// 11 럭셔리볼 로드
	ballThrow[10] = new AnimationClip(L"LuxuryBallThrow", srcTex, 11, monsterBallThrow_startPos[6], monsterBallThrow_endPos[6]);
	ballGetMiss[10] = new AnimationClip(L"LuxuryballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[6], monsterballGetMiss_endPos[6]);
	ballGet[10] = new AnimationClip(L"LuxuryballGet", srcTex3, 26, monsterballGet_startPos[6], monsterballGet_endPos[6]);
	indexName.push_back("럭셔리볼");
	indexBallExplan.push_back("잡은 야생 포켓몬이\n 매우 친밀해지기 쉬운\n 편안한 볼.");

	ballThrowClipName[10] = L"LuxuryBallThrow";
	ballMissClipName[10] = L"LuxuryballGetMiss";
	ballGetClipName[10] = L"LuxuryballGet";

	// 12 프리미어볼 로드
	ballThrow[11] = new AnimationClip(L"PremierBallThrow", srcTex, 11, monsterBallThrow_startPos[5], monsterBallThrow_endPos[5]);
	ballGetMiss[11] = new AnimationClip(L"PremierballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[5], monsterballGetMiss_endPos[5]);
	ballGet[11] = new AnimationClip(L"PremierballGet", srcTex3, 26, monsterballGet_startPos[5], monsterballGet_endPos[5]);
	indexName.push_back("프리미어볼");
	indexBallExplan.push_back("무언가의 기념품으로\n 특별히 만들어진\n 조금 희귀한 볼.");

	ballThrowClipName[11] = L"PremierBallThrow";
	ballMissClipName[11] = L"PremierballGetMiss";
	ballGetClipName[11] = L"PremierballGet";

	// 13 다크볼 로드
	ballThrow[12] = new AnimationClip(L"DarkBallThrow", srcTex, 11, monsterBallThrow_startPos[4], monsterBallThrow_endPos[4]);
	ballGetMiss[12] = new AnimationClip(L"DarkballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[4], monsterballGetMiss_endPos[4]);
	ballGet[12] = new AnimationClip(L"DarkballGet", srcTex3, 26, monsterballGet_startPos[4], monsterballGet_endPos[4]);
	indexName.push_back("다크볼");
	indexBallExplan.push_back("밤이나 동굴 등 어두운 곳에서\n 포켓몬을 잡기 쉬운\n 조금 특이한 볼.");

	ballThrowClipName[12] = L"DarkBallThrow";
	ballMissClipName[12] = L"DarkballGetMiss";
	ballGetClipName[12] = L"DarkballGet";

	// 14 힐볼 로드
	ballThrow[13] = new AnimationClip(L"HealBallThrow", srcTex, 11, monsterBallThrow_startPos[3], monsterBallThrow_endPos[3]);
	ballGetMiss[13] = new AnimationClip(L"HealballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[3], monsterballGetMiss_endPos[3]);
	ballGet[13] = new AnimationClip(L"HealballGet", srcTex3, 26, monsterballGet_startPos[3], monsterballGet_endPos[3]);
	indexName.push_back("힐볼");
	indexBallExplan.push_back("잡은 포켓몬의\n HP와 상태 이상을 회복시키는\n 조금 다정한 볼.");

	ballThrowClipName[13] = L"HealBallThrow";
	ballMissClipName[13] = L"HealballGetMiss";
	ballGetClipName[13] = L"HealballGet";

	// 15 퀵볼 로드
	ballThrow[14] = new AnimationClip(L"QuickBallThrow", srcTex, 11, monsterBallThrow_startPos[2], monsterBallThrow_endPos[2]);
	ballGetMiss[14] = new AnimationClip(L"QuickballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[2], monsterballGetMiss_endPos[2]);
	ballGet[14] = new AnimationClip(L"QuickballGet", srcTex3, 26, monsterballGet_startPos[2], monsterballGet_endPos[2]);
	indexName.push_back("퀵볼");
	indexBallExplan.push_back("배틀이 시작되자마자\n 사용하면 잡기 쉬워지는\n 조금 특이한 볼.");

	ballThrowClipName[14] = L"QuickBallThrow";
	ballMissClipName[14] = L"QuickballGetMiss";
	ballGetClipName[14] = L"QuickballGet";

	// 16 프레셔스볼 로드
	ballThrow[15] = new AnimationClip(L"PreciousBallThrow", srcTex, 11, monsterBallThrow_startPos[1], monsterBallThrow_endPos[1]);
	ballGetMiss[15] = new AnimationClip(L"PreciousballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[1], monsterballGetMiss_endPos[1]);
	ballGet[15] = new AnimationClip(L"PreciousballGet", srcTex3, 26, monsterballGet_startPos[1], monsterballGet_endPos[1]);
	indexName.push_back("프레셔스볼");
	indexBallExplan.push_back("무언가의 기념품으로\n 특별히 만들어진\n 상당히 진귀한 볼.");

	ballThrowClipName[15] = L"PreciousBallThrow";
	ballMissClipName[15] = L"PreciousballGetMiss";
	ballGetClipName[15] = L"PreciousballGet";

	// 17 드림볼 로드
	ballThrow[16] = new AnimationClip(L"DreamBallThrow", srcTex, 11, monsterBallThrow_startPos[0], monsterBallThrow_endPos[0]);
	ballGetMiss[16] = new AnimationClip(L"DreamballGetMiss", srcTex2, 13, monsterballGetMiss_startPos[0], monsterballGetMiss_endPos[0]);
	ballGet[16] = new AnimationClip(L"DreamballGet", srcTex3, 26, monsterballGet_startPos[0], monsterballGet_endPos[0]);
	indexName.push_back("드림볼");
	indexBallExplan.push_back("하일링크의 숲에서 어느 사이엔지\n 가방 속에 나타나는 꿈의 볼.\n 어떤 포켓몬이라도 잡을 수 있다.");

	ballThrowClipName[16] = L"DreamBallThrow";
	ballMissClipName[16] = L"DreamballGetMiss";
	ballGetClipName[16] = L"DreamballGet";

	pokeballSprite = new AnimationClip(L"PokeBallClip", srcTex4, 17, {0,0}, texSize4);

	SAFE_DELETE(srcTex4);
	SAFE_DELETE(srcTex3);
	SAFE_DELETE(srcTex2);
	SAFE_DELETE(srcTex);


	aniThrow = new Animator();
	aniGet = new Animator();
	animRectThrow = new AnimationRect({ 340,300,0 }, { 200,200,0 }, -1.5708f);
	animRectGet = new AnimationRect({ 900,500,0 }, { 200,200,0 },-1.5708f);

	for (int i = 0; i < 17; i++)
	{
		aniThrow->AddAnimClip(ballThrow[i]);
		aniGet->AddAnimClip(ballGetMiss[i]);
		aniGet->AddAnimClip(ballGet[i]);
	}

	aniThrow->SetLoopOff();
	aniGet->SetLoopOff();
	aniThrow->SetCurrentAnimClip(ballThrowClipName[currentBallIndex]);
	aniGet->SetCurrentAnimClip(ballMissClipName[currentBallIndex]);
	animRectThrow->SetAnimation(aniThrow);
	animRectGet->SetAnimation(aniGet);
	pos[0] = {340,300,0};
	pos[1] = { 400,330,0 };
	pos[2] = { 460,360,0 };
	pos[3] = { 520,390,0 };
	pos[4] = { 580,420,0 };
	pos[5] = { 640,450,0 };
	pos[6] = { 700,480,0 };
	pos[7] = { 760,510,0 };
	pos[8] = { 820,540,0 };
	pos[9] = { 880,510,0 };
	pos[10] = { 900,500,0 };
	frameIndex = aniThrow->GetFrameIndex();


}

PokeBall::~PokeBall()
{
	SAFE_DELETE(animRectGet);
	SAFE_DELETE(animRectThrow);
	SAFE_DELETE(aniGet);
	SAFE_DELETE(aniThrow);
}

void PokeBall::Update()
{
	aniThrow->SetCurrentAnimClip(ballThrowClipName[currentBallIndex]);

	if (ballThrowing)
	{
		aniThrow->Update();
		animRectThrow->Update();
		PokeBallThrow();
		cout << "포켓볼 던지는중..." << endl;
	}
	if (ballThrowing && aniThrow->GetAniEnd() && !gotchaPokemon)
	{
		gotchaPokemon = true;
		cout << "포켓볼 던지기 끝 포획 판별중..." << endl;
		GotCha();
		if (getPokemon == true)
		{
			aniGet->SetCurrentAnimClip(ballGetClipName[currentBallIndex]);
			cout << "포획성공" << endl;
			playerGetPokemon = true;
			
		}
		else if (getPokemon == false)
		{
			aniGet->SetCurrentAnimClip(ballMissClipName[currentBallIndex]);
			cout << "포획실패" << endl;
		}
	}

	if (gotchaPokemon)
	{
		ballThrowing = false;
		aniGet->Update();
		animRectGet->Update();
	}

	if (playerGetPokemon && aniGet->GetAniEnd())
	{
		cout << "포획성공 애니메이션 끝" << endl;
		getPokemonRenderOn = true;
		Reset();
	}
	else if (!getPokemon && aniGet->GetAniEnd())
	{
		cout << "포획 실패 에니메이션 끝" << endl;
		Reset();
	}
}

void PokeBall::Render()
{
	if(ballThrowing)
		animRectThrow->Render();
	else if (gotchaPokemon)
		animRectGet->Render();
}

void PokeBall::PokeBallThrow()
{
	if (frameIndex < aniThrow->GetFrameIndex())
	{
		frameIndex = aniThrow->GetFrameIndex();
		animRectThrow->SetPosition(pos[frameIndex]);
	}
}

void PokeBall::GotCha()
{
	int pokemonRand = rand();

	switch (currentBallIndex)
	{
	case 0:
		if (pokemonRand % 12 == 11)
			getPokemon = true;
		else
			getPokemon = false;

		break;
	case 1:
		if (pokemonRand % 10 == 9)
			getPokemon = true;
		else
			getPokemon = false;
		break;
	case 2:
		if (pokemonRand % 8 == 7)
			getPokemon = true;
		else
			getPokemon = false;
		break;
	case 3:
		getPokemon = true;

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 10:

		break;
	case 11:

		break;
		
	case 12:

		break;

	case 13:

		break;

	case 14:

		break;
		
	case 15:

		break;

	case 16:

		break;

	default:
		
		break;
	}
}

void PokeBall::Reset()
{
	aniThrow->SetAniReset();
	aniGet->SetAniReset();
	ballThrowing = false;
	gotchaPokemon = false;
	getPokemon = false;
	frameIndex = 0;
}
