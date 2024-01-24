#pragma once

class UI
{
public:
	enum FillType
	{
		NONE = 0,
		LEFT_TO_RIGHT,
		RIGHT_TO_LEFT,
		UP_TO_DOWN,
		DOWN_TO_UP,
	};
public:
	virtual ~UI();
	
	virtual void Update();
	virtual void Render();

	void Init(Vector3 position, Vector3 size, float rotation, Color color, FillType type = NONE);
	void Init(Vector3 position, Vector3 size, float rotation, wstring path, FillType type = NONE);
	void Init(Vector3 position, Vector3 size, float rotation, FillType type = NONE);
	
	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void SetShader(wstring shaderPath);

private:
	template<typename T> 
	void SetVertices(vector<T>& vertices, FillType type);

	void UpdateWorld();
	void UpdatePosition();


protected:
	vector<VertexColor> colorVertices;
	vector<VertexTexture> textureVertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	WorldBuffer* wb = nullptr;
	Matrix world;

	Vector3 originSize;
	Vector3 originPosition;
	
	Vector3 position;
	Vector3 size;
	float rotation;

	Color color;
	Vector2 uv;

	ID3D11ShaderResourceView* srv = nullptr;
	D3D11_MAPPED_SUBRESOURCE subResource;

};