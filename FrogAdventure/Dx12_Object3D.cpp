#include "Dx12_Object3D.h"
#include "COMRelease.h"

Dx12_Object3D::Dx12_Object3D()
{
}

Dx12_Object3D::~Dx12_Object3D()
{

	COM_RELEASE(vBuff);
	COM_RELEASE(iBuff);
	COM_RELEASE(cBuff);
}

void Dx12_Object3D::Create(ID3D12Device * device, Dx12_CBVSRVUAVHeap * cbvSrvHeap)
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

void Dx12_Object3D::Update(const DirectX::XMFLOAT3 & pos, const DirectX::XMFLOAT3 & angle, const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & projection, const DirectX::XMFLOAT4& color, const DirectX::XMFLOAT3& scale)
{
	cbData.matrix = DirectX::XMMatrixIdentity();
	transform.scale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	transform.rotation = DirectX::XMMatrixIdentity();
	transform.rotation *= DirectX::XMMatrixRotationZ(angle.z);
	transform.rotation *= DirectX::XMMatrixRotationX(angle.x);
	transform.rotation *= DirectX::XMMatrixRotationY(angle.y);
	transform.translation = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cbData.matrix *= transform.scale;
	cbData.matrix *= transform.rotation;
	cbData.matrix *= transform.translation;
	cbData.color = color;
	CBData* cbMap = nullptr;
	cBuff->Map(0, nullptr, (void**)&cbMap);
	cbMap->color = cbData.color;
	cbMap->matrix = cbData.matrix * view * projection;
	cBuff->Unmap(0, nullptr);
}

std::vector<VertexUV>* Dx12_Object3D::GetVertices()
{
	return &vertices;
}

std::vector<unsigned short>* Dx12_Object3D::GetIndices()
{
	return &indices;
}
