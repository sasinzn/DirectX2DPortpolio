#include "Framework.h"
#include "Star.h"

#define PI 3.1415926

Star::Star(Vector3 position, Vector3 size, float rotation)
	:position(position), size(size), rotation(rotation)
{
	{
		vertices.assign(6, VertexColor());

		vertices[0].position = Vector3(cos(PI / 3) , sin(PI / 3) , 0.0f);  // ¿ì»ó´Ü
		vertices[0].color = color;

		vertices[1].position = Vector3(1 , 0.0f , 0.0f); //  ¿ìÃø
		vertices[1].color = color;

		vertices[2].position = Vector3(cos(PI / 3), -sin(PI / 3), 0.0f); // ¿ìÇÏ´Ü
		vertices[2].color = color;

		vertices[3].position = Vector3(-cos(PI / 3) , -sin(PI / 3), 0.0f); // ÁÂ ÇÏ´Ü
		vertices[3].color = color;

		vertices[4].position = Vector3(-1.0f, 0.0f, 0.0f); // ÁÂÃø
		vertices[4].color = color;

		vertices[5].position = Vector3(-cos(PI / 3), sin(PI / 3), 0.0f); // ÁÂ»ó´Ü
		vertices[5].color = color;

		
	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Index Buffer
	{
		indices = { 0, 2, 4, 1, 3, 5 };

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
}

Star::~Star()
{
	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void Star::Update()
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

void Star::Render()
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

void Star::GUI()
{
	ImGui::Begin("Star", &bOpen);
	{
		ImGui::InputFloat3(MakeLabel("Pos").c_str(), position, 2);
		ImGui::InputFloat3(MakeLabel("Size").c_str(), size, 2);
		ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation);
		if (ImGui::ColorPicker4("Color", color))
			UpdateColor();
	}
	ImGui::End();
}

void Star::UpdateColor()
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

string Star::MakeLabel(string preFix)
{
	string label = preFix + "##" + to_string((uint)this);

	return label;
}
