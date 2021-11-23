#include"BasicShader.hlsli"
float4 main( float4 pos : POSITION ) : SV_POSITION
{
	float4 svpos = mul(mat,pos);
	return svpos;
}