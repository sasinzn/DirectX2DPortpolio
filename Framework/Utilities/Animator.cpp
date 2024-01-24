#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed, float playRate)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed) , playRate(playRate)
{
	srv = srcTex->GetSRV();

	// 이미지의 크기를 저장
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// 클립 사이즈 ( 애니메이션이 있는 텍스처의 크기 )
	Vector2 clipSize = endPos - startPos;

	// 프레임 사이즈 ( 애니메이션 중 하나의 크기 )
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 텍셀 프레임 사이즈 계산 (UV 좌표에서의 크기 계산 )
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// 텍셀 시작 위치
	Vector2 texcelStartPos;

	texcelStartPos.x = startPos.x / imageWidth;
	texcelStartPos.y = startPos.y / imageHeight;

	// 현재 재생되는 프레임

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
