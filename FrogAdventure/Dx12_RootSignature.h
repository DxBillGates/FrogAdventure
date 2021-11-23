#pragma once
#include<d3d12.h>
class Dx12_RootSignature
{
private:
	ID3D12RootSignature* mRootSignature;
	ID3DBlob* mRootBlob;
public:
	Dx12_RootSignature(ID3D12Device* device, int rootParamCount = 1);
	~Dx12_RootSignature();
	ID3D12RootSignature* Get();
};

