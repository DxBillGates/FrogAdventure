#pragma once
#include<DirectXMath.h>
class Keyboard;
class Xinput;
class Dx12_Device;
class Dx12_CBVSRVUAVHeap;
class Dx12_ObjectFactory;
class Dx12_Renderer;

enum SceneName
{
	DEFAULT,
	GAME_PLAY,
	RESULT,
};
class Scene
{
protected:
	static Keyboard* keyboard;
	static Xinput* ctrler;
	static Dx12_Device* device;
	static Dx12_CBVSRVUAVHeap* heap;
	static Dx12_ObjectFactory* objFactory;
	static Dx12_Renderer* renderer;
protected:
	SceneName sceneName;
	bool nextSceneFlag;
public:
	Scene();
	virtual ~Scene();
	SceneName GetSceneName();
	void SetSceneName(SceneName sceneName);
	virtual void LoadAsset() = 0;
	virtual void Initialize() = 0;
	virtual void Update(DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, const DirectX::XMMATRIX& pro2d) = 0;
	virtual void DrawSprite() = 0;
	virtual void Draw() = 0;
	bool GetNextSceneFlag();
	virtual SceneName GetNextSceneName() = 0;
	static void SetMember(Keyboard* pKeyboard, Xinput* pCtrler, Dx12_Device* pDevice, Dx12_CBVSRVUAVHeap* pHeap, Dx12_ObjectFactory* pObjFactory, Dx12_Renderer* pRenderer);
};

