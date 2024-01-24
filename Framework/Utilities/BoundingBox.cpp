#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox(Vector3 position, Vector3 size, float rotation, Color color)
	: position(position), size(size), rotation(rotation), color(color)
{
	edge = new RectEdge();
	data = new AxisData();

	Init();
}

BoundingBox::~BoundingBox()
{
	SAFE_RELEASE(bs);

	SAFE_DELETE(cb);
	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);

	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::Init()
{
	// vertices
	{
		vertices.assign(4, VertexColor());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
		vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);

		for (VertexColor& v : vertices)
			v.color = color;
	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Index Buffer
	{
		indices = { 0,1,2,0,3,1 };

		ib = new IndexBuffer;
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// Vertex Shader
	{
		vs = new VertexShader;
		vs->Create(ShaderPath + L"CollisionShader.hlsl", "VS");
	}

	// Input Layout
	{
		il = new InputLayout;
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// Pixel Shader
	{
		ps = new PixelShader;
		ps->Create(ShaderPath + L"CollisionShader.hlsl", "PS");
	}

	// Buffer
	{
		wb = new WorldBuffer;
		cb = new CollisionBuffer;
	}

	// Blend State
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bs);
	}
}


void BoundingBox::Update()
{

	world =
		DXMath::Scaling(this->size) *
		DXMath::RotationInDegree(this->rotation) *
		DXMath::Translation(this->position);

	wb->SetWorld(world);

	if (Keyboard::Get()->Down(VK_F1))
		cb->SwitchRender();
}

void BoundingBox::Update(Vector3 position, Vector3 size, float rotation)
{
	this->position = position;
	this->size = size;
	this->rotation = rotation;

	world =
		DXMath::Scaling(this->size) *
		DXMath::RotationInDegree(this->rotation) *
		DXMath::Translation(this->position);

	wb->SetWorld(world);

	if (Keyboard::Get()->Down(VK_F1))
		cb->SwitchRender();
}

void BoundingBox::Render()
{
	// IA
	{
		vb->SetIA();
		ib->SetIA();
		il->SetIA();
		DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	// VS
	{
		vs->SetShader();
		wb->SetVSBuffer(0);
	}

	// PS
	{
		ps->SetShader();
		cb->SetPSBuffer(0);
	}

	DC->DrawIndexed(ib->GetCount(), 0, 0);
	DC->OMSetBlendState(bs, nullptr, 0xFFFFFFFF);
}

void BoundingBox::UpdateCollisionData()
{
	// AABB
	{
		D3DXVec3TransformCoord(&edge->LT, &vertices[3].position, &world);
		D3DXVec3TransformCoord(&edge->LB, &vertices[0].position, &world);
		D3DXVec3TransformCoord(&edge->RT, &vertices[1].position, &world);
		D3DXVec3TransformCoord(&edge->RB, &vertices[2].position, &world);
	}

	// OBB
	{
		// Center Position Vector Update
		{
			float x = (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) / 4.f;
			float y = (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) / 4.f;

			data->centerPos = Vector3(x, y, 0);
		}

		// Axis Vector Update
		{
			D3DXVec3TransformNormal(&data->axisDir[x], &Values::RightVec, &world);
			D3DXVec3TransformNormal(&data->axisDir[y], &Values::UpVec, &world);

			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}

		// Axis Length Update
		{
			Vector3 unitAxes[2] = { data->axisDir[x], data->axisDir[y] };

			Vector3 verticesPos[4] = { edge->LT, edge->LB, edge->RT, edge->RB };
			float minValues[2] = { INT_MAX, INT_MAX };
			float maxValues[2] = { INT_MIN, INT_MIN };

			for (int i = 0; i < 4; ++i)
			{
				Vector3 point = verticesPos[i];

				for (int j = 0; j < 2; ++j)
				{
					float projection = D3DXVec3Dot(&point, &unitAxes[j]);

					if (projection < minValues[j])
						minValues[j] = projection;

					if (projection > maxValues[j])
						maxValues[j] = projection;
				}
			}
			data->axisLen[x] = (maxValues[x] - minValues[x]) / 2;
			data->axisLen[y] = (maxValues[y] - minValues[y]) / 2;
		}
	}
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if (a == nullptr || b == nullptr) return false;

	RectEdge aEdge = *a->edge;
	RectEdge bEdge = *b->edge;

	if (aEdge.RB.x >= bEdge.LT.x &&
		aEdge.LT.x <= bEdge.RB.x &&
		aEdge.LT.y >= bEdge.RB.y &&
		aEdge.RB.y <= bEdge.LT.y)
		return true;

	return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;

	centerDir = ad.centerPos - bd.centerPos;

	// a Rect : X Axis
	{
		axis = ad.axisDir[x];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[x];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}

	// a Rect : Y Axis
	{
		axis = ad.axisDir[y];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[y];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}

	// b Rect : X Axis
	{
		axis = bd.axisDir[x];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[x];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}

	// b Rect : Y Axis
	{
		axis = bd.axisDir[y];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[y];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}

	return true;
}


void BoundingBox::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexColor& v : vertices)
			v.color = color;

		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());

	}

	DC->Unmap(vb->GetResource(), 0);
}


void BoundingBox::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}



/*

BoundingBox::BoundingBox(Vector3 position, Vector3 size, float rotation, Color color)
	:position(position), size(size), rotation(rotation), color(color)
{
	edge = new RectEdge();
	data = new AxisData();

	Init();
}

BoundingBox::~BoundingBox()
{
	SAFE_RELEASE(bs);

	SAFE_DELETE(cb);
	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::Init()
{
	// vertices
	{
		vertices.assign(4, VertexColor());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);

		for (VertexColor& v : vertices)
			v.color = color;

	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Index Buffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer;
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// Vertex Shader
	{
		vs = new VertexShader;
		vs->Create(ShaderPath + L"CollisionShader.hlsl", "VS");
	}

	// Input Layout
	{
		il = new InputLayout;
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// Pixel Shader
	{
		ps = new PixelShader;
		ps->Create(ShaderPath + L"CollisionShader.hlsl", "PS");
	}

	// Buffer
	{
		wb = new WorldBuffer;
		cb = new CollisionBuffer;
	}

	// Blend State
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bs);


	}

}

void BoundingBox::Update(Vector3 position, Vector3 size, float rotation) // 충돌체의 크기, 회전방향 , 충돌체의 위치(입력시 이동)
{
	this->position = position;
	this->size = size;
	this->rotation = rotation;


	world =
		DXMath::Scaling(this->size) *
		DXMath::RotationInDegree(this->rotation) *
		DXMath::Translation(this->position);



	wb->SetWorld(world);

	if (Keyboard::Get()->Down(VK_F1))
		cb->SwitchRender();
}

void BoundingBox::Render()
{
	// IA
	{
		vb->SetIA();
		ib->SetIA();
		il->SetIA();
		DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	// VS
	{
		vs->SetShader();
		wb->SetVSBuffer(0);
	}

	// PS
	{
		ps->SetShader();
		cb->SetPSBuffer(0);
	}

	DC->DrawIndexed(ib->GetCount(), 0, 0);
	DC->OMSetBlendState(bs, nullptr, 0xFFFFFFFF);
}

void BoundingBox::UpdateCollisionData()
{
	// AABB
	{
		D3DXVec3TransformCoord(&edge->LT, &vertices[3].position, &world);
		D3DXVec3TransformCoord(&edge->LB, &vertices[0].position, &world);
		D3DXVec3TransformCoord(&edge->RT, &vertices[1].position, &world);
		D3DXVec3TransformCoord(&edge->RB, &vertices[2].position, &world);
	}

	// OBB
	{
		// Center Position Vector Update
		{
			float x = (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) / 4.f;
			float y = (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) / 4.f;

			data->centerPos = Vector3(x, y, 0);
		}

		// Axis Vector Update
		{
			D3DXVec3TransformNormal(&data->axisDir[x], &Values::RightVec, &world);
			D3DXVec3TransformNormal(&data->axisDir[y], &Values::UpVec, &world);

			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}



		// Axis Length Update
		{
			Vector3 unitAxes[2] = { data->axisDir[x], data->axisDir[y] };

			Vector3 verticesPos[4] = { edge->LT, edge->LB , edge->RT, edge->RB };
			float minValue[2] = { INT_MAX, INT_MAX };
			float maxValue[2] = { INT_MIN, INT_MIN };

			for (int i = 0; i < 4; i++)
			{
				Vector3 point = verticesPos[i];

				for (int j = 0; j < 2; j++)
				{
					float projection = D3DXVec3Dot(&point, &unitAxes[j]);

					if (projection < minValue[j])
						minValue[j] = projection;

					if (projection > maxValue[j])
						maxValue[j] = projection;

				}

			}
			data->axisLen[x] = (maxValue[x] - minValue[x]) / 2;
			data->axisLen[y] = (maxValue[y] - minValue[y]) / 2;


		}


	}

}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if (a == nullptr || b == nullptr) return false;

	RectEdge aEdge = *a->edge;
	RectEdge bEdge = *b->edge;

	if (aEdge.RB.x >= bEdge.LT.x &&
		aEdge.LT.x <= bEdge.RB.x &&
		aEdge.LT.y >= bEdge.RB.y &&
		aEdge.RB.y <= bEdge.LT.y)
		return true;

	return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;

	centerDir = ad.centerPos - bd.centerPos;

	// a Rect : X Axis
	{
		axis = ad.axisDir[x];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[x];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			 abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}

	// a Rect : Y Axis
	{
		axis = ad.axisDir[y];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[y];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			 abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;

	}

	// b Rect : X Axis
	{
		axis = bd.axisDir[x];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[x];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			 abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;

	}

	// b Rect : Y Axis
	{
		axis = bd.axisDir[y];

		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[y];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			 abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;

	}

	return true;
}

void BoundingBox::ColorEdgeInit(BoundingBox* a)
{

	RectEdge aEdge;

	D3DXVec3TransformCoord(&aEdge.LT, &vertices[3].position, &world);
	D3DXVec3TransformCoord(&aEdge.LB, &vertices[0].position, &world);
	D3DXVec3TransformCoord(&aEdge.RT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&aEdge.RB, &vertices[2].position, &world);
	//상단
	{
		ce.LT = aEdge.LT; // 좌상단
		ce.RT = aEdge.RT; // 우상단
		ce.TC = Vector3(aEdge.RT.x / 2, aEdge.LT.y, aEdge.LT.z); // 상단 중앙
		ce.LTTC = Vector3(ce.TC.x / 2, aEdge.LT.y, aEdge.LT.z); // 좌상 ~ 상단 센터 중앙
		ce.TCRT = Vector3(aEdge.RB.x - ce.LTTC.x, aEdge.LT.y, aEdge.LT.z); // 상단센터 ~ 우상단
	}

	//하단
	{
		ce.LB = aEdge.LB;								//좌 하단
		ce.RB = aEdge.RB;								//우 하단
		ce.BC = Vector3(ce.TC.x, ce.LB.y, ce.LB.z);			//하단 센터
		ce.LBBC = Vector3(ce.LTTC.x, ce.LB.y, ce.LB.z);		//좌 하단 ~ 하단 센터
		ce.BCRB = Vector3(ce.TCRT.x, ce.LB.y, ce.LB.z);		//하단 센터 ~ 우 하단
	}

	//좌측
	{
		ce.LTLC = Vector3(ce.LB.x, ce.LC.y / 2, ce.LB.z);			// 좌 상단 ~ 좌 센터
		ce.LC = Vector3(ce.LB.x, ce.LB.y / 2, ce.LB.z);				// 좌 센터
		ce.LCLB = Vector3(ce.LB.x, ce.LB.y - ce.LTLC.y, ce.LB.z);	// 좌 센터 ~ 좌 하단
	}
	//우측
	{
		ce.RTRC = Vector3(ce.RB.x, ce.LTLC.y, ce.RB.z);		// 우 상단 ~ 우 센터
		ce.RC 	= Vector3(ce.RB.x, ce.LC.y, ce.RB.z);		// 우 센터
		ce.RCRB = Vector3(ce.RB.x, ce.LCLB.y, ce.RB.z);		// 우 센터 ~ 우 하단
	}


}

int BoundingBox::ColorBounding(BoundingBox* a, vector<Color>* pixels, float width, float height)
{
	a->ColorEdgeInit(a);

	int pixelNum = width * height;
	Color* color = new Color[pixelNum];

	vector<Color>::iterator iter;
	iter = pixels->begin();

//	int count;
//	for(iter ; iter != pixels->end(); iter++, ++count)
//		color[count-1] = *iter;

	ColorEdge aEdge = a->ce;
	// 인덱스 값 계산
	//상단
	int indexLT = (aEdge.LT.x * width) + (aEdge.LT.y * height) * width;
	int indexLTTC = (aEdge.LTTC.x * width) + (aEdge.LTTC.y * height) * width;
	int indexTC = (aEdge.TC.x * width)  + (aEdge.TC.y * height) * width;
	int indexTCRT = (aEdge.TCRT.x * width) + (aEdge.TCRT.y * height) * width;
	int indexRT = (aEdge.RT.x * width)  + (aEdge.RT.y * height) * width;

	//하단
	int indexLB = (aEdge.LB.x * width)  + (aEdge.LB.y * height * width);
	int indexLBBC = (aEdge.LBBC.x * width)  + (aEdge.LBBC.y * height * width);
	int indexBC = (aEdge.BC.x * width)  + (aEdge.BC.y * height * width);
	int indexBCRB = (aEdge.BCRB.x * width)  + (aEdge.BCRB.y * height * width);
	int indexRB = (aEdge.RB.x * width) + (aEdge.RB.y * height * width);

	//좌측
	int indexLTLC = (aEdge.LTLC.x * width) + (aEdge.LTLC.y * height * width);
	int indexLC = (aEdge.LC.x * width) + (aEdge.LC.y * height * width);
	int indexLCLB = (aEdge.LCLB.x * width) + (aEdge.LCLB.y * height * width);

	//우측
	int indexRTRC = (aEdge.RTRC.x * width) + (aEdge.RTRC.y * height * width);
	int indexRC = (aEdge.RC.x * width) + (aEdge.RC.y * height * width);
	int indexRCRB = (aEdge.RCRB.x * width) + (aEdge.RCRB.y * height * width);

	//상단 충돌 return 1
	if ((iter[indexLT] == 0 || iter[indexRT] == 0) && (iter[indexLTTC] == 0 || iter[indexTC] == 0 || iter[indexTCRT] == 0))
		return 1;
	//좌측 상단 혹은 우측상단과 상단 중앙 3점중 하나가 블랙일때 상단 충돌

	//하단 충돌 return 2
	if ((iter[indexLB] == 0 || iter[indexRB] == 0) && (iter[indexLBBC] == 0 || iter[indexBC] == 0 || iter[indexBCRB] == 0))
		return 2;
	//좌측 하단 혹은 우측 하단과 하단 중앙 3점중 하나가 블랙일때 하단 충돌

	//좌측 충돌 return 3
	if ((iter[indexLT] == 0 || iter[indexLB] == 0) && (iter[indexLTLC] == 0 || iter[indexLC] == 0 || iter[indexLCLB] == 0))
		return 3;
	//좌측 상단 혹은 좌측 하단과 좌측 중앙 3점중 하나가 블랙일떄 좌측 충돌

	//우측 충돌 return 4
	if ((iter[indexRT] == 0 || iter[indexRB] == 0) && (iter[indexRTRC] == 0 || iter[indexRC] == 0 || iter[indexRCRB] == 0))
		return 4;
	//우측 상단 혹은 우측 하단과 우측 중앙 3점중 하나가 블랙일때 우측 충돌


	// 동적할당 해제
	{
		SAFE_DELETE_ARRAY(color);
	}

	return 0;
}


*/

