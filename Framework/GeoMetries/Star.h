#pragma once
class Star
{
public:
	Star(Vector3 position, Vector3 size, float rotation);
	~Star();

	void Update();
	void Render();

	void GUI();

	void UpdateColor();
	string MakeLabel(string preFix);

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world;
	Matrix S, R, T;

	Vector3 position;
	Vector3 size;
	float rotation;

	Color color = Color(1, 0, 0, 1);

	WorldBuffer* wb = nullptr;

	bool bOpen = true;


};