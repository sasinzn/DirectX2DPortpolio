#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
{
	if (!descs || !count || !blob)
		CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,									// InputLayout을 구성하는 각 선언들의 배열
		count,									// InputLayout을 구성하는 선언의 수
		blob->GetBufferPointer(),				// 셰이더 코드를 포함하는 블롭에 대한 포인터
		blob->GetBufferSize(),					// 셰이더 코드 블롭의 크기
		&inputLayout							// 반환되는 포인터 변수
	);
	CHECK(hr);
	
	// blob = 메모리 블럭
}

void InputLayout::SetIA()
{
	// 입력 어셈블러 스테이지에서 사용할 인풋 레이아웃 설정
	DC->IASetInputLayout(inputLayout);
}
