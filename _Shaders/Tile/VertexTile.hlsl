struct VertexInput
{
    float4 position : POSITION0;                
    float2 uv : TEXCOORD0;
    float2 uv2 : TEXCOORD1;
    float4 color : COLOR0;
    uint index : INDEX0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;             
    float2 uv : TEXCOORD0;
    float2 uv2 : TEXCOORD1;
    float4 color : COLOR0;
    uint index : INDEX0;
};

cbuffer WorldBuffer : register(b0)            
{
    matrix _world;
}

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
}

cbuffer IndexNumBuffer : register(b0)
{
    uint _index;
}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.uv = input.uv;
    output.uv2 = input.uv2 ;
    output.color = input.color ;
    output.index = input.index ;
   

    return output;
}

Texture2D _sourceTex : register(t0);           
SamplerState _samp : register(s0);              


float4 PS(PixelInput input) : SV_Target
{
    float4 color = 0;

    if (input.uv.x > 0.0f || input.uv.y > 0.0f)
        color = _sourceTex.Sample(_samp, input.uv);
    else
        color = input.color;

    if (input.index == _index)
    {
        if (input.uv2.x < 0.05f || input.uv2.x > 0.95f || input.uv2.y < 0.05f || input.uv2.y > 0.95f)
            color = float4 (1, 0, 0, 1);
    }
    
    return color;
}

/*
Sementic : 세멘틱
- HLSL 셰이더에서 데이터의 의미를 지정하는데 사용
- 셰이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리할 수 있도록 해줌
- 변수 이름 뒤에 ':' 기호와 함께 지정
- 시스템 값 세멘틱은 'SV_' 접두사로 시작하며 Direct3D 에서 정의된 특별한 의미를 가짐
- 시스템 값 세멘틱은 셰이더 스테이지 간에 데이터를 전달하는데 사용

slot
- GPU 에서 사용하는 상수 버퍼, 텍스쳐, 샘플러 등의 자원들을 식별하는 인덱스
- 각 슬롯은 고유한 번호를 가지며, 해당 자원의 유형과 역할에 따라 다르게 할당됨
- registrer 라는 키워드를 사용하여 지정
- 각 자원이 어떤 슬롯에 할당될 것인지 명시적으로 지정할 수 있음
-주요슬롯
    1) 상수버퍼 슬롯
    - 상수 데이터를 저장하는데 사용되며, VS와 PS에서 공유할수 있다
    - 상수 버퍼 슬롯은 register(b#) 을 사용하여 지정

    2) 텍스쳐 슬롯
    - 이미지 데이터를 저장하는데 사용
    - 텍스쳐 버퍼 슬롯은 register(t#) 을 사용하여 지정

    3) 샘플러 슬롯
    - 텍스처를 샘플링 하는데 사용
    - 샘플러 슬롯은  register(S#)을 사용하여 지정

cbuffer = Constant Buffer : 상수 버퍼
- 셰이더에서 사용하는 전역 변수를 저장하는데 사용
- 각 상수 버퍼 레지스터에는 한개의 상수 버퍼만 할당될수 있음
- 상수 버퍼 내부에는 여러개의 변수를 전언할 수 있음

Sampler
- 텍스쳐에서 픽셀 값을 가져오는 방법을 정의하는 객체
- 텍스처 샘플링은 텍스처 이미지에 대해 텍셀 값을 계산하는 작업
    ( 텍셀 : 텍스처의 픽셀 값 )

*/