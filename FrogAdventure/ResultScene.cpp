#include "ResultScene.h"
#include "SoundData.h"

ResultScene::ResultScene(Player * player, std::vector<Dx12_Texture2D*>* numberTextures, SceneToScene* sceneToScene) :pNumberTextures(numberTextures), meter(0), pPlayer(player), pSceneToScene(sceneToScene),
hitSEData("Resource/Music/hit04.wav")
{
	meterObjs.resize(10);
	for (auto& x : meterObjs)
	{
		objFactory->CreatePlane(44 * 2, 64 * 2, &x);
	}
	objFactory->CreatePlane(44 * 2, 64 * 2, &meterObj);
	sceneToSceneFlag = false;
	objFactory->CreatePlane(96*4, 32*4, &restartObj);
}

ResultScene::~ResultScene()
{
	delete restartTexture;
	delete hitSound;
	delete meterTex;
}

void ResultScene::LoadAsset()
{
	restartTexture = new Dx12_Texture2D(L"Resource/Texture/restart.png", device->GetDevice(), heap);
	meterTex = new Dx12_Texture2D(L"Resource/Texture/Number/M.png", device->GetDevice(), heap);

	hitSound = new Sound(&hitSEData);
}

void ResultScene::Initialize()
{
	meter = (int)pPlayer->GetPos().x;
	pPlayer->Initialize();
	pPlayer->IncreaceFuel(100000);
	count = 0;
	drawFlag = true;
	sceneToSceneFlag = true;
	nextSceneFlag = false;
	beginSceneToSceneFlag = false;
}

void ResultScene::Update(DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pro3d, const DirectX::XMMATRIX & pro2d)
{
	if (count > 90)
	{
		drawFlag = (drawFlag) ? false : true;
		count = 0;
	}
	for (int i = 0; i < (int)meterObjs.size(); ++i)
	{
		meterObjs[i].Update({ 16 * 13 + 44.0f * 2 * i,16.0f * 2 * 6,0 }, pro2d);
	}
	meterObj.Update({ 16 * 13 + 44.0f * 2 * 10,16.0f * 2 * 6,0 }, pro2d);
	if (!beginSceneToSceneFlag)
		pPlayer->Update(view, pro3d, pro2d);
	++count;
	if (sceneToSceneFlag)
	{
		pSceneToScene->DownScale();
		if (pSceneToScene->GetScale() <= 0)
		{
			sceneToSceneFlag = false;
			pSceneToScene->Initialize();
		}
		pSceneToScene->Update(view, pro3d, Vector3(pPlayer->GetPos().x, 0, 0));
	}

	Vector3 pos = pPlayer->GetPos();
	if (pos.y >= 500)
	{
		pPlayer->SetPos(Vector3(pPlayer->GetPos().x, 495, 0));
		pPlayer->SetVel(Vector3(pPlayer->GetVel().x,-pPlayer->GetVel().y,0));
		hitSound->Start();
	}
	else if (pos.y <= -500)
	{
		nextSceneName = GAME_PLAY;
		beginSceneToSceneFlag = true;
	}


	if (beginSceneToSceneFlag)
	{
		pSceneToScene->UpScale();
		if (pSceneToScene->GetScale() > 20)
		{
			nextSceneFlag = true;
		}
		pSceneToScene->Update(view, pro3d, Vector3(pPlayer->GetPos().x, 0, 0));
	}
	restartObj.Update({ 64 * 10-48*4,64 * 8,0 }, pro2d);
}

void ResultScene::DrawSprite()
{
	if (meter < 0)
	{
		meter = 0;
	}
	if (drawFlag)
	{
		for (int i = (int)meterObjs.size() - 1, j = 10, k = 1; i >= 0; --i, j *= 10, k *= 10)
		{
			renderer->Render(&meterObjs[i], (*pNumberTextures)[meter%j / k], heap);
		}
		renderer->Render(&meterObj, meterTex, heap);
	}
	renderer->Render(&restartObj, restartTexture, heap);
	device->ClearDepthBuffer();
}

void ResultScene::Draw()
{
	if (sceneToSceneFlag || beginSceneToSceneFlag)
	{
		pSceneToScene->Draw(renderer, heap);
	}
	pPlayer->Draw(renderer, heap);
}

SceneName ResultScene::GetNextSceneName()
{
	return nextSceneName;
}
