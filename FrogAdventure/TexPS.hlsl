#include"TexShader.hlsli"
Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
float4 main(TexOutput input) : SV_TARGET
{
	float4 returnColor = tex.Sample(smp,input.uv);
	return returnColor;
//return float4(input.uv,1,1);
}