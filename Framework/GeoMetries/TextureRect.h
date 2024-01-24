#pragma once

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
	TextureRect(Vector3 position, Vector3 size, float rotation);
	~TextureRect();

	virtual void Move(bool holding);
	
	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderpath);
	void SetSize(Vector3 size) { this->size = size; };
	void SetPosition(Vector3 pos) { this->position = pos; }

	void Update();
	void UpdateWorld();
	void Render();
	void GUI();

	const Vector3* GetVerticesLocalPosition() { return verticesLocalPosition; }
	const Matrix GetWorld() { return world; }

	const Vector3 GetPosition() { return position; }
	const Vector3 GetSize() { return size; }
	const float GetRotation() { return rotation; }
	

protected:
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;
	InputLayout* il = nullptr;

	Matrix world;
	Matrix S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;

	ID3D11ShaderResourceView* srv = nullptr;
	D3D11_MAPPED_SUBRESOURCE subResource;

	Vector3 verticesLocalPosition[4];
};