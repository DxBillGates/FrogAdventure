#include "Dx12_Renderer.h"

Dx12_Renderer::Dx12_Renderer(Dx12_Pipeline * texPSO, Dx12_Pipeline * basicPSO, ID3D12GraphicsCommandList* cmdList)
{
	texPipeline = texPSO;
	basicPipeline = basicPSO;
	pCmdList = cmdList;
}

Dx12_Renderer::~Dx12_Renderer()
{
	delete texPipeline;
	delete basicPipeline;
}

void Dx12_Renderer::Render(Dx12_Object * obj, Dx12_Texture2D * texture,Dx12_CBVSRVUAVHeap* heap)
{
	if (texture == nullptr)
	{
		basicPipeline->Set(pCmdList,D3D12_FILL_MODE_SOLID);
		heap->Set(pCmdList);
	}
	else
	{
		texPipeline->Set(pCmdList, D3D12_FILL_MODE_SOLID);
		heap->Set(pCmdList);
		pCmdList->SetGraphicsRootDescriptorTable(1, heap->GetSRVHandleForGPU(texture->GetSRVNumber()));
	}
	pCmdList->SetGraphicsRootDescriptorTable(0, heap->GetCBVHandleForGPU(obj->GetCBVNumber()));
	pCmdList->IASetIndexBuffer(obj->GetIBuffView());
	pCmdList->IASetVertexBuffers(0, 1, obj->GetVBuffView());
	pCmdList->DrawIndexedInstanced(obj->GetIndexCount(), 1, 0, 0, 0);

}
