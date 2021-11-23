#include "Dx12_Object2D.h"
#include "COMRelease.h"

Dx12_Object2D::Dx12_Object2D()
{
}

Dx12_Object2D::~Dx12_Object2D()
{
	COM_RELEASE(vBuff);
	COM_RELEASE(iBuff);
	COM_RELEASE(cBuff);
}

void Dx12_Object2D::Create(ID3D12Device * device, Dx12_CBVSRVUAVHeap* cbvSrvHeap)
{
	cbvNumber = cbvSrvHeap->GetNextCbvDescriptorNumber();
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resDesc.Width = sizeof(VertexUV)*vertices.size();
	device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vBuff));
	vbView.BufferLocation = vBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = (UINT)resDesc.Width;
	vbView.StrideInBytes = sizeof(VertexUV);
	resDesc.Width = sizeof(unsigned short)*indices.size();
	device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&iBuff));
	ibView.BufferLocation = iBuff->GetGPUVirtualAddress();
	ibView.SizeInBytes = (UINT)resDesc.Width;
	ibView.Format = DXGI_FORMAT_R16_UINT;
	resDesc.Width = (sizeof(CBData) + 0xff)&~0xff;
	device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&cBuff));
	cbvSrvHeap->CreateCBV(cBuff);
	VertexUV* vbMap = nullptr;
	unsigned short* ibMap = nullptr;
	vBuff->Map(0, nullptr, (void**)&vbMap);
	iBuff->Map(0, nullptr, (void**)&ibMap);
	for (int i = 0; i < (int)vertices.size(); ++i)
	{
		vbMap[i] = vertices[i];
	}
	for (int i = 0; i < (int)indices.size(); ++i)
	{
		ibMap[i] = indices[i];
	}
	vBuff->Unmap(0, nullptr);
	iBuff->Unmap(0, nullptr);
	indexCount = (int)indices.size();
}

void Dx12_Object2D::Update(const DirectX::XMFLOAT3 & pos, const DirectX::XMMATRIX & projection)
{
	static DirectX::XMFLOAT3 oldPos = {-100000,-100000,-100000};
	if (oldPos.x == pos.x && oldPos.y == pos.y && oldPos.z == pos.z)
	{
		return;
	}
	cbData.matrix = DirectX::XMMatrixIdentity();
	transform.translation = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cbData.matrix *= transform.translation;
	cbData.color = { 0,0,0,1 };
	CBData* cbMap = nullptr;
	cBuff->Map(0, nullptr, (void**)&cbMap);
	cbMap->color = cbData.color;
	cbMap->matrix = cbData.matrix * projection;
	cBuff->Unmap(0, nullptr);
}

std::vector<VertexUV>* Dx12_Object2D::GetVertices()
{
	return &vertices;
}

std::vector<unsigned short>* Dx12_Object2D::GetIndices()
{
	return &indices;
}
