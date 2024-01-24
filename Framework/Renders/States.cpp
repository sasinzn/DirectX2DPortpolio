#include "Framework.h"
#include "States.h"

D3D11_RASTERIZER_DESC States::rsDesc;
D3D11_DEPTH_STENCIL_DESC States::dsDesc;
D3D11_SAMPLER_DESC States::spDesc;
D3D11_BLEND_DESC States::blDesc;

void States::Create()
{
	CreateRasterizerDesc();
	CreateDepthStencilDesc();
	CreateSamplerDesc();
	CreateBlendDesc();


}

#pragma region Get Desc

void States::GetRasterizerDesc(D3D11_RASTERIZER_DESC* desc)
{
    memcpy(desc, &rsDesc, sizeof(D3D11_RASTERIZER_DESC));
}

void States::GetDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc)
{
    memcpy(desc, &dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
}

void States::GetSamplerDesc(D3D11_SAMPLER_DESC* desc)
{
    memcpy(desc, &spDesc, sizeof(D3D11_SAMPLER_DESC));
}

void States::GetBlendDesc(D3D11_BLEND_DESC* desc)
{
    memcpy(desc, &blDesc, sizeof(D3D11_BLEND_DESC));
}

#pragma endregion


#pragma region Create State


void States::CreateRasterizer(D3D11_RASTERIZER_DESC* desc, ID3D11RasterizerState** state)
{
    HRESULT hr = DEVICE->CreateRasterizerState(desc, state);
    CHECK(hr);
}

void States::CreateDepthStencil(D3D11_DEPTH_STENCIL_DESC* desc, ID3D11DepthStencilState** state)
{
    HRESULT hr = DEVICE->CreateDepthStencilState(desc, state);
    CHECK(hr);
}

void States::CreateSampler(D3D11_SAMPLER_DESC* desc, ID3D11SamplerState** state)
{
    HRESULT hr = DEVICE->CreateSamplerState(desc, state);
    CHECK(hr);
}

void States::CreateBlend(D3D11_BLEND_DESC* desc, ID3D11BlendState** state)
{
    HRESULT hr = DEVICE->CreateBlendState(desc, state);
    CHECK(hr);
}


#pragma endregion



#pragma region Create Desc



void States::CreateRasterizerDesc()             // �ȼ�ȭ �����ִ� �༮
{
	Zero(rsDesc);

    rsDesc.FillMode = D3D11_FILL_SOLID;         // �ٰ����� ä��� ���
    rsDesc.CullMode = D3D11_CULL_BACK;          // �ĸ� �ø� ��� ����
    rsDesc.FrontCounterClockwise = false;       // ���� ���� ������ �ð�������� ����
    rsDesc.DepthBias = 0;                       // ���� ���̾ ��
    rsDesc.DepthBiasClamp = .0f;                // ���� ���̾ Ŭ���� ��
    rsDesc.SlopeScaledDepthBias = .0f;          // ��絵�� ���� ���� ���̾ ��
    rsDesc.ScissorEnable = false;               // ���� �׽�Ʈ ��� ���� ( ������ ����� Ư�� ������ ������ �ϴµ� ��� )
    rsDesc.MultisampleEnable = false;           // ��Ƽ ���ø� ��� ���� ( �ȼ� ����� �ε巯���� �������Ѽ� �̹��� ǰ���� ��� )
    rsDesc.AntialiasedLineEnable = false;       // �� ��Ƽ������� ��� ���� ( ���� ��踦 �ε巴�� )
}

void States::CreateDepthStencilDesc() // ���̹��ۿ� ������
{
    Zero(dsDesc);

    dsDesc.DepthEnable = true;                                                      // ���� �׽�Ʈ ��� ����            
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;                             // ���� ������ ��� ��Ʈ�� ���� ���� �۾��� ���
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;                                       // ���� �׽�Ʈ �Լ��� LESS�� ����
                                                                                    
    dsDesc.StencilEnable = true;                                                    // ���ٽ� �׽�Ʈ ��� ����
    dsDesc.StencilReadMask = 0xFF;                                                  // ���ٽ� ���ۿ��� ���� �� �ִ� ��Ʈ ����ũ ����
    dsDesc.StencilWriteMask = 0xFF;                                                 // ���ٽ� ���ۿ��� ���� �ִ� ��Ʈ ����ũ ����
                                                                                    
                                                                                    
     dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;                        // ������� ���ٽ� ���� �۾� ����
     dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;                   // ������� ���ٽ� ���� ���� �۾� ����
     dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;                        // ������� ���ٽ� �н� �۾� ����
     dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;                        // ������� ���ٽ� �Լ� ����
                                                                                    

    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;                     // �ĸ� ���� ���ٽ� ���� �۾� ����
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;                          // �ĸ� ���� ���ٽ� ���� ���� �۾� ����
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;                          // �ĸ� ���� ���ٽ� �н� �۾� ����
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;                          // �ĸ� ���� ���ٽ� �Լ� ����
                                                                                    

}

void States::CreateSamplerDesc()
{
    Zero(spDesc);

    spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    spDesc.MaxAnisotropy = 1;
    spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    spDesc.MinLOD = FLT_MIN;
    spDesc.MaxLOD = FLT_MAX;
}

void States::CreateBlendDesc()
{
    Zero(blDesc);
                                                                                                    
    blDesc.AlphaToCoverageEnable = false;                                                           // Alpha To Coverage ��� ���� 
    blDesc.IndependentBlendEnable = false;                                                          // �������� ���� ��� ����
                                                                                                     
    blDesc.RenderTarget[0].BlendEnable = false;                                                     // ���� Ÿ�ٿ� ���� ���� ��� ����
    blDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;                                        // ������ ���� ���� ���� �μ��� ����
    blDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;                                   // �ҽ� ���� ���� ���� �μ��� ����
    blDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;                                            // ���� ���� ���� ������ ����
                                                                                                    

    blDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;                                        // ������ ���Ŀ� ���� ���� �μ��� ����
    blDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;                                        // �ҽ� ���Ŀ� ���� ���� �μ��� ����
    blDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;                                       // ���Ŀ� ���� ���� ������ ����
                                                                                                    
    blDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;                    // ��� ���� ä���� ���� Ÿ�ٿ� ���
}


#pragma endregion


/*
Depth
- 3D �׷��ȿ��� �ȼ��� ���̸� ��Ÿ���� ��
- ���� ���� ���۶�� 2D �̹��� ���ۿ� ����
- ���� ���۴� �� �ȼ��� ���� ���� ���� ����, �� ���� ������ �߿��� �׽�Ʈ �� ������Ʈ
- ���� ���۸� ����ϸ� 3D ��鿡�� ��ü���� �ùٸ� ������ ���������� �� �� ����

Depth Test
- �������� �ȼ��� ���� ���� �˻��� ������ ���θ� �����ϴµ� ���
- ���� �׽�Ʈ�� ����ڰ� ������ ���� �Լ��� ����Ͽ� �������� �ȼ��� ���� ���� ���� ��
- �����ϸ� ������, �����ϸ� �ɷ���

Stencil
- ���� ���ۿ� �Բ� ���Ǵ� 2D �̹��� ����
- �� �ȼ��� ���� ���ٽ� ���� �����ϸ�, �� ���� ������ �߿� �׽�Ʈ �� ������Ʈ
- �پ��� ������ ������� ���
    ex) �׸��� ����, Ŭ���� ���, ���� ������ ��

Stencil Test
- �������� �ȼ��� ���ٽ� ���� �˻��Ͽ� ������ ���θ� �����ϴµ� ���
- ����ڰ� ������ ���ٽ� �Լ��� ����Ͽ� �������� �ȼ��� ���ٽ� ���� ���ٽ� ������ ���� ��
- ���ٽ� �׽�Ʈ�� �����ϸ� �ȼ��� ������, �����ϸ� �ɷ���

Blending
- �������� �ȼ��� ������ �����ϴ� ��� �� �ϳ�
- �������� �ȼ��� ����� ���� Ÿ���� ���� ������ �����ϴ� ����

*/


/*
Alpha To coverage
- ��Ƽ���ø��� ��Ƽ���ϸ����(MSAA)�� ����� �� ���İ��� Ŀ������ ����ũ�� ��ȯ�Ͽ� ������ �����ϴ� ���
- ������ ��ü�� �����ڸ��� �� �ε巴�� ó�� �� �� ����

Independent Blend
- ���� ���� Ÿ�ٿ� ���� ���� Blend �̹�����

*/
