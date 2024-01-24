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
    
    //Line
    {
        if(input.uv.x < .01f || input.uv.x > .99f || input.uv.y < .01f || input.uv.y > .99f)
            return float4(1, 1, 1, 1);
        
        if(input.uv.x < 0.51f && input.uv.x > 0.49f)
            return float4(1, 1, 1, 1);
        
        if (input.uv.y < 0.51f && input.uv.y > 0.49f)
            return float4(1, 1, 1, 1);
    }
    
    {
        if (input.uv.x < .5f && input.uv.y < .5f) // �»��
        {
            color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.0, input.uv.y * 2.0));
            float3 greyScale = dot(color.rgb, float3(.299f, .587f, .114f));
            
            color = float4(greyScale, 1);
        }
        else if (input.uv.x > .5f && input.uv.y < .5f) // ����
        {
            // ���� �ϳ� ������ 
            // negative
            color = _sourceTex.Sample(_samp, float2((input.uv.x * 2.0) - 1, input.uv.y * 2.0));
            float3 value = 1 - abs(color.rgb);
            color = float4(value, color.a);
            
            
        }
        else if (input.uv.x < .5f && input.uv.y > .5f) // ���ϴ�
        {
            // ���� ���
            color = _sourceTex.Sample(_samp, float2((input.uv.x * 2.0), (input.uv.y * 2.0) - 1));
            
            
        }
        else if (input.uv.x > .5f && input.uv.y > .5f) // ���ϴ�
        {
            // ���� �ϳ��� �� ä��
            color = _sourceTex.Sample(_samp, float2((input.uv.x * 2.0) - 1, (input.uv.y * 2.0) - 1));
            color = float4(1, 1, 0, 0);
        }
    }
    
    return color;
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