#include "Framework.h"
#include "Map.h"

Map::Map(Vector3 position, Vector3 size)
	:TextureRect(position, size, 0.f)
{
	// 도시 세팅 시작도시 태초마을
	// 태초마을, 상록시티, 회색시티, 블루시티, 갈색시티, 보라타운, 무지개시티, 연분홍시티, 노랑시티, 홍련섬, 석영고원
#pragma region City Create
	
	stage = new Stage;

	// 태초마을
	

	// 상록시티
	Texture2D* srcTex1 = new Texture2D(TextureMapCityPath + L"02_SangRokCity.png");
	StageClip* SangRokCity = new StageClip(L"02_SangRokCity", srcTex1, { srcTex1->GetWidth(),srcTex1->GetHeight(),0.f });
	SangRokCity->SetStageRoute(NORTH, L"Route_02");
	SangRokCity->SetStageRoute(WEST, L"Route_22");
	SangRokCity->SetStageRoute(SOUTH, L"Route_01");


	stage->AddStage(SangRokCity);
	SAFE_DELETE(srcTex1);

	// 회색시티
	Texture2D* srcTex2 = new Texture2D(TextureMapCityPath + L"03_GrayCity.png");
	StageClip* GrayCity = new StageClip(L"03_GrayCity", srcTex2, { srcTex2->GetWidth(),srcTex2->GetHeight(),0.f });
	GrayCity->SetStageRoute(EAST, L"Route_03");
	GrayCity->SetStageRoute(SOUTH, L"Route_02");
	stage->AddStage(GrayCity);
	SAFE_DELETE(srcTex2);

	// 블루시티
	Texture2D* srcTex3 = new Texture2D(TextureMapCityPath + L"04_BlueCity.png");
	StageClip* BlueCity = new StageClip(L"04_BlueCity", srcTex3, { srcTex3->GetWidth(),srcTex3->GetHeight(),0.f });
	BlueCity->SetStageRoute(NORTH, L"Route_24");
	BlueCity->SetStageRoute(WEST, L"Route_04");
	BlueCity->SetStageRoute(EAST, L"Route_09");
	BlueCity->SetStageRoute(SOUTH, L"Route_05");
	stage->AddStage(BlueCity);
	SAFE_DELETE(srcTex3);

	// 갈색시티
	Texture2D* srcTex4 = new Texture2D(TextureMapCityPath + L"05_GalsekCity.png");
	StageClip* GalsekCity = new StageClip(L"05_GalsekCity", srcTex4, { srcTex4->GetWidth(),srcTex4->GetHeight(),0.f });
	GalsekCity->SetStageRoute(NORTH, L"Route_06");
	GalsekCity->SetStageRoute(EAST, L"Route_11");
	stage->AddStage(GalsekCity);
	SAFE_DELETE(srcTex4);

	// 보라타운
	Texture2D* srcTex5 = new Texture2D(TextureMapCityPath + L"06_PurpleTown.png");
	StageClip* PurpleTown = new StageClip(L"06_PurpleTown", srcTex5, { srcTex5->GetWidth(),srcTex5->GetHeight(),0.f });
	PurpleTown->SetStageRoute(NORTH, L"Route_10");
	PurpleTown->SetStageRoute(SOUTH, L"Route_12");
	PurpleTown->SetStageRoute(WEST, L"Route_08");
	stage->AddStage(PurpleTown);
	SAFE_DELETE(srcTex5);

	// 무지개시티
	Texture2D* srcTex6 = new Texture2D(TextureMapCityPath + L"07_RainbowCity.png");
	StageClip* RainbowCity = new StageClip(L"07_RainbowCity", srcTex6, { srcTex6->GetWidth(),srcTex6->GetHeight(),0.f });
	RainbowCity->SetStageRoute(WEST, L"Route_16");
	RainbowCity->SetStageRoute(EAST, L"Route_07");
	stage->AddStage(RainbowCity);
	SAFE_DELETE(srcTex6);

	//연분홍 시티
	Texture2D* srcTex7 = new Texture2D(TextureMapCityPath + L"08_YeonbunhongCity.png");
	StageClip* YeonbunhongCity = new StageClip(L"08_YeonbunhongCity", srcTex7, { srcTex7->GetWidth(),srcTex7->GetHeight(),0.f });
	YeonbunhongCity->SetStageRoute(WEST, L"Route_18");
	YeonbunhongCity->SetStageRoute(EAST, L"Route_15");
	YeonbunhongCity->SetStageRoute(SOUTH, L"Route_19");
	stage->AddStage(YeonbunhongCity);
	SAFE_DELETE(srcTex7);

	// 노랑시티
	Texture2D* srcTex8 = new Texture2D(TextureMapCityPath + L"09_YellowCity.png");
	StageClip* YellowCity = new StageClip(L"09_YellowCity", srcTex8, { srcTex8->GetWidth(),srcTex8->GetHeight(),0.f });
	YellowCity->SetStageRoute(NORTH, L"Route_05");
	YellowCity->SetStageRoute(SOUTH, L"Route_06");
	YellowCity->SetStageRoute(EAST, L"Route_08");
	YellowCity->SetStageRoute(WEST, L"Route_07");

	stage->AddStage(YellowCity);
	SAFE_DELETE(srcTex8);

	// 홍련섬
	Texture2D* srcTex9 = new Texture2D(TextureMapCityPath + L"10_HongryeonIsland.png");
	StageClip* HongryeonIsland = new StageClip(L"10_HongryeonIsland", srcTex9, { srcTex9->GetWidth(),srcTex9->GetHeight(),0.f });
	HongryeonIsland->SetStageRoute(NORTH, L"Route_21");
	HongryeonIsland->SetStageRoute(EAST, L"Route_20");

	stage->AddStage(HongryeonIsland);
	SAFE_DELETE(srcTex9);

	// 석영고원
	Texture2D* srcTex11 = new Texture2D(TextureMapCityPath + L"11_SukyeongLeague.png");
	StageClip* SukyeongLeague = new StageClip(L"11_SukyeongLeague", srcTex11, { srcTex11->GetWidth(),srcTex11->GetHeight(),0.f });
	SukyeongLeague->SetStageRoute(SOUTH, L"Route_23");

	stage->AddStage(SukyeongLeague);
	SAFE_DELETE(srcTex11);

#pragma endregion

	// 도로 세팅 1~25번 도로
#pragma region Road Create

	// 1번 도로
	

	

	// 2번 도로
	Texture2D* srcTex13 = new Texture2D(TextureMapRoadPath + L"Route_02.png");
	StageClip* Route_02 = new StageClip(L"Route_02", srcTex13, { srcTex13->GetWidth(),srcTex13->GetHeight(),0.f });
	Route_02->SetStageRoute(NORTH, L"03_GrayCity");
	Route_02->SetStageRoute(SOUTH, L"02_SangRokCity");

	stage->AddStage(Route_02);
	SAFE_DELETE(srcTex13);

	// 3번 도로
	Texture2D* srcTex14 = new Texture2D(TextureMapRoadPath + L"Route_03.png");
	StageClip* Route_03 = new StageClip(L"Route_03", srcTex14, { srcTex14->GetWidth(),srcTex14->GetHeight(),0.f });
	Route_03->SetStageRoute(NORTH, L"Route_04");
	Route_03->SetStageRoute(WEST, L"03_GrayCity");

	stage->AddStage(Route_03);
	SAFE_DELETE(srcTex14);

	// 4번 도로
	Texture2D* srcTex15 = new Texture2D(TextureMapRoadPath + L"Route_04.png");
	StageClip* Route_04 = new StageClip(L"Route_04", srcTex15, { srcTex15->GetWidth(),srcTex15->GetHeight(),0.f });
	Route_04->SetStageRoute(NORTH, L"Route_03");
	Route_04->SetStageRoute(EAST, L"04_BlueCity");

	stage->AddStage(Route_04);
	SAFE_DELETE(srcTex15);

	// 5번 도로
	Texture2D* srcTex16 = new Texture2D(TextureMapRoadPath + L"Route_05.png");
	StageClip* Route_05 = new StageClip(L"Route_05", srcTex16, { srcTex16->GetWidth(),srcTex16->GetHeight(),0.f });
	Route_05->SetStageRoute(NORTH, L"04_BlueCity");
	Route_05->SetStageRoute(SOUTH, L"09_YellowCity");
	stage->AddStage(Route_05);
	SAFE_DELETE(srcTex16);

	// 6번 도로
	Texture2D* srcTex17 = new Texture2D(TextureMapRoadPath + L"Route_06.png");
	StageClip* Route_06 = new StageClip(L"Route_06", srcTex17, { srcTex17->GetWidth(),srcTex17->GetHeight(),0.f });
	Route_06->SetStageRoute(NORTH, L"09_YellowCity");
	Route_06->SetStageRoute(SOUTH, L"05_GalsekCity");

	stage->AddStage(Route_06);
	SAFE_DELETE(srcTex17);

	// 7번 도로
	Texture2D* srcTex18 = new Texture2D(TextureMapRoadPath + L"Route_07.png");
	StageClip* Route_07 = new StageClip(L"Route_07", srcTex18, { srcTex18->GetWidth(),srcTex18->GetHeight(),0.f });
	Route_07->SetStageRoute(EAST, L"09_YellowCity");
	Route_07->SetStageRoute(WEST, L"07_RainbowCity");
	stage->AddStage(Route_07);
	SAFE_DELETE(srcTex18);

	// 8번 도로
	Texture2D* srcTex19 = new Texture2D(TextureMapRoadPath + L"Route_08.png");
	StageClip* Route_08 = new StageClip(L"Route_08", srcTex19, { srcTex19->GetWidth(),srcTex19->GetHeight(),0.f });
	Route_08->SetStageRoute(WEST, L"09_YellowCity");
	Route_08->SetStageRoute(EAST, L"06_PurpleTown");

	stage->AddStage(Route_08);
	SAFE_DELETE(srcTex19);

	// 9번 도로
	Texture2D* srcTex20 = new Texture2D(TextureMapRoadPath + L"Route_09.png");
	StageClip* Route_09 = new StageClip(L"Route_09", srcTex20, { srcTex20->GetWidth(),srcTex20->GetHeight(),0.f });
	Route_09->SetStageRoute(WEST, L"04_BlueCity");
	Route_09->SetStageRoute(EAST, L"Route_10");
	stage->AddStage(Route_09);
	SAFE_DELETE(srcTex20);

	// 10번 도로
	Texture2D* srcTex21 = new Texture2D(TextureMapRoadPath + L"Route_10.png");
	StageClip* Route_10 = new StageClip(L"Route_10", srcTex21, { srcTex21->GetWidth(),srcTex21->GetHeight(),0.f });
	Route_10->SetStageRoute(WEST, L"Route_09");
	Route_10->SetStageRoute(SOUTH, L"06_PurpleTown");

	stage->AddStage(Route_10);
	SAFE_DELETE(srcTex21);

	// 11번 도로
	Texture2D* srcTex22 = new Texture2D(TextureMapRoadPath + L"Route_11.png");
	StageClip* Route_11 = new StageClip(L"Route_11", srcTex22, { srcTex22->GetWidth(),srcTex22->GetHeight(),0.f });
	Route_11->SetStageRoute(WEST, L"05_GalsekCity");
	Route_11->SetStageRoute(EAST, L"Route_12");

	stage->AddStage(Route_11);
	SAFE_DELETE(srcTex22);

	// 12번 도로
	Texture2D* srcTex23 = new Texture2D(TextureMapRoadPath + L"Route_12.png");
	StageClip* Route_12 = new StageClip(L"Route_12", srcTex23, { srcTex23->GetWidth(),srcTex23->GetHeight(),0.f });
	Route_12->SetStageRoute(NORTH, L"06_PurpleTown");
	Route_12->SetStageRoute(WEST, L"Route_11");
	Route_12->SetStageRoute(SOUTH, L"Route_13");

	stage->AddStage(Route_12);
	SAFE_DELETE(srcTex23);

	// 13번 도로
	Texture2D* srcTex24 = new Texture2D(TextureMapRoadPath + L"Route_13.png");
	StageClip* Route_13 = new StageClip(L"Route_13", srcTex24, { srcTex24->GetWidth(),srcTex24->GetHeight(),0.f });
	Route_13->SetStageRoute(NORTH, L"Route_12");
	Route_13->SetStageRoute(WEST, L"Route_14");
	stage->AddStage(Route_13);
	SAFE_DELETE(srcTex24);

	// 14번 도로
	Texture2D* srcTex25 = new Texture2D(TextureMapRoadPath + L"Route_14.png");
	StageClip* Route_14 = new StageClip(L"Route_14", srcTex25, { srcTex25->GetWidth(),srcTex25->GetHeight(),0.f });
	Route_14->SetStageRoute(EAST, L"Route_13");
	Route_14->SetStageRoute(WEST, L"Route_15");

	stage->AddStage(Route_14);
	SAFE_DELETE(srcTex25);

	// 15번 도로
	Texture2D* srcTex26 = new Texture2D(TextureMapRoadPath + L"Route_15.png");
	StageClip* Route_15 = new StageClip(L"Route_15", srcTex26, { srcTex26->GetWidth(),srcTex26->GetHeight(),0.f });
	Route_15->SetStageRoute(EAST, L"Route_14");
	Route_15->SetStageRoute(WEST, L"08_YeonbunhongCity");

	stage->AddStage(Route_15);
	SAFE_DELETE(srcTex26);

	// 16번 도로
	Texture2D* srcTex27 = new Texture2D(TextureMapRoadPath + L"Route_16.png");
	StageClip* Route_16 = new StageClip(L"Route_16", srcTex27, { srcTex27->GetWidth(),srcTex27->GetHeight(),0.f });
	Route_16->SetStageRoute(EAST, L"07_RainbowCity");
	Route_16->SetStageRoute(SOUTH, L"Route_17");

	stage->AddStage(Route_16);
	SAFE_DELETE(srcTex27);

	// 17번 도로
	Texture2D* srcTex28 = new Texture2D(TextureMapRoadPath + L"Route_17.png");
	StageClip* Route_17 = new StageClip(L"Route_17", srcTex28, { srcTex28->GetWidth(),srcTex28->GetHeight(),0.f });
	Route_17->SetStageRoute(NORTH, L"Route_16");
	Route_17->SetStageRoute(SOUTH, L"Route_18");

	stage->AddStage(Route_17);
	SAFE_DELETE(srcTex28);

	// 18번 도로
	Texture2D* srcTex29 = new Texture2D(TextureMapRoadPath + L"Route_18.png");
	StageClip* Route_18 = new StageClip(L"Route_18", srcTex29, { srcTex29->GetWidth(),srcTex29->GetHeight(),0.f });
	Route_18->SetStageRoute(NORTH, L"Route_17");
	Route_18->SetStageRoute(EAST, L"08_YeonbunhongCity");

	stage->AddStage(Route_18);
	SAFE_DELETE(srcTex29);

	// 19번 도로
	Texture2D* srcTex30 = new Texture2D(TextureMapRoadPath + L"Route_19.png");
	StageClip* Route_19 = new StageClip(L"Route_19", srcTex30, { srcTex30->GetWidth(),srcTex30->GetHeight(),0.f });
	Route_19->SetStageRoute(NORTH, L"08_YeonbunhongCity");
	Route_19->SetStageRoute(WEST, L"Route_20");

	stage->AddStage(Route_19);
	SAFE_DELETE(srcTex30);

	// 20번 도로
	Texture2D* srcTex31 = new Texture2D(TextureMapRoadPath + L"Route_20.png");
	StageClip* Route_20 = new StageClip(L"Route_20", srcTex31, { srcTex31->GetWidth(),srcTex31->GetHeight(),0.f });
	Route_20->SetStageRoute(WEST, L"10_HongryeonIsland");
	Route_20->SetStageRoute(EAST, L"Route_19");

	stage->AddStage(Route_20);
	SAFE_DELETE(srcTex31);

	// 21번 도로
	Texture2D* srcTex32 = new Texture2D(TextureMapRoadPath + L"Route_21.png");
	StageClip* Route_21 = new StageClip(L"Route_21", srcTex32, { srcTex32->GetWidth(),srcTex32->GetHeight(),0.f });
	Route_21->SetStageRoute(NORTH, L"01_TaechoTown");
	Route_21->SetStageRoute(SOUTH, L"10_HongryeonIsland");

	stage->AddStage(Route_21);
	SAFE_DELETE(srcTex32);

	// 22번 도로
	Texture2D* srcTex33 = new Texture2D(TextureMapRoadPath + L"Route_22.png");
	StageClip* Route_22 = new StageClip(L"Route_22", srcTex33, { srcTex33->GetWidth(),srcTex33->GetHeight(),0.f });
	Route_22->SetStageRoute(EAST, L"02_SangRokCity");
	Route_22->SetStageRoute(NORTH, L"Route_23");

	stage->AddStage(Route_22);
	SAFE_DELETE(srcTex33);

	// 23번 도로
	Texture2D* srcTex34 = new Texture2D(TextureMapRoadPath + L"Route_23.png");
	StageClip* Route_23 = new StageClip(L"Route_23", srcTex34, { srcTex34->GetWidth(),srcTex34->GetHeight(),0.f });
	Route_23->SetStageRoute(SOUTH, L"Route_22");

	stage->AddStage(Route_23);
	SAFE_DELETE(srcTex34);

	// 24번 도로
	Texture2D* srcTex35 = new Texture2D(TextureMapRoadPath + L"Route_24.png");
	StageClip* Route_24 = new StageClip(L"Route_24", srcTex35, { srcTex35->GetWidth(),srcTex35->GetHeight(),0.f });
	Route_24->SetStageRoute(EAST, L"Route_25");
	Route_24->SetStageRoute(SOUTH, L"04_BlueCity");

	stage->AddStage(Route_24);
	SAFE_DELETE(srcTex35);

	// 25번 도로
	Texture2D* srcTex36 = new Texture2D(TextureMapRoadPath + L"Route_25.png");
	StageClip* Route_25 = new StageClip(L"Route_25", srcTex36, { srcTex36->GetWidth(),srcTex36->GetHeight(),0.f });
	Route_25->SetStageRoute(WEST, L"Route_24");

	stage->AddStage(Route_25);
	SAFE_DELETE(srcTex36);

#pragma endregion

	
}

Map::~Map()
{
}

void Map::Update()
{
	stage->Update();

	__super::Update();
}

void Map::Render()
{
	srv = stage->GetCurrentSRV();

	__super::Render();
}
