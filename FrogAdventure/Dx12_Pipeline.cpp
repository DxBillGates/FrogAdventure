#include "Dx12_Pipeline.h"
#include "COMRelease.h"

Dx12_Pipeline::Dx12_Pipeline(ID3D12Device * device, Dx12_Shader* shader, Dx12_RootSignature* rootSignature, int inputLayoutCount, bool writeDepthAlpha, BlendMode blendMode)
{
	HRESULT result;
	mRootSignature = rootSignature;
	mShaderResource = shader;
	D3D12_RENDER_TARGET_BLEND_DESC blendDesc = {};
	SetBlendMode(&blendDesc, blendMode);
	D3D12_INPUT_ELEMENT_DESC* inputLayout = new D3D12_INPUT_ELEMENT_DESC[inputLayoutCount];
	inputLayout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	if (inputLayoutCount == 2)
	{
		inputLayout[1] = { "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 };
	}
	else if (inputLayoutCount == 3)
	{
		inputLayout[1] = { "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 };
		inputLayout[2] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	}
	//PipelineStateÇÃê›íËÇ∆ê∂ê¨
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.VS.BytecodeLength = mShaderResource->GetVsBlob()->GetBufferSize();
	psoDesc.VS.pShaderBytecode = mShaderResource->GetVsBlob()->GetBufferPointer();
	psoDesc.PS.BytecodeLength = mShaderResource->GetPsBlob()->GetBufferSize();
	psoDesc.PS.pShaderBytecode = mShaderResource->GetPsBlob()->GetBufferPointer();
	psoDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	psoDesc.RasterizerState.DepthClipEnable = true;
	psoDesc.DepthStencilState.DepthEnable = true;
	psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	psoDesc.BlendState.RenderTarget[0] = blendDesc;
	if (writeDepthAlpha)
	{
		psoDesc.BlendState.AlphaToCoverageEnable = true;
	}
	else
	{
		psoDesc.BlendState.AlphaToCoverageEnable = false;
	}
	psoDesc.InputLayout.pInputElementDescs = inputLayout;
	psoDesc.InputLayout.NumElements = inputLayoutCount;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.pRootSignature = mRootSignature->Get();
	result = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mSolidPipeline));
	psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	result = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mWirePipeline));

	delete[] inputLayout;
}

Dx12_Pipeline::~Dx12_Pipeline()
{
	delete mRootSignature;
	delete mShaderResource;
	COM_RELEASE(mSolidPipeline);
	COM_RELEASE(mWirePipeline);
}

void Dx12_Pipeline::Set(ID3D12GraphicsCommandList * cmdList, D3D12_FILL_MODE mode)
{
	if (mode == D3D12_FILL_MODE_SOLID)cmdList->SetPipelineState(mSolidPipeline);
	else cmdList->SetPipelineState(mWirePipeline);
	cmdList->SetGraphicsRootSignature(mRootSignature->Get());
}

void Dx12_Pipeline::SetBlendMode(D3D12_RENDER_TARGET_BLEND_DESC * blendDesc, BlendMode mode)
{
	(*blendDesc).RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	(*blendDesc).BlendEnable = true;
	(*blendDesc).BlendOpAlpha = D3D12_BLEND_OP_ADD;
	(*blendDesc).SrcBlendAlpha = D3D12_BLEND_ONE;
	(*blendDesc).DestBlendAlpha = D3D12_BLEND_ZERO;
	switch (mode)
	{
	case BLENDMODE_ADD:
		/* â¡éZçáê¨ */
		(*blendDesc).BlendOp = D3D12_BLEND_OP_ADD;
		(*blendDesc).SrcBlend = D3D12_BLEND_ONE;
		(*blendDesc).DestBlend = D3D12_BLEND_ONE;
		break;
	case BLENDMODE_SUB:
		/* å∏éZçáê¨ */
		(*blendDesc).BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
		(*blendDesc).SrcBlend = D3D12_BLEND_ONE;
		(*blendDesc).DestBlend = D3D12_BLEND_ONE;
		break;
	case BLENDMODE_INV:
		/* êFîΩì] */
		(*blendDesc).BlendOp = D3D12_BLEND_OP_ADD;
		(*blendDesc).SrcBlend = D3D12_BLEND_INV_DEST_COLOR;
		(*blendDesc).DestBlend = D3D12_BLEND_ZERO;
		break;
	case BLENDMODE_ALPHA:
		/* îºìßñæ */
		(*blendDesc).BlendOp = D3D12_BLEND_OP_ADD;
		(*blendDesc).SrcBlend = D3D12_BLEND_SRC_ALPHA;
		(*blendDesc).DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		break;
	}
}
