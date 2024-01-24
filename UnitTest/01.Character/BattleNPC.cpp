#include "stdafx.h"
#include "BattleNPC.h"

BattleNPC::BattleNPC(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TextureNPCPath + L"NPC1.png");
	Texture2D* srcTex2 = new Texture2D(TextureNPCPath + L"NPC2.png");
	Texture2D* srcTex3 = new Texture2D(TextureNPCPath + L"NPC3.png");
	Texture2D* srcTex4 = new Texture2D(TextureNPCPath + L"NPC4.png");
	Texture2D* srcTex5 = new Texture2D(TextureNPCPath + L"NPC5.png");
	Texture2D* srcTex6 = new Texture2D(TextureNPCPath + L"NPC6.png");
	Texture2D* srcTex7 = new Texture2D(TextureNPCPath + L"NPC7.png");

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

#pragma region Clip Position NPC
	Vector2 NPCU_startPos = Values::ZeroVec2;
	Vector2 NPCU_endPos = Vector2(texSize.x, texSize.y * 0.25f);

	Vector2 NPCD_startPos = Vector2(0, texSize.y * 0.25f);
	Vector2 NPCD_endPos = Vector2(texSize.x, texSize.y * 0.5f);

	Vector2 NPCL_startPos = Vector2(0, texSize.y * 0.5f);
	Vector2 NPCL_endPos = Vector2(texSize.x, texSize.y * 0.75f);

	Vector2 NPCR_startPos = Vector2(0, texSize.y * 0.75f);
	Vector2 NPCR_endPos = Vector2(texSize.x, texSize.y);

#pragma endregion

#pragma region Clip ADD NPC
	// 1
	AnimationClip* NPC1U = new AnimationClip(L"NPC1U", srcTex, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC1D = new AnimationClip(L"NPC1D", srcTex, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC1L = new AnimationClip(L"NPC1L", srcTex, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC1R = new AnimationClip(L"NPC1R", srcTex, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC1U);
	animator->AddAnimClip(NPC1D);
	animator->AddAnimClip(NPC1L);
	animator->AddAnimClip(NPC1R);
	//2
	AnimationClip* NPC2U = new AnimationClip(L"NPC2U", srcTex2, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC2D = new AnimationClip(L"NPC2D", srcTex2, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC2L = new AnimationClip(L"NPC2L", srcTex2, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC2R = new AnimationClip(L"NPC2R", srcTex2, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC2U);
	animator->AddAnimClip(NPC2D);
	animator->AddAnimClip(NPC2L);
	animator->AddAnimClip(NPC2R);

	//3
	AnimationClip* NPC3U = new AnimationClip(L"NPC3U", srcTex3, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC3D = new AnimationClip(L"NPC3D", srcTex3, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC3L = new AnimationClip(L"NPC3L", srcTex3, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC3R = new AnimationClip(L"NPC3R", srcTex3, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC3U);
	animator->AddAnimClip(NPC3D);
	animator->AddAnimClip(NPC3L);
	animator->AddAnimClip(NPC3R);

	//4
	AnimationClip* NPC4U = new AnimationClip(L"NPC4U", srcTex4, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC4D = new AnimationClip(L"NPC4D", srcTex4, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC4L = new AnimationClip(L"NPC4L", srcTex4, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC4R = new AnimationClip(L"NPC4R", srcTex4, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC4U);
	animator->AddAnimClip(NPC4D);
	animator->AddAnimClip(NPC4L);
	animator->AddAnimClip(NPC4R);

	//5
	AnimationClip* NPC5U = new AnimationClip(L"NPC5U", srcTex5, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC5D = new AnimationClip(L"NPC5D", srcTex5, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC5L = new AnimationClip(L"NPC5L", srcTex5, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC5R = new AnimationClip(L"NPC5R", srcTex5, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC5U);
	animator->AddAnimClip(NPC5D);
	animator->AddAnimClip(NPC5L);
	animator->AddAnimClip(NPC5R);

	//6
	AnimationClip* NPC6U = new AnimationClip(L"NPC6U", srcTex6, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC6D = new AnimationClip(L"NPC6D", srcTex6, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC6L = new AnimationClip(L"NPC6L", srcTex6, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC6R = new AnimationClip(L"NPC6R", srcTex6, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC6U);
	animator->AddAnimClip(NPC6D);
	animator->AddAnimClip(NPC6L);
	animator->AddAnimClip(NPC6R);
	
	//7
	AnimationClip* NPC7U = new AnimationClip(L"NPC7U", srcTex7, 3, NPCU_startPos, NPCU_endPos, true);
	AnimationClip* NPC7D = new AnimationClip(L"NPC7D", srcTex7, 3, NPCD_startPos, NPCD_endPos);
	AnimationClip* NPC7L = new AnimationClip(L"NPC7L", srcTex7, 3, NPCL_startPos, NPCL_endPos);
	AnimationClip* NPC7R = new AnimationClip(L"NPC7R", srcTex7, 3, NPCR_startPos, NPCR_endPos, true);

	animator->AddAnimClip(NPC7U);
	animator->AddAnimClip(NPC7D);
	animator->AddAnimClip(NPC7L);
	animator->AddAnimClip(NPC7R);

#pragma endregion

	animator->SetCurrentAnimClip(L"NPC1R");
	animRect->SetAnimation(animator);
	SAFE_DELETE(srcTex7);
	SAFE_DELETE(srcTex6);
	SAFE_DELETE(srcTex5);
	SAFE_DELETE(srcTex4);
	SAFE_DELETE(srcTex3);
	SAFE_DELETE(srcTex2);
	SAFE_DELETE(srcTex);

	collision = new BoundingBox(position, size, 0.f, Color(1, 0, 0, 0.35f));
	holding = true;
	interaction = false;
	activeNPC = true;
	deltaTime = 0;
	pos = position;
	npcDir = STAY;

	int temp = (rand() % 12) + 1;

	pPokemon.push_back(new Pokemon(7, 8));
	currentBattlePokemon = pPokemon[0];

	for (int i = 0; i < 8; i++)
	{
		npcU[i] = L"NPC" + std::to_wstring(i) + L"U";
		npcD[i] = L"NPC" + std::to_wstring(i) + L"D";
		npcL[i] = L"NPC" + std::to_wstring(i) + L"L";
		npcR[i] = L"NPC" + std::to_wstring(i) + L"R";
	}
}

BattleNPC::~BattleNPC()
{
	SAFE_DELETE(collision);
}

void BattleNPC::Update()
{
	animRect->Move(holding);
	collision->Update();
	collision->UpdateCollisionData();

	animRect->Update();
	animator->Update();

	for (Pokemon* r : pPokemon)
		r->Update();


}

void BattleNPC::Render()
{
	animRect->Render();
	collision->Render();
}

bool BattleNPC::InterActionNPC(BoundingBox* player)
{
	if (activeNPC)
	{
		if (BoundingBox::AABB(player, collision) == true ||
			BoundingBox::OBB(player, collision) == true)
		{
			collision->SetColor(Color(1, 0, 0, 0.35f));

			if (deltaTime > 0.5)
			{
				interaction = true;
				deltaTime = 0;
			}
			else
				deltaTime += Time::Delta();
		}
		else
		{
			collision->SetColor(Color(0, 1, 0, 0.35f));
		}

		
	}

	if (interaction)
		return true;
	else
		return false;
}

void BattleNPC::SetNPC(int NPCindexNum, Direction dir)
{
	Vector3 posXtemp, posYtemp;
	posXtemp = { 50,0,0 };
	posYtemp = { 0,50,0 };
	npcDir = dir;
	switch (dir)
	{
	case EAST:
		animator->SetCurrentAnimClip(npcL[NPCindexNum]);
		collision->Update(pos - posXtemp, { 166,66,0 }, 0.f);
		break;
	case WEST:
		animator->SetCurrentAnimClip(npcR[NPCindexNum]);
		collision->Update(pos + posXtemp, { 166,66,0 }, 0.f);
		break;
	case SOUTH:
		animator->SetCurrentAnimClip(npcD[NPCindexNum]);
		collision->Update(pos - posYtemp, { 66,166,0 }, 0.f);
		break;
	case NORTH:
		animator->SetCurrentAnimClip(npcU[NPCindexNum]);
		collision->Update(pos + posYtemp, { 66,166,0 }, 0.f);
		break;
	default:
		break;
	}


}

void BattleNPC::AddPokemon()
{
	int temp = (rand() % 12) + 1;

	pPokemon.push_back(new Pokemon(10, 8));
}
