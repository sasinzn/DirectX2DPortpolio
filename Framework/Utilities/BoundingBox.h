#pragma once

enum
{
	x = 0,
	y,
};

struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};

struct AxisData
{
	Vector3 centerPos;
	Vector3 axisDir[2];
	float axisLen[2];
};

class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.isOn = 1;
	}

	void SwitchRender() { data.isOn = !data.isOn; }

	struct Data
	{
		int isOn;
		Vector3 dummy;
	};

private:
	Data data;
};

class BoundingBox
{
public:
	BoundingBox(Vector3 position, Vector3 size, float rotation, Color color);
	~BoundingBox();

	void Init();

	void Update();
	void Update(Vector3 position, Vector3 size, float rotation);
	void Render();

	void UpdateColor();
	void SetColor(Color color);
	void UpdateCollisionData();

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world;
	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;
	Color color;

	CollisionBuffer* cb = nullptr;
	ID3D11BlendState* bs = nullptr;

	RectEdge* edge = nullptr;
	AxisData* data = nullptr;
};



/*
enum
{
	x = 0,
	y,
};

struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};

struct AxisData
{
	Vector3 centerPos;
	Vector3 axisDir[2];
	float axisLen[2];

};

struct ColorEdge
{
	Vector3 LT, LTTC, TC, TCRT, RT; // 상단
	Vector3 LB, LBBC, BC, BCRB, RB; // 하단
	Vector3 LTLC, LC, LCLB;			// 좌측
	Vector3 RTRC, RC, RCRB;			// 우측
};


class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.isOn = 1;
	}

	void SwitchRender() { data.isOn = !data.isOn; }

	struct Data
	{
		int isOn;
		Vector3 dummy;
	};
private:
	Data data;
};


class BoundingBox
{
public:
	BoundingBox(Vector3 position, Vector3 size, float rotation, Color color);
	~BoundingBox();

	void Init();

	void Update(Vector3 position, Vector3 size, float rotation);
	void Render();


	void UpdateCollisionData();

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);
	void ColorEdgeInit(BoundingBox* a);
	static int ColorBounding(BoundingBox* a, vector<Color>* pixels, float width, float height);

private:

	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world;
	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;
	Color color;

	CollisionBuffer* cb = nullptr;
	ID3D11BlendState* bs = nullptr;

	RectEdge* edge = nullptr;
	AxisData* data = nullptr;

	ColorEdge ce;
};

*/
