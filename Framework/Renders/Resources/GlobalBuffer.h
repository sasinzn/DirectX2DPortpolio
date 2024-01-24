// WVP ��� ����
#pragma once

#include "Framework.h"

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		// ��� �ʱ�ȭ
		D3DXMatrixIdentity(&data.world);

	}
	
	void SetWorld(Matrix world)
	{
		// ��� ��ġ
		D3DXMatrixTranspose(&data.world, &world);
	}
	struct Data
	{
		Matrix world;
	};

private:
	Data data;

};

class VPBuffer : public ShaderBuffer
{
public:
	VPBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		// ��� �ʱ�ȭ
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.Projection);

	}

	void SetView(Matrix view)
	{
		// ��� ��ġ
		D3DXMatrixTranspose(&data.view, &view);
	}
	void SetProj(Matrix Projection)
	{
		// ��� ��ġ
		D3DXMatrixTranspose(&data.Projection, &Projection);
	}

private:
	struct Data
	{
		Matrix view;
		Matrix Projection;
	};
private:
	Data data;
};


/*
WVP : World, View, Projection

- 3D ���� 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ������ �ϳ�

1. World
- ���� ������ ���ÿ��� ���� ��ǥ�� ��ȯ�ϴ� ���� �ǹ�
- ���� ��ġ, ȸ�� �� ũ�⸦ ����

2. View
- ī�޶��� ��ġ, ���� �� �þ߸� ��Ÿ���� ���
- ���� ��ǥ�迡�� ī�޶� �ٶ󺸴� ������ ��Ÿ��
- ī�޶��� ��ġ�� ������ ����

3. Projection
- 3D ������ 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �ǹ�
- �þ߰�, ��Ⱦ��, ũ���� ���(Clipping Plans)���� ����Ͽ� ����


*/