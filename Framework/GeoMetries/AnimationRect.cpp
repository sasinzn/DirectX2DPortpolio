#include "Framework.h"
#include "AnimationRect.h"



AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	:TextureRect(position, size, 0.f)
{
	SetShader(ShaderPath + L"Animation.hlsl");

	
	/*
	animator = new Animator();

	Texture2D* srcTex = new Texture2D(TexturePath + L"player.png");
	AnimationClip* RunR = new AnimationClip(L"RunR", srcTex, 10, Values::ZeroVec2, { srcTex->GetWidth(), srcTex->GetHeight() * .5f });
	AnimationClip* RunL = new AnimationClip(L"RunL", srcTex, 10, {0, srcTex->GetHeight() * .5f}, { srcTex->GetWidth(), srcTex->GetHeight() }, true);

	animator->AddAnimClip(RunR);
	animator->AddAnimClip(RunL);
	animator->SetCurrentAnimClip(L"RunL");

	SAFE_DELETE(srcTex);

	*/

	

	// Sampler
	{
		// 선형 보간
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// 점 보간
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);

	}
}

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation)
	:TextureRect(position, size, rotation)
{

	SetShader(ShaderPath + L"Animation.hlsl");

	// Sampler
	{
		// 선형 보간
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// 점 보간
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);

	}

}

AnimationRect::~AnimationRect()
{
}

void AnimationRect::Update()
{
	animator->Update();

	MapVertexBuffer();
	{
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;


	}
	UnmapVertexBuffer();

	__super::Update();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

void AnimationRect::Move(bool holding)
{
	if (!holding)
	{
		auto key = Keyboard::Get();
		float delta = Time::Delta();

		if (key->Press(VK_LSHIFT))
		{		

			if (key->Press('W'))
			{
				position.y += 150 * delta;
				animator->SetCurrentAnimClip(L"RunU");
				if(key->Press('A'))
					position.x -= 150 * delta;
				if(key->Press('D'))
					position.x += 150 * delta;
			}
			else if (key->Press('S'))
			{
				position.y -= 150 * delta;
				animator->SetCurrentAnimClip(L"RunD");
				if (key->Press('A'))
					position.x -= 150 * delta;
				if (key->Press('D'))
					position.x += 150 * delta;
			}
			else if (key->Press('A'))
			{
				position.x -= 150 * delta;
				animator->SetCurrentAnimClip(L"RunL");

			}
			else if (key->Press('D'))
			{
				position.x += 150 * delta;
				animator->SetCurrentAnimClip(L"RunR");

			}
		}
		else
		{
			if (key->Press('W'))
			{
				position.y += 100 * delta;
				animator->SetCurrentAnimClip(L"WalkU");
				if (key->Press('A'))
					position.x -= 100 * delta;
				if (key->Press('D'))
					position.x += 100 * delta;

			}
			else if (key->Press('S'))
			{
				position.y -= 100 * delta;
				animator->SetCurrentAnimClip(L"WalkD");
				if (key->Press('A'))
					position.x -= 100 * delta;
				if (key->Press('D'))
					position.x += 100 * delta;
			}
			else if (key->Press('A'))
			{
				position.x -= 100 * delta;
				animator->SetCurrentAnimClip(L"WalkL");

			}
			else if (key->Press('D'))
			{
				position.x += 100 * delta;
				animator->SetCurrentAnimClip(L"WalkR");

			}
		}
	}
//	cout << "X : " << position.x << "Y : " << position.y << endl;
}
