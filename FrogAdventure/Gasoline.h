#pragma once
#include "Item.h"
#include "Vector.h"
class Gasoline : public Item
{
private:
	static Dx12_Texture2D* tex;
	Dx12_Object3D mesh;
	Vector3 pos;
	const int RECOVERY;
	const float SIZE;
	bool isLive;
public:
	Gasoline(Dx12_ObjectFactory* objFactory,float playerPosX);
	~Gasoline();
    void LoadAsset(Dx12_Device* device, Dx12_CBVSRVUAVHeap* heap);
    void Initialize();
	void Init(Vector3 pos);
    void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pers, const DirectX::XMMATRIX& ortho);
    void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap);
	Vector3 GetPos();
	int GetRecovery();
	float GetSize();
	bool GetIsLive();
	void SetIsLive(bool flag);
	static void LoadStaticTexture(Dx12_Texture2D* newtex);
	static void DeleteStaticTexture();
};

