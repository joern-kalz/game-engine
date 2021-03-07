#include "TexturedTriangleHeader.hlsli"

float4 main(PixelShaderInput input) : SV_TARGET
{
	return diffuseTexture.Sample(linearSampler, input.textureUV);
}