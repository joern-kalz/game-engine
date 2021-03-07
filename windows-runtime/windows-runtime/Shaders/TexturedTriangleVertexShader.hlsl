#include "TexturedTriangleHeader.hlsli"

PixelShaderInput main(VertextShaderInput input)
{
	PixelShaderInput output = (PixelShaderInput)0;
	output.position = input.position;
	output.textureUV = input.textureUV;
	return output;
}

