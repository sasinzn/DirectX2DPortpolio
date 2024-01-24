#pragma once

class ItemBag
{
public:
	ItemBag(class Player* player);
	~ItemBag();

	void Update();
	void Render();

	void PickMenu();
	void ItemExplanRender();
	void HealRender();
	void KeyRender();
	void BallRender();


private:
	class TextureRect* backGround = nullptr;
	class TextureRect* bagLeft = nullptr;
	class TextureRect* bagCenter = nullptr;
	class TextureRect* bagRight = nullptr;
	class TextureRect* bagMenuItem = nullptr;
	class TextureRect* bagMenuKeyItem = nullptr;
	class TextureRect* bagMenuPokeball = nullptr;
	class TextureRect* selectItem1 = nullptr;
	class TextureRect* selectItem2 = nullptr;
	class TextureRect* selectItem3 = nullptr;
	class TextureRect* selectItem4 = nullptr;
	class TextureRect* selectItem5 = nullptr;
	class TextureRect* selectItem6 = nullptr;
	class Player* playerData = nullptr;
	class PokeBall* balls = nullptr;
	class SwitchPokemon* pokemonMenu = nullptr;

	SelectMove currentMenu = BagItem;
	MenuTree bagMenuTree = TopMenu;
	int pokeBallindexCount = 0; // 0 ~ 10
	int healingItemindexCount = 0; // 0 ~ 15
	int keyItemindexCount = 0;	// 0 ~ 4
	int selectIndexNo = 1; // 1~6 이후 인덱스카운트 증가
	int pokeBallIndexNo = selectIndexNo + pokeBallindexCount;
	int healingItemIndexNo = selectIndexNo + healingItemindexCount;
	int keyItemIndexNo = selectIndexNo + keyItemindexCount;
	bool usingitemcount = false;

	class Animator* animator = nullptr;
	class AnimationRect* animRect = nullptr;

};