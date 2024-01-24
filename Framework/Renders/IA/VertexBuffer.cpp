#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	// IA �� ���� ���۸� �Է��ϴ� �Լ�
	DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}

// IASetVertexBuffers �Ű�����

/*
StartSlot			: �Է� ���� �ε���
NumBuffers			: ���� ����
ppVertexBuffers		: ���۸� ����Ű�� ������ ����
pStrides			: ����ü ũ��
pOffsets			: ������ ������ �� ( Ư�� ��ġ���� �о���̰��� �� �� ��� )

*/