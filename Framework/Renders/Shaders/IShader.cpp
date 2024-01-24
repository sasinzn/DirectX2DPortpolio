#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
	ID3DBlob* error = nullptr;									// �����Ϸ� ���� �޼����� ������ Blob �����͸� nullptr�� �ʱ�ȭ
	HRESULT hr = D3DCompileFromFile								// ���̴� ������ ������ �ϰ�, ����� Blob �����ͷ� ���޹���
	(
		path.c_str(),											// �������� ���̴� ���� ��� 
		nullptr,												// ���̴� ������ ����� ��Ÿ���� ������
		nullptr,												// Include �������̽��� ������ Ŭ������ ����� ���̴� ���Ͽ��� �ٸ� ������ Include �Ҷ� ����Ҽ� �ִ� ���ؽ�Ʈ
		entryName.c_str(),										// �������� ���̴� ���Ͽ��� ���� ���������� ����� �Լ� �̸�
		profile.c_str(),										// �������� ���̴� ���Ͽ��� ����� ������ �̸�
		D3DCOMPILE_ENABLE_STRICTNESS,							// ������ ������ �ɼ� / ��� �޼����� ����1�� ����
		0,														// ����� ������ ���Ե� ������ ����� �����ϱ� ���� �ɼ�
		blob,													// ������ ����� ������ Blob ������ �ּҰ�
		&error													// �����Ϸ� ���� �޼����� ������ Blob ������ �ּҰ�
	);															 
	CheckShaderError(hr, error);								// �����Ϸ� ������ �߻��ϸ� ���� �޼��� ���
	SAFE_RELEASE(error);										// Blob ������ ����
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
	if (FAILED(hr))
	{
		if (error)
		{
			string str = (const char*)error->GetBufferPointer();
			MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
		}
		CHECK(false);

	}

}


/*
ID3DBlob
- �޸𸮿� �Ҵ�� ������ ���
- ��ǥ������ ���̴� �ڵ峪 ���� ������ ��
- �޸𸮿� �Ҵ�� ������ ����� �����ϰ� ������ ������ �� ����
*/