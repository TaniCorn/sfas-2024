cbuffer cbChangedPerFrame : register(b0)
{
    matrix mvp;

};
cbuffer cbFade : register(b1)
{
    float4 fadeColor;
};

Texture2D colorMap : register(t0);
SamplerState colorSample : register(s0);

struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input) 0;
    vsOut.pos = mul(vertex.pos, mvp);
    vsOut.tex0 = vertex.tex0;
    return vsOut;
}

float4 PS_Main(PS_Input frag) : SV_TARGET
{
    float4 finalColor = colorMap.Sample(colorSample, -frag.tex0);
    float4 fadeColorChange = float4(fadeColor.xyz, fadeColor.w);
    
    finalColor *= fadeColorChange;
    return finalColor;
}