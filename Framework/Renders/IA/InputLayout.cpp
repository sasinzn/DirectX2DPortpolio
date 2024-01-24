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
		descs,									// InputLayout�� �����ϴ� �� ������� �迭
		count,									// InputLayout�� �����ϴ� ������ ��
		blob->GetBufferPointer(),				// ���̴� �ڵ带 �����ϴ� ��ӿ� ���� ������
		blob->GetBufferSize(),					// ���̴� �ڵ� ����� ũ��
		&inputLayout							// ��ȯ�Ǵ� ������ ����
	);
	CHECK(hr);
	
	// blob = �޸� ��
}

void InputLayout::SetIA()
{
	// �Է� ����� ������������ ����� ��ǲ ���̾ƿ� ����
	DC->IASetInputLayout(inputLayout);
}
