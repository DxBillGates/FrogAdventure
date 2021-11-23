#include "Dx12_RootSignature.h"
#include "COMRelease.h"

Dx12_RootSignature::Dx12_RootSignature(ID3D12Device * device, int rootParamCount)
{
	HRESULT result;
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER* rootParam = new D3D12_ROOT_PARAMETER[rootParamCount];
	D3D12_DESCRIPTOR_RANGE cbvRange = {};
	cbvRange.NumDescriptors = 1;
	cbvRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	cbvRange.BaseShaderRegister = 0;
	cbvRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	rootParam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam[0].DescriptorTable.pDescriptorRanges = &cbvRange;
	rootParam[0].DescriptorTable.NumDescriptorRanges = 1;
	rootParam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	if (rootParamCount >= 2)
	{
		//サンプラーの設定
		D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		samplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		//レンジの設定
		D3D12_DESCRIPTOR_RANGE srvRange = {};
		srvRange.NumDescriptors = 1;
		srvRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		srvRange.BaseShaderRegister = 0;
		srvRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		rootParam[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam[1].DescriptorTable.pDescriptorRanges = &srvRange;
		rootParam[1].DescriptorTable.NumDescriptorRanges = 1;
		rootParam[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootSignatureDesc.pStaticSamplers = &samplerDesc;
		rootSignatureDesc.NumStaticSamplers = 1;
	}
	//ルートシグネチャの設定と生成
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParam;
	rootSignatureDesc.NumParameters = rootParamCount;
	ID3DBlob* errorBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &mRootBlob, &errorBlob);
	result = device->CreateRootSignature(0, mRootBlob->GetBufferPointer(), mRootBlob->GetBufferSize(), IID_PPV_ARGS(&mRootSignature));
	delete[] rootParam;
}

Dx12_RootSignature::~Dx12_RootSignature()
{
	COM_RELEASE(mRootSignature);
	COM_RELEASE(mRootBlob);
}

ID3D12RootSignature * Dx12_RootSignature::Get()
{
	return mRootSignature;
}
