#pragma once

class RectGame
{
public:
	RectGame(Vector3 position, Vector3 size, float rotation);
	~RectGame();

	void Update();
	void Render();

	void Move();
	void Jump();
	void Gravity();

	void GUI();

	void UpdateColor();
	string MakeLabel(string preFix);

	void UpdateWorld();
	void SetColor(Color color);
	void SetPlayer() { bPlayer = true; } // 박스가 플레이어이 인지 설정
	bool GetCol() { return bCol; }

	void SetCol(bool col) { bCol = col; }
		

	BoundingBox* GetCollision() { return collision; }

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
	bool bPlayer = false;	// 해당 박스가 플레이어 인지 확인
	bool bCol = false;		// 현재 충돌중인지 확인
	
	BoundingBox* collision = nullptr;

	Vector3 verticesPosition[4];
};
