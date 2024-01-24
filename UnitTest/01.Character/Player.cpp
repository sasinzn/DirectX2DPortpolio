#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
	:Character(position, size)
{
	Texture2D* srcTex = new Texture2D(TexturePath + L"Player_Walk.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	
#pragma region Clip Position Walk
	Vector2 WalkU_startPos = Values::ZeroVec2;
	Vector2 WalkU_endPos = Vector2(texSize.x, texSize.y * 0.25f);

	Vector2 WalkD_startPos = Vector2(0, texSize.y * 0.25f);
	Vector2 WalkD_endPos = Vector2(texSize.x, texSize.y * 0.5f);

	Vector2 WalkL_startPos = Vector2(0, texSize.y * 0.5f);
	Vector2 WalkL_endPos = Vector2(texSize.x, texSize.y * 0.75f);

	Vector2 WalkR_startPos = Vector2(0, texSize.y * 0.75f);
	Vector2 WalkR_endPos = Vector2(texSize.x, texSize.y);

#pragma endregion

	Texture2D* srcTex2 = new Texture2D(TexturePath + L"Player_Run.png");
	Vector2 texSize2 = Vector2(srcTex2->GetWidth(), srcTex2->GetHeight());

#pragma region Clip Position Run
	Vector2 RunU_startPos = Values::ZeroVec2;
	Vector2 RunU_endPos = Vector2(texSize.x, texSize.y * 0.25f);

	Vector2 RunD_startPos = Vector2(0, texSize.y * 0.25f);
	Vector2 RunD_endPos = Vector2(texSize.x, texSize.y * 0.5f);

	Vector2 RunL_startPos = Vector2(0, texSize.y * 0.5f);
	Vector2 RunL_endPos = Vector2(texSize.x, texSize.y * 0.75f);

	Vector2 RunR_startPos = Vector2(0, texSize.y * 0.75f);
	Vector2 RunR_endPos = Vector2(texSize.x, texSize.y);

#pragma endregion

	
	AnimationClip* WalkU = new AnimationClip(L"WalkU", srcTex, 3, WalkU_startPos, WalkU_endPos, true);
	AnimationClip* WalkD = new AnimationClip(L"WalkD", srcTex, 3, WalkD_startPos, WalkD_endPos);
	AnimationClip* WalkL = new AnimationClip(L"WalkL", srcTex, 3, WalkL_startPos, WalkL_endPos);
	AnimationClip* WalkR = new AnimationClip(L"WalkR", srcTex, 3, WalkR_startPos, WalkR_endPos, true);

	animator->AddAnimClip(WalkU);
	animator->AddAnimClip(WalkD);
	animator->AddAnimClip(WalkL);
	animator->AddAnimClip(WalkR);

	AnimationClip* RunU = new AnimationClip(L"RunU", srcTex2, 3, RunU_startPos, RunU_endPos, true);
	AnimationClip* RunD = new AnimationClip(L"RunD", srcTex2, 3, RunD_startPos, RunD_endPos);
	AnimationClip* RunL = new AnimationClip(L"RunL", srcTex2, 3, RunL_startPos, RunL_endPos);
	AnimationClip* RunR = new AnimationClip(L"RunR", srcTex2, 3, RunR_startPos, RunR_endPos, true);

	animator->AddAnimClip(RunU);
	animator->AddAnimClip(RunD);
	animator->AddAnimClip(RunL);
	animator->AddAnimClip(RunR);

	animator->SetCurrentAnimClip(L"WalkU");

	animRect->SetAnimation(animator);
	
	SAFE_DELETE(srcTex2);
	SAFE_DELETE(srcTex);

	collision = new BoundingBox(position, size, 0.f, Color(0,1,0,0.35f));
	holding = false;

	pPokemon.push_back(new Pokemon(1, 6,true));
	currentBattlePokemon = pPokemon[0];

	playerItem = new Item();
	pokemonMenu = new SwitchPokemon(this);
}

Player::~Player()
{
	SAFE_DELETE(pokemonMenu);
	SAFE_DELETE(playerItem);

	for (Pokemon* r : pPokemon)
		SAFE_DELETE(r);

	SAFE_DELETE(collision);
}

void Player::Update()
{
	
	animRect->Move(holding);
	
	animRect->Update();
	animator->Update();

	Vector3 position = animRect->GetPosition() + Vector3(100.f, 0.f, 0.f);
	Vector3 size = animRect->GetSize() + Vector3(animRect->GetSize().x, 0, 0);

	collision->UpdateCollisionData();
	collision->Update(animRect->GetPosition(), animRect->GetSize(), 0);
//	collision->Update(position, size, 35.0f);

	for (Pokemon* r : pPokemon)
	{
		r->Update();
	}
		

	currentBattlePokemon->Update();
	pokemonMenu->Update();

	Revolution();

}

void Player::Render()
{
	animRect->Render();
	collision->Render();
	pokemonMenu->Render();
}

void Player::GotchaPokemon(int indexNum, int level, int currentHP)
{
	pPokemon.push_back(new Pokemon(indexNum, level, true));
	pPokemon.back()->SetCurrentHP(currentHP);
}

void Player::AddPokemon(int indexNum, int level)
{
	pPokemon.push_back(new Pokemon(indexNum, level, true));
}

void Player::AllPokemonHealing()
{
	for (auto r : pPokemon)
	{
		r->VisitPMCenter();
	}
}

void Player::UsingItem(int PokemonIndexNum, int ItemindexNum)
{
	if (!usingitem)
	{
		playerItem->UseItems(ItemindexNum, pPokemon[PokemonIndexNum - 1]);
		playerItem->UseItemNum(ItemindexNum);
		usingitem = true;
	}
		



}

void Player::Revolution()
{
	for (int i = 0; i < pPokemon.size(); i++)
	{
		if (pPokemon[i]->isRevolution())
		{
			Pokemon* temp = new Pokemon(pPokemon[i]->RevolutionIndexNo(), pPokemon[i]->GetCurrentLevel(), true);
			pPokemon.erase(pPokemon.begin() + i);
			pPokemon.insert(pPokemon.begin() + i, temp);
			currentBattlePokemon = pPokemon[0];
		}
	}
	
}
