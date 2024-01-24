#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<uint>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(uint);								
	count = indices.size();								

	D3D11_BUFFER_DESC desc;								
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));		

	//desc 설정
	{
		desc.Usage = usage;								
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;		
		desc.ByteWidth = stride * count;				

		switch (usage)
		{
			// GPU 에서만 접근 가능한 버퍼
		case D3D11_USAGE_DEFAULT:
			// GPU 에서만 접근 가능하고, 수정할수 없는 버퍼
		case D3D11_USAGE_IMMUTABLE:
			break;

			// CPU 에서 접근 가능하고, 동적으로 수정 가능한 버퍼
		case D3D11_USAGE_DYNAMIC:
			desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
			break;
			// CPU 에서 접근 가능, GPU 에서 사용할 수 있는 형태로 변환 가능한 버퍼
		case D3D11_USAGE_STAGING:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;


		}

	}

	// 생성
	{
		D3D11_SUBRESOURCE_DATA subData;									
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));			

		subData.pSysMem = indices.data();								

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	
		CHECK(hr); // 실패시 펑

	}


}

void IndexBuffer::SetIA()
{
	// IA 에 정점 버퍼를 입력하는 함수
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
