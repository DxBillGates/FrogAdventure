#pragma once
#include"Dx12_RootSignature.h"
#include"Dx12_Shader.h"
enum BlendMode
{
	BLENDMODE_ADD,
	BLENDMODE_SUB,
	BLENDMODE_INV,
	BLENDMODE_ALPHA
};
class Dx12_Pipeline
{
private:
	Dx12_RootSignature* mRootSignature;
	Dx12_Shader* mShaderResource;
	ID3D12PipelineState* mSolidPipeline;
	ID3D12PipelineState* mWirePipeline;
public:
	Dx12_Pipeline(ID3D12Device* device,Dx12_Shader* shader,Dx12_RootSignature* rootSignature, int inputLayoutCount = 1, bool writeDepthAlpha = false,BlendMode blendMode = BLENDMODE_ALPHA);
	~Dx12_Pipeline();
	void Set(ID3D12GraphicsCommandList* cmdList, D3D12_FILL_MODE mode);
private:
	void SetBlendMode(D3D12_RENDER_TARGET_BLEND_DESC* blendDesc, BlendMode mode);
};

