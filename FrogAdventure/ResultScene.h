#pragma once
#include "Scene.h"
#include "Player.h"
#include "SoundData.h"
#include "Sound.h"
#include "SceneToScene.h"
class ResultScene : public Scene
{
private:
	std::vector<Dx12_Texture2D*>* pNumberTextures;
	std::vector<Dx12_Object2D> meterObjs;
	Dx12_Object2D restartObj;
	Dx12_Texture2D* restartTexture;
	int meter;
	Player* pPlayer;
	int count;
	bool drawFlag;
	bool sceneToSceneFlag;
	SceneToScene* pSceneToScene;
	SceneName nextSceneName;
	bool beginSceneToSceneFlag;

	Dx12_Object2D meterObj;
	Dx12_Texture2D* meterTex;
	SoundData hitSEData;
	Sound* hitSound;
public:
	ResultScene(Player* player,std::vector<Dx12_Texture2D*>* numberTextures,SceneToScene* sceneToScene);
	~ResultScene();
	void LoadAsset();
	void Initialize();
	void Update(DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, const DirectX::XMMATRIX& pro2d);
	void DrawSprite();
	void Draw();
	SceneName GetNextSceneName();
};

