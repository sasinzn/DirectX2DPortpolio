#pragma once

#include "TextureRect.h"

class BlurBuffer : public ShaderBuffer
{
public:
	BlurBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		data.textureSize = Values::ZeroVec2;
		data.blurCount = 1;
	}

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}

	int* GetblurCountPtr() { return &data.blurCount; }

	struct Data
	{
		Vector2 textureSize;
		int blurCount;
		int dummy;
	};

private:
	Data data;

};

class BlurTexture : public TextureRect
{
public:
	BlurTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~BlurTexture();

	void Update();
	void Render();

	void GUI();

private:
	BlurBuffer* buffer = nullptr;
};