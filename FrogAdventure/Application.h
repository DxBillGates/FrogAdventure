#pragma once
#include"Window.h"
#include"Keyboard.h"
#include"Xinput.h"
#include"Dx12_Device.h"
#include"Dx12_CBVSRVUAVHeap.h"
#include"Dx12_ObjectFactory.h"
#include"Dx12_Object2D.h"
#include"Dx12_Object3D.h"
#include"Dx12_Texture2D.h"
#include"Dx12_Renderer.h"
#include"SceneManager.h"
#include"Player.h"
#include"SceneToScene.h"
#include"SoundData.h"
#include"Sound.h"
class Application
{
private:
	Window gameWindow;
	Keyboard keyboard;
	Xinput ctrler;
	Dx12_Device device;
	Dx12_CBVSRVUAVHeap cbvSrvHeap;
	Dx12_ObjectFactory objFactory;
	Dx12_Renderer* renderer;
private:
	DirectX::XMFLOAT3 eyepos;
	DirectX::XMFLOAT3 target;
	DirectX::XMFLOAT3 up;
	DirectX::XMMATRIX projection2D;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection3D;
private:
	double fps;
	std::vector<Dx12_Object2D> fpsObjects;
	std::vector<Dx12_Texture2D*> numberTextures;
private:
	SceneManager sceneManager;
	Player player;
	SceneToScene* sceneToScene;

	Dx12_Object2D botanObj;
	Dx12_Texture2D* botanTexture;
	Dx12_Texture2D* botanUpTexture;
	SoundData jetSEData;
	Sound* jetSound;

	SoundData bgmData;
	Sound* bgm;
public:
	Application(int windowWidth, int windowHeight, const char* title);
	~Application();
	void LoadAsset();
	bool Init();
	void Run();
private:
	void Update();
	void Draw();
	int count;
};

