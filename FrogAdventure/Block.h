#pragma once
#include "GameObject.h"
#include "Dx12_Object3D.h"
#include "Dx12_Texture2D.h"
#include "Vector.h"
class Block : public GameObject
{
private:
	Dx12_Object3D speedUpObj;
	Dx12_Object3D mesh;
	static Dx12_Texture2D* mtex;
	static Dx12_Texture2D* speedTex;
	Vector3 pos;
	bool isLive;
	float size;
	float scale;
	float scale2;
public:
	Block(Vector3 pos,Dx12_ObjectFactory* objFactory);
	~Block();
	void LoadAsset(Dx12_Device* device, Dx12_CBVSRVUAVHeap* heap);
	void Initialize();
	void Init(Vector3 pos,float num,float num2);
	void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, const DirectX::XMMATRIX& pro2d);
	void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap);
	static void SetStaticTexture(Dx12_Texture2D* tex,Dx12_Texture2D* speedUpTex);
	static void DeleteStaticTexture();
	Vector3 GetPos();
	float GetSize();
	float GetSpeedUpWallSize();
	bool GetIsLive();
	void SetIsLive(bool flag);
};

