#pragma once

class SwitchPokemon
{
public:
	SwitchPokemon(class Player* player);
	~SwitchPokemon();

	void Update();
	void Render();

	void SetPokemonNum(int num) { pokemonNum = num; }
	void SetSelectPokemon(int indexNum) { selectPokemon = indexNum; }
	int GetSelectPokemon() { return selectPokemon; }
	int GetPokemonNum() { return pokemonNum; }
	void PokemonInfoRender();
	void HpUpdate();

	bool GetPokemonMenuOpen() { return openPokemonMenu; }
	void OpenPokemonMenu() { openPokemonMenu = true; }
	void ClosePokemonMenu() { openPokemonMenu = false; }

private:
	class Animator* animator = nullptr;
	class AnimationRect* animRect = nullptr;
	class TextureRect* backGround = nullptr;
	class TextureRect* pokemon01 = nullptr;
	class TextureRect* pokemon02 = nullptr;
	class TextureRect* pokemon03 = nullptr;
	class TextureRect* pokemon04 = nullptr;
	class TextureRect* pokemon05 = nullptr;
	class TextureRect* pokemon06 = nullptr;
	class TextureRect* pokemon01select = nullptr;
	class TextureRect* pokemon02select = nullptr;
	class TextureRect* pokemon03select = nullptr;
	class TextureRect* pokemon04select = nullptr;
	class TextureRect* pokemon05select = nullptr;
	class TextureRect* pokemon06select = nullptr;
	class HpBar* Hp01 = nullptr;
	class HpBar* Hp02 = nullptr;
	class HpBar* Hp03 = nullptr;
	class HpBar* Hp04 = nullptr;
	class HpBar* Hp05 = nullptr;
	class HpBar* Hp06 = nullptr;

	class Player* playerData = nullptr;

	int selectPokemon = 0;
	int pokemonNum = 0;

	float HpPercent01 = 1.0f;
	float HpPercent02 = 1.0f;
	float HpPercent03 = 1.0f;
	float HpPercent04 = 1.0f;
	float HpPercent05 = 1.0f;
	float HpPercent06 = 1.0f;

	bool openPokemonMenu;
};