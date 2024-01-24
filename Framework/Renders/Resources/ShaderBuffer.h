// GPU에서 사용하는 데이터를 CPU 에서 생성하고 수정할 수 있도록 버퍼를 제공하는 역할
#pragma once

#include "Framework.h"

class ShaderBuffer
{
public:
	// Vertex Shader Buffer
	void SetVSBuffer(uint slot)
	{
		MapData();
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	// Pixel Shader Buffer
	void SetPSBuffer(uint slot)
	{
		MapData();
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	ShaderBuffer(void* data, uint dataSize)
		:data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;					// 버퍼의 사용 방식
		desc.ByteWidth = dataSize;							// 버퍼의 크기
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// 바인딩할 대상
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPU에서 버퍼에 접근하는 방식 설정

		// 버퍼 생성
		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);

	}

private:
	void MapData()
	{
		D3D11_MAPPED_SUBRESOURCE subResource;		//데이터 매핑을 위한 구조체
		HRESULT hr = DC->Map
		(
			buffer,									// 매핑할 그래픽 리소스
			0,										// 매핑할 시작 바이트 위치
			D3D11_MAP_WRITE_DISCARD,				// 매핑 방법
			0,										// 매핑을 원하는 하위 리소스
			&subResource							// 매핑된 메모리 주소를 전달

		);
		CHECK(hr);

		memcpy(subResource.pData, data, dataSize);
		DC->Unmap(buffer, 0);


	}


private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr;
	uint dataSize = 0;
};
