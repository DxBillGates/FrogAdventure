#pragma once
#include "GameObject.h"
#include "Dx12_Object3D.h"
#include "Dx12_Texture2D.h"
#include "Vector.h"
#include "Keyboard.h"
#include "Xinput.h"
#include "Block.h"
#include "Gasoline.h"
#include "RocketParticle.h"
enum Direction
{
	RIGHT_MOVE,
	UP_MOVE,
	LEFT_MOVE,
	DOWN_MOVE
};
class Player : public GameObject
{
private:
	Keyboard* keyboard;
	Xinput* ctrler;
private:
	Dx12_Object3D mesh;
	Dx12_Texture2D* mtex;
	const float SIZE;
	Vector3 pos;
	Vector3 vel;
	Vector3 directionVector = { 0,0,0 };
	Vector3 freqVector;
	float freqCount;
	int decayCount;
	int fuel;
	int gemAmount;
	bool feverMode;
	RocketParticle* particle;
	int feverCount;
	int count;
	bool finishFeverMode;
	int finishFeverModeCount;
	bool inputFlag;
public:
	Player(Dx12_ObjectFactory* objFactory,Keyboard* pKeyboard,Xinput* pCtrler);
	~Player();
	void LoadAsset(Dx12_Device* device, Dx12_CBVSRVUAVHeap* heap);
	void Initialize();
	void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, const DirectX::XMMATRIX& pro2d);
	void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap);
	Vector3 GetPos();
	Vector3 GetVel();
	void IncreaseVel(const Vector3& iVel);
	void IncreaceFuel(int value);
	int GetFuelValue();
	float GetSize();
	void IncreaseGemAmount();
	bool GetFeverMode();
	void SetVel(Vector3 vel);
	void SetPos(Vector3 pos);
	int GetGemAmount()
	{
		return gemAmount;
	}
};

