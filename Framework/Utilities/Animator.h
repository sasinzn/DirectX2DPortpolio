#pragma once

class AnimationClip
{
public:
	friend class Animator;
	AnimationClip
	(wstring clipName, Texture2D* srcTex , UINT frameCount, Vector2 startPos, Vector2 endPos , bool bReversed = false , float palyRate = 1.f/ 12.f);


protected:
	wstring clipName = L"";
	vector<Vector2> keyFrames;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	bool bReversed = false;
	float playRate = 0.f;

};


class Animator
{
public:
	Animator();
	~Animator();

	void Update();
	void AddAnimClip(AnimationClip* animClip);
	void ClearAnimClip();
	void SetCurrentAnimClip(wstring clipName);
	void SetLoopOff() { loopAni = false; }
	void SetLoopOn() { loopAni = true; }
	void SetAniOff() { aniOff = true; }
	void SetAniReset() { currentFrameIndex = 0; aniEnd = false; }
	void SetFrame(int indexNo) { currentFrame = currentClip->keyFrames[indexNo]; }
	bool GetAniEnd() { return aniEnd; }
	UINT GetFrameIndex() { return currentFrameIndex; }

	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }
	
private:
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }

private:
	unordered_map<wstring, AnimationClip*> animClips;

	AnimationClip* currentClip = nullptr;		// ���� ����ǰ� �ִ� Ŭ��
	UINT currentFrameIndex = 0;					// ���� �������� �ε���
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.f;					// ������ ���� ����
	bool loopAni = true;					// �ִϸ��̼� ����
	bool aniEnd = false;					// �ִϸ��̼� ��� ��
	bool aniOff = false;
};
