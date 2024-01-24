struct VertexInput
{
    float4 position : POSITION0;                // ���� ��ġ
    float2 uv : TEXCOORD0;                      // uv ��ǥ
};

struct PixelInput
{
    float4 position : SV_POSITION0;             // �ȼ� ��ġ
    float2 uv : TEXCOORD0;                       // uv ��ǥ
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

cbuffer ShadedBuffer : register(b0)
{
    int Selection;
}


PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.uv = input.uv;
    return output;
}

Texture2D _sourceTex : register(t0);            // �ؽ��� �����͸� ����
SamplerState _samp : register(s0);              // ���ø� �ϴ� ����� ����


float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    float4 resultColor = 0;
    
    
    // uv ��ǥ x 0 ~ 0.5 / 0.5 ~ 1
    // y 0 ~ 0.5 / 0.5 ~ 1 
    // 4�и����� ����� ���� ������ �ٸ� ���͸� ����
    // if �� ���
    if (Selection == 1)
        return color;
    else if (Selection == 2)
    {
        // AM
        float3 temp = dot(color.rgb, float3(.299f, .587f, .114f));
        resultColor = float4(temp, color.a);
    }
    else if (Selection == 3)
    {
        // Sepia
        float3 gray = float3(.393f, .769f, .189f);
        float3 temp = dot(color.rgb, gray);
        
        temp.r += 0.2;
        temp.g += 0.1;
        
        resultColor = float4(temp, color.a);
        
    }
    else if (Selection == 4)
    {
        // Negative
        float3 value = 1 - abs(color.rgb);
        resultColor = float4(value, color.a);
        
    }
    else if (Selection == 5) 
    {
        // Posterize
        float3 value = float3(2.0f, 2.0f, 2.0f);
        float3 posterize = round(color.rgb * value) / value;
        resultColor = float4(posterize, color.a);
        
    }

    return resultColor;
    
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

Sampler
- �ؽ��Ŀ��� �ȼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ�ó ���ø��� �ؽ�ó �̹����� ���� �ؼ� ���� ����ϴ� �۾�
    ( �ؼ� : �ؽ�ó�� �ȼ� �� )

*/