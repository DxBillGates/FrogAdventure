#pragma once
#include<DirectXMath.h>
struct Vertex
{
	DirectX::XMFLOAT3 pos;
};

struct VertexUV
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
};

struct VertexNormal
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 normal;
};

struct CBData
{
	DirectX::XMFLOAT4 color;
	DirectX::XMMATRIX matrix;
};

struct Transform
{
	DirectX::XMMATRIX translation;
	DirectX::XMMATRIX rotation;
	DirectX::XMMATRIX scale;
};