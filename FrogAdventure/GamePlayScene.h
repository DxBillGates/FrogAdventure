#pragma once
#include"Scene.h"
#include"Player.h"
#include"Block.h"
#include"Dx12_Object2D.h"
#include"Dx12_Texture2D.h"
#include"Vector.h"
#include<vector>
#include"Gasoline.h"
#include"Gem.h"
#include"SoundData.h"
#include"Sound.h"
#include"SceneToScene.h"
#include"SpeedUpParticle.h"
class GamePlayScene : public Scene
{
private:
	Dx12_Renderer* spriteRenderer;
	float f;
	float c;
	float b;
	bool shakeFlag;
	Dx12_Object2D frontBObjLeft;
	Dx12_Object2D frontBObjCenter;
	Dx12_Object2D frontBObjRight;
	Vector3 frontBObjPosCenter;
	Dx12_Object2D centerBObjLeft;
	Dx12_Object2D centerBObjCenter;
	Dx12_Object2D centerBObjRight;
	Vector3 centerBObjPosCenter;
	Dx12_Object2D backBObjLeft;
	Dx12_Object2D backBObjCenter;
	Dx12_Object2D backBObjRight;
	Vector3 backBObjPosCenter;
	Dx12_Texture2D* backGroundFrontTex;
	Dx12_Texture2D* backGroundCenterTex;
	Dx12_Texture2D* backGroundBackTex;

	Player* player;
	std::vector<Gasoline*> gasolines;
	std::vector<Gem*> gems;
	std::vector<Block*> blocks;
	std::vector<Dx12_Texture2D*> gemTextures;
	std::vector<Dx12_Texture2D*> numberTextures;
	std::vector<Dx12_Texture2D*>* pWhiteNumberTextures;
	std::vector<Dx12_Object2D> meterObjects;
	std::vector<Dx12_Object2D> fuelValueObjects;
	Dx12_Object2D meterObj;
	Dx12_Texture2D* meterTex;

	Sound* hitSound;
	Sound* itemSound;
	Sound* jetSound;
	Sound* explosionSound;
	SceneToScene* pSceneToScene;
	bool sceneToSceneFlag;
	float playerPos2X;
	float blockSize;
	float speedUpSize;
	int randNum;
	int randXNum;
	bool inScene;

	Dx12_Object2D fuelObj;
	Dx12_Texture2D* fuelTex;
	Dx12_Object3D titleObj;
	Dx12_Texture2D* titleTex;

	Dx12_Texture2D* voidGemTex;
	std::vector<Dx12_Object2D> voidGemsMesh;
	std::vector<bool> getGems;

	SoundData itemSEData;
	SoundData explosionSEData;
	SoundData hitSEData;
	SpeedUpParticle* speedUpParticle;
public:
	GamePlayScene(Player* pPlayer,SceneToScene* sceneToScene, std::vector<Dx12_Texture2D*>* whiteNumberTextures);
	~GamePlayScene();
	void LoadAsset();
	void Initialize();
	void Update(DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, const DirectX::XMMATRIX& pro2d);
	void DrawSprite();
	void Draw();
	SceneName GetNextSceneName();
};

