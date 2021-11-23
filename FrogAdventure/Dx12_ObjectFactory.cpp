#include "Dx12_ObjectFactory.h"

Dx12_ObjectFactory::Dx12_ObjectFactory(ID3D12Device* pDevice, Dx12_CBVSRVUAVHeap* pCbvHeap)
{
	device = pDevice;
	cbvHeap = pCbvHeap;
}

void Dx12_ObjectFactory::CreatePlane(float width, float height, Dx12_Object2D * obj, bool centerIsLeftTop)
{
	int verticesNum = 4;
	std::vector<VertexUV>* pVertices = obj->GetVertices();
	std::vector<unsigned short>* pIndices = obj->GetIndices();
	if (centerIsLeftTop)
	{
		(*pVertices) =
		{
			{{    0,     0,0},{0,0}},
			{{width,     0,0},{1,0}},
			{{width,height,0},{1,1}},
			{{    0,height,0},{0,1}},
		};
	}
	else
	{
		(*pVertices) = 
		{
			{{-width / 2,-height / 2,0},{0,0}},
			{{width / 2,-height / 2,0},{1,0}},
			{{width / 2,height / 2,0},{1,1}},
			{{-width / 2,height / 2,0},{0,1}},
		};
	}
	(*pIndices) =
	{
		0,1,2,0,2,3,
	};
	pVertices = nullptr;
	pIndices = nullptr;
	obj->Create(device, cbvHeap);
}

void Dx12_ObjectFactory::CreatePlane(float width, float height, Dx12_Object3D * obj, bool centerIsLeftTop)
{
	int verticesNum = 4;
	std::vector<VertexUV>* pVertices = obj->GetVertices();
	std::vector<unsigned short>* pIndices = obj->GetIndices();
	if (centerIsLeftTop)
	{
		(*pVertices) =
		{
			{{    0,     0,0},{0,0}},
			{{width,     0,0},{1,0}},
			{{width,-height,0},{1,1}},
			{{    0,-height,0},{0,1}},
		};
	}
	else
	{
		(*pVertices) =
		{
			{{-width / 2,height / 2,0},{0,0}},
			{{width / 2,height / 2,0},{1,0}},
			{{width / 2,-height / 2,0},{1,1}},
			{{-width / 2,-height / 2,0},{0,1}},
		};
	}
	(*pIndices) =
	{
		0,1,2,0,2,3,
	};
	pVertices = nullptr;
	pIndices = nullptr;
	obj->Create(device, cbvHeap);
}

void Dx12_ObjectFactory::CreateCube(float width, float height, float depth, Dx12_Object3D * obj)
{
	int verticesNum = 24;
	std::vector<VertexUV>* pVertices = obj->GetVertices();
	std::vector<unsigned short>* pIndices = obj->GetIndices();
	(*pVertices) =
	{
		{{-width / 2, height / 2,-depth / 2},{0,0}},{{ width / 2, height / 2,-depth / 2},{1,0}},{{ width / 2,-height / 2,-depth / 2},{1,1}},{{-width / 2,-height / 2,-depth / 2},{0,1}},
		{{ width / 2, height / 2,-depth / 2},{0,0}},{{ width / 2, height / 2, depth / 2},{1,0}},{{ width / 2,-height / 2, depth / 2},{1,1}},{{ width / 2,-height / 2,-depth / 2},{0,1}},
		{{ width / 2, height / 2, depth / 2},{0,0}},{{-width / 2, height / 2, depth / 2},{1,0}},{{-width / 2,-height / 2, depth / 2},{1,1}},{{ width / 2,-height / 2, depth / 2},{0,1}},
		{{-width / 2, height / 2, depth / 2},{0,0}},{{-width / 2, height / 2,-depth / 2},{1,0}},{{-width / 2,-height / 2,-depth / 2},{1,1}},{{-width / 2,-height / 2, depth / 2},{0,1}},
		{{-width / 2, height / 2, depth / 2},{0,0}},{{ width / 2, height / 2, depth / 2},{1,0}},{{ width / 2, height / 2,-depth / 2},{1,1}},{{-width / 2, height / 2,-depth / 2},{0,1}},
		{{ width / 2,-height / 2,-depth / 2},{0,0}},{{-width / 2,-height / 2,-depth / 2},{1,0}},{{-width / 2,-height / 2, depth / 2},{1,1}},{{ width / 2,-height / 2, depth / 2},{0,1}},
	};
	(*pIndices) =
	{
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23,
	};
	pVertices = nullptr;
	pIndices = nullptr;
	obj->Create(device, cbvHeap);
}
