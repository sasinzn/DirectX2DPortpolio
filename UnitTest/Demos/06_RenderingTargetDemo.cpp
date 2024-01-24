#include "stdafx.h"
#include "06_RenderingTargetDemo.h"

#include "GeoMetries/Rect.h"
#include "GeoMetries/TextureRect.h"
#include "Utilities/Rendertexture.h"

void RenderingTargetDemo::Init()
{
	rtt = new RenderTexture;

	Vector3 size = Vector3(100, 100, 1);
	Vector3 trPos = Vector3(WinMaxWidth - (WinMaxWidth / 4), WinMaxHeight - (WinMaxHeight / 4), 0);
	Vector3 trsiz = Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0);
	float rot = 0;

	r1 = new Rect(Vector3(200, 200, 0), size, rot);
	r2 = new Rect(Vector3(500, 400, 0), size, rot);
	r3 = new Rect(Vector3(700, 100, 0), size, rot);

	tr1 = new TextureRect(Vector3(100, 100, 0), Vector3(500, 500, 1), 0.f, TexturePath + L"asdf.jpg");
	tr2 = new TextureRect(trPos, trsiz, rot);

//	tr2->SetShader(ShaderPath + L"VertexTexture.hlsl");
	tr2->SetShader(ShaderPath + L"VertexTextureOutLine.hlsl");

}

void RenderingTargetDemo::Destroy()
{
	SAFE_DELETE(tr2);
	SAFE_DELETE(tr1);
	SAFE_DELETE(r3);
	SAFE_DELETE(r2);
	SAFE_DELETE(r1);
	SAFE_DELETE(rtt);
}

void RenderingTargetDemo::Update()
{
	r1->Update();
	r2->Update();
	r3->Update();
	tr1->Update();
	tr2->Update();
}

void RenderingTargetDemo::Render()
{
	r1->Render();
	r2->Render();
	r3->Render();

	tr1->Render();
	tr2->SetSRV(rtt->Getsrv());
	tr2->Render();


}

void RenderingTargetDemo::PostRender()
{
	Graphics::Get()->InitViewport();
	rtt->RenderToTexture();
	{
		r1->Render();
		r2->Render();
		r3->Render();

		tr1->Render();
	}
}

void RenderingTargetDemo::GUI()
{
}
