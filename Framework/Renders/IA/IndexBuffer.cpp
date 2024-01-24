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

	//desc ����
	{
		desc.Usage = usage;								
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;		
		desc.ByteWidth = stride * count;				

		switch (usage)
		{
			// GPU ������ ���� ������ ����
		case D3D11_USAGE_DEFAULT:
			// GPU ������ ���� �����ϰ�, �����Ҽ� ���� ����
		case D3D11_USAGE_IMMUTABLE:
			break;

			// CPU ���� ���� �����ϰ�, �������� ���� ������ ����
		case D3D11_USAGE_DYNAMIC:
			desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
			break;
			// CPU ���� ���� ����, GPU ���� ����� �� �ִ� ���·� ��ȯ ������ ����
		case D3D11_USAGE_STAGING:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;


		}

	}

	// ����
	{
		D3D11_SUBRESOURCE_DATA subData;									
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));			

		subData.pSysMem = indices.data();								

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	
		CHECK(hr); // ���н� ��

	}


}

void IndexBuffer::SetIA()
{
	// IA �� ���� ���۸� �Է��ϴ� �Լ�
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
