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
	vector<string> indexName;					// ���ͺ� ���� �̸�
	vector<string> indexBallExplan;				// ���ͺ� ����
	int indexNo[17];
	class AnimationClip* ballThrow[17];			// ���ͺ� ������ ��������Ʈ
	class AnimationClip* ballGetMiss[17];		// ���ͺ� ��� ��������Ʈ (��)
	class AnimationClip* ballGet[17];		// ���ͺ� ��� ��������Ʈ (��)
	class AnimationClip* pokeballSprite;

	Vector3 pos[11];											// �ؽ��� ��ġ
	UINT frameIndex = 0;
	class TextureRect* monsterBallTex = nullptr;			// ������â �ؽ��� (������ X)

	class Animator* aniThrow = nullptr;
	class Animator* aniGet = nullptr;
	class AnimationRect* animRectThrow = nullptr;
	class AnimationRect* animRectGet = nullptr;

	bool ballThrowing = false;					//���ͺ� ��������
	bool gotchaPokemon = false;					//���ϸ� ��ȹ �Ǻ���
	bool getPokemon = false;					//���ϸ� ��ȹ ����
	bool playerGetPokemon = false;				//�÷��̾�� ���ϸ� �߰�
	bool getPokemonRenderOn = false;			//���ϸ� ��ȹ ������ ��
	int currentBallIndex = 0;								// 0 ~ 16;
	wstring ballThrowClipName[17];
	wstring ballMissClipName[17];
	wstring ballGetClipName[17];

};
