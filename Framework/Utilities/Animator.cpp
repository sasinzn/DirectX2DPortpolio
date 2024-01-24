#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed, float playRate)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed) , playRate(playRate)
{
	srv = srcTex->GetSRV();

	// �̹����� ũ�⸦ ����
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// Ŭ�� ������ ( �ִϸ��̼��� �ִ� �ؽ�ó�� ũ�� )
	Vector2 clipSize = endPos - startPos;

	// ������ ������ ( �ִϸ��̼� �� �ϳ��� ũ�� )
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// �ؼ� ������ ������ ��� (UV ��ǥ������ ũ�� ��� )
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// �ؼ� ���� ��ġ
	Vector2 texcelStartPos;

	texcelStartPos.x = startPos.x / imageWidth;
	texcelStartPos.y = startPos.y / imageHeight;

	// ���� ����Ǵ� ������

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyFrame.x = texcelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texcelStartPos.y;

		keyFrames.push_back(keyFrame);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
		SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (!aniOff)
	{
		if (deltaTime > currentClip->playRate)
		{
			if (currentClip->bReversed == false)
			{
				currentFrameIndex++;

				if (currentFrameIndex == currentClip->frameCount && loopAni == true)
					currentFrameIndex = 0;
				else if (currentFrameIndex == currentClip->frameCount && loopAni == false)
				{
					currentFrameIndex--;
					aniEnd = true;
				}


				currentFrame = currentClip->keyFrames[currentFrameIndex];

			}
			else
			{
				currentFrameIndex--;

				if (currentFrameIndex == -1 && loopAni == true)
					currentFrameIndex = currentClip->frameCount - 1;
				else if (currentFrameIndex == -1 && loopAni == false)
				{
					currentFrameIndex++;
					aniEnd = true;
				}
					

				currentFrame = currentClip->keyFrames[currentFrameIndex];
			}
			deltaTime = 0.f;

		}
		else
			deltaTime += Time::Delta();
	}

	


}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::ClearAnimClip()
{
	animClips.clear();
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = animClips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipName == clipName)
		return;

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		deltaTime = 0.f;

		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		currentFrame = currentClip->keyFrames[currentFrameIndex];
		
	}
}
