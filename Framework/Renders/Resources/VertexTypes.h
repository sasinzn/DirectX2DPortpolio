#pragma once
// 버텍스 정보를 저장하기 위한 구조체

// 색상

struct VertexColor
{
	VertexColor()
		:position(0, 0, 0), color(0, 0, 0, 0) {}

	VertexColor(Vector3 postion, Color color)
		:position(postion), color(color) {}

	Vector3 position;
	Color color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;

};

struct VertexTexture
{
	VertexTexture()
		:position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 postion, Color uv)
		:position(postion), uv(uv) {}

	Vector3 position;
	Vector2 uv;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;


};

struct VertexTile
{
	VertexTile()
		: position(Values::ZeroVec3), uv(Values::ZeroVec2), color(0, 0, 0, 0) {}

	VertexTile(Vector3 position, Vector2 uv, Vector2 uv2, Color color, uint index)
		: position(position), uv(uv), uv2(uv2), color(color), index(index) {}

	Vector3 position;
	Vector2 uv;
	Vector2 uv2;
	Color color;
	uint index;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 5;
};

