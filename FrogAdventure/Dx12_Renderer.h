#pragma once
#include"Dx12_Pipeline.h"
#include"Dx12_Object.h"
#include"Dx12_Texture2D.h"
#include"Dx12_CBVSRVUAVHeap.h"
class Dx12_Renderer
{
private:
	Dx12_Pipeline* texPipeline;
	Dx12_Pipeline* basicPipeline;
	ID3D12GraphicsCommandList* pCmdList;
public:
	Dx12_Renderer(Dx12_Pipeline* texPSO, Dx12_Pipeline* basicPSO, ID3D12GraphicsCommandList* cmdList);
	~Dx12_Renderer();
	void Render(Dx12_Object* obj,Dx12_Texture2D* texture,Dx12_CBVSRVUAVHeap* heap);
};

