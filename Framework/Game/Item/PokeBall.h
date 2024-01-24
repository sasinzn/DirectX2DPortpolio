#pragma once

class PokeBall
{
public:
	PokeBall();
	~PokeBall();

	void Update();
	void Render();

	void ThrowBall() { ballThrowing = true; }
	void PokeBallThrow();
	void GotCha();
	void Reset();

	bool BallThrowing() { return ballThrowing; }
	bool BallGotCha() { return gotchaPokemon; }
	bool PokemonGet() { return getPokemon; }
	void PokemonGetReset() { getPokemon = false; }
	void PokemonGetRenderReset() { getPokemonRenderOn = false; }
	
	void SetMonsterBall(int indexNo) { currentBallIndex = indexNo - 1; };
	void SetPlayerPokemonGotchaReset() { playerGetPokemon = false; }
	bool GetPlayerPokemonGotcha() { return playerGetPokemon; }
	bool GetPokemonGetRender() { return getPokemonRenderOn; }
	class AnimationClip* GetBallThrow(int indexNo) { return ballThrow[indexNo - 1]; }
	class AnimationClip* GetBallGetLeft(int indexNo) { return ballGetMiss[indexNo - 1]; }
	class AnimationClip* GetBallGetRIght(int indexNo) { return ballGet[indexNo - 1]; }
	class AnimationClip* GetBallClip() { return pokeballSprite; }
	string GetBallName(int indexNo) { return indexName[indexNo - 1]; }
	string GetBallName() { return indexName[currentBallIndex]; }
	string GetBallExplan(int indexNo) { return indexBallExplan[indexNo - 1]; }
	int GetBallIndexNo(int indexNo) { return this->indexNo[indexNo - 1]; }

	
private:
	vector<string> indexName;					// 몬스터볼 종류 이름
	vector<string> indexBallExplan;				// 몬스터볼 설명
	int indexNo[17];
	class AnimationClip* ballThrow[17];			// 몬스터볼 던지기 스프라이트
	class AnimationClip* ballGetMiss[17];		// 몬스터볼 잡기 스프라이트 (좌)
	class AnimationClip* ballGet[17];		// 몬스터볼 잡기 스프라이트 (우)
	class AnimationClip* pokeballSprite;

	Vector3 pos[11];											// 텍스쳐 위치
	UINT frameIndex = 0;
	class TextureRect* monsterBallTex = nullptr;			// 아이템창 텍스쳐 (움직임 X)

	class Animator* aniThrow = nullptr;
	class Animator* aniGet = nullptr;
	class AnimationRect* animRectThrow = nullptr;
	class AnimationRect* animRectGet = nullptr;

	bool ballThrowing = false;					//몬스터볼 던지는중
	bool gotchaPokemon = false;					//포켓몬 포획 판별중
	bool getPokemon = false;					//포켓몬 포획 성공
	bool playerGetPokemon = false;				//플레이어에게 포켓몬 추가
	bool getPokemonRenderOn = false;			//포켓몬 포획 랜더링 온
	int currentBallIndex = 0;								// 0 ~ 16;
	wstring ballThrowClipName[17];
	wstring ballMissClipName[17];
	wstring ballGetClipName[17];

};
