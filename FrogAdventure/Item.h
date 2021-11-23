#pragma once
#include "GameObject.h"
class Item : public GameObject
{
public:
	Item();
	virtual ~Item();
	virtual void LoadAsset(Dx12_Device* device, Dx12_CBVSRVUAVHeap* heap) = 0;
	virtual void Initialize() = 0;
	virtual void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pers, const DirectX::XMMATRIX& ortho) = 0;
	virtual void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap) = 0;
};

