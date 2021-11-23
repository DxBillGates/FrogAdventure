#pragma once
#include"Dx12_Object.h"
#include"Dx12_ObjectData.h"
#include"Dx12_CBVSRVUAVHeap.h"
#include"Dx12_Texture2D.h"
#include<vector>
#include<d3d12.h>
class Dx12_Object2D : public Dx12_Object
{
private:
	std::vector<VertexUV> vertices;
	std::vector<unsigned short> indices;
	CBData cbData;
	Transform transform;
public:
	Dx12_Object2D();
	~Dx12_Object2D();
	void Create(ID3D12Device* device, Dx12_CBVSRVUAVHeap* cbvSrvHeap);
	void Update(const DirectX::XMFLOAT3& pos, const DirectX::XMMATRIX& projection);
	std::vector<VertexUV>* GetVertices();
	std::vector<unsigned short>* GetIndices();
};