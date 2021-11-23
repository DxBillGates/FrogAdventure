#pragma once
#include"Dx12_Device.h"
#include"Dx12_CBVSRVUAVHeap.h"
#include"Dx12_ObjectFactory.h"
#include"Dx12_Renderer.h"
class GameObject
{
public:
	GameObject();
	GameObject(Dx12_ObjectFactory*);
	virtual ~GameObject();
	virtual void LoadAsset(Dx12_Device* device,Dx12_CBVSRVUAVHeap* heap) = 0;
	virtual void Initialize() = 0;
	virtual void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pers, const DirectX::XMMATRIX& ortho) = 0;
	virtual void Draw(Dx12_Renderer* renderer,Dx12_CBVSRVUAVHeap* heap) = 0;
};

