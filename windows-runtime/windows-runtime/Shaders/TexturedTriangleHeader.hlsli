Texture2D diffuseTexture : register(t0);
SamplerState linearSampler : register(s0);

struct VertextShaderInput
{
    float4 position : POSITION;
    float2 textureUV : TEXCOORD0;
};

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float2 textureUV : TEXCOORD0;
};
