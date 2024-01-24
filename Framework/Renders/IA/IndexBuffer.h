// 정점의 인덱스를 저장하는 버퍼

#pragma once

class IndexBuffer
{
public:
	~IndexBuffer();

	
	void Create(const vector<uint>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride = 0;			// 정점 버퍼에서 한 정점의 크기를 나태는 값
	uint offset = 0;			// 버퍼에서 읽기 시작할 위치
	uint count = 0;				// 정점 버퍼에서 읽을 정점의 개수
private:


};