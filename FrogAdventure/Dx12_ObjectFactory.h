#pragma once
#include"Dx12_Object2D.h"
#include"Dx12_Object3D.h"
#include"Dx12_CBVSRVUAVHeap.h"
class Dx12_ObjectFactory
{
private:
	ID3D12Device* device;
	Dx12_CBVSRVUAVHeap* cbvHeap;
public:
	Dx12_ObjectFactory(ID3D12Device* pDevice,Dx12_CBVSRVUAVHeap* pCbvHeap);
	void CreatePlane(float width, float height, Dx12_Object2D* obj,bool centerIsLeftTop = true);
	void CreatePlane(float width, float height, Dx12_Object3D* obj,bool centerIsLeftTop = true);
	void CreateCube(float width, float height, float depth, Dx12_Object3D* obj);
};

