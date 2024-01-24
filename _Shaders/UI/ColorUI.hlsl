struct VertexInput
{
    float4 position : POSITION0;                // ���� ��ġ
    float4 color : COLOR0;                      // ���� ����
};

struct PixelInput
{
    float4 position : SV_POSITION0;             // �ȼ� ��ġ
    float4 color : COLOR0;                      // �ȼ� ����
};

cbuffer WorldBuffer : register(b0)              // ���� ũ�� ( 0 ~ 127 )
{
    matrix _world;
}

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.color = input.color;
    return output;
}

float4 PS(PixelInput input) : SV_Target
{
    return input.color;
}

/*
Sementic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Direct3D ���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
- GPU ���� ����ϴ� ��� ����, �ؽ���, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- registrer ��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����
-�ֿ佽��
    1) ������� ����
    - ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� �����Ҽ� �ִ�
    - ��� ���� ������ register(b#) �� ����Ͽ� ����

    2) �ؽ��� ����
    - �̹��� �����͸� �����ϴµ� ���
    - �ؽ��� ���� ������ register(t#) �� ����Ͽ� ����

    3) ���÷� ����
    - �ؽ�ó�� ���ø� �ϴµ� ���
    - ���÷� ������  register(S#)�� ����Ͽ� ����

cbuffer = Constant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �Ѱ��� ��� ���۸� �Ҵ�ɼ� ����
- ��� ���� ���ο��� �������� ������ ������ �� ����


*/