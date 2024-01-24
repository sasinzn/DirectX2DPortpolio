#include "Framework.h"
#include "RectGame.h"

RectGame::RectGame(Vector3 position, Vector3 size, float rotation)
	:position(position), size(size), rotation(rotation)
{
	// vertices
	{
		vertices.assign(4, VertexColor());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = color;

		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = color;

		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = color;

		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].color = color;


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
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
	}

	// Input Layout
	{
		il = new InputLayout;
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// Pixel Shader
	{
		ps = new PixelShader;
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
	}

	// World
	{
		wb = new WorldBuffer;

	}

	
	// Collision
	{
//		collision = new BoundingBox();

		for (int i = 0; i < 4; i++)
		{
			verticesPosition[i] = vertices[i].position;
		}

	}

}

RectGame::~RectGame()
{
	SAFE_DELETE(collision);

	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void RectGame::Update()
{
	Gravity();
	UpdateWorld();

//	collision->UpdateCollisionData(world, verticesPosition);
}

void RectGame::Render()
{
	//IA
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
	}

	DC->DrawIndexed(ib->GetCount(), 0, 0);

}

void RectGame::Move()
{

	//	키보드 컨트롤 ( 좌우 이동과 점프만 가능 )


	if (Keyboard::Get()->Press('A'))
		position.x -= 10;

	if (Keyboard::Get()->Press('D'))
		position.x += 10;

	if (Keyboard::Get()->Down(VK_SPACE))
		Jump();
}

void RectGame::Jump()
{

	position.y += 80;
}

void RectGame::Gravity()
{
	if (bPlayer == true )
		position.y -= 1;
	else if (bPlayer == true && bCol == true)
		position.y -= 0.3;
	else
		position.y -= 0.3;
}

void RectGame::GUI()
{
	ImGui::Begin("Rect", &bOpen);
	{
		ImGui::InputFloat3(MakeLabel("Pos").c_str(), position, 2);
		ImGui::InputFloat3(MakeLabel("Size").c_str(), size, 2);
		ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation);
		if (ImGui::ColorPicker4("Color", color))
			UpdateColor();
	}
	ImGui::End();
}

void RectGame::UpdateColor()
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

string RectGame::MakeLabel(string preFix)
{
	string label = preFix + "##" + to_string((uint)this);

	return label;
}

void RectGame::UpdateWorld()
{
	//SRT

	//Scale
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	// Rotation
	D3DXMatrixRotationZ(&R, rotation);
	// Translation
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);

	
}

void RectGame::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}
