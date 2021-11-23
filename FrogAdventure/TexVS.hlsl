#include"TexShader.hlsli"
TexOutput main(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	TexOutput output;
	output.svpos = mul(mat, pos);
	output.uv = uv;
	return output;
}