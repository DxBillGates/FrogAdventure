#pragma once
#include"Dx12_Object.h"
#include"Dx12_ObjectData.h"
#include"Dx12_CBVSRVUAVHeap.h"
#include<vector>
class Dx12_Object3D : public Dx12_Object
{
	std::vector<VertexUV> vertices;
	std::vector<unsigned short> indices;
	CBData cbData;
	Transform transform;
public:
	Dx12_Object3D();
	~Dx12_Object3D();
	void Create(ID3D12Device* device, Dx12_CBVSRVUAVHeap* cbvSrvHeap);
	void Update(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3 & angle, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& projection, const DirectX::XMFLOAT4& color = { 0,0,0,1 }, const DirectX::XMFLOAT3& scale = { 1,1,1 });
	std::vector<VertexUV>* GetVertices();
	std::vector<unsigned short>* GetIndices();
};

