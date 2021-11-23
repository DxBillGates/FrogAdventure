#pragma once
#include "Item.h"
#include "Vector.h"
class Gem : public Item
{
private:
	Dx12_Texture2D* tex;
	Dx12_Object3D mesh;
	Vector3 pos;
	const float SIZE;
	bool isLive;
public:
	Gem(Dx12_ObjectFactory* objFactory, Vector3 pos,Dx12_Texture2D* tex);
	~Gem();
	void LoadAsset(Dx12_Device* device, Dx12_CBVSRVUAVHeap* heap);
	void Initialize();
	void Init(Vector3 pos);
	void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pers, const DirectX::XMMATRIX& ortho);
	void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap);
	Vector3 GetPos();
	float GetSize();
	bool GetIsLive();
	void SetIsLive(bool flag);
};

