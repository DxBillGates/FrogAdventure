cbuffer cBuff0 : register(b0)
{
	float4 color;
	matrix mat;
}
struct TexOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};