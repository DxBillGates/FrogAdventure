#include "SceneManager.h"

SceneManager::SceneManager():nowScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	for (auto& x : scenes)
	{
		delete x;
		x = nullptr;
		scenes.clear();
	}
}

void SceneManager::Add(Scene * newScene, SceneName sceneName)
{
	newScene->SetSceneName(sceneName);
	scenes.emplace_back(newScene);
}

void SceneManager::ChangeScene(SceneName sceneName)
{
	for (auto& x : scenes)
	{
		if (x->GetSceneName() == sceneName)
		{
			nowScene = x;
			break;
		}
	}
}

Scene * SceneManager::GetNowScene()
{
	if (!nowScene)
	{
		return nullptr;
	}
	return nowScene;
}

void SceneManager::LoadAsset()
{
	for (auto& x : scenes)
	{
		x->LoadAsset();
	}
}

void SceneManager::Initialize()
{
	if (!nowScene)
	{
		return;
	}
	nowScene->Initialize();
}

void SceneManager::Update(DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, const DirectX::XMMATRIX& pro2d)
{
	if (!nowScene)
	{
		return;
	}
	nowScene->Update(view,pro3d,pro2d);
}

void SceneManager::DrawSprite()
{
	if (!nowScene)
	{
		return;
	}
	nowScene->DrawSprite();
}

void SceneManager::Draw()
{
	if (!nowScene)
	{
		return;
	}
	nowScene->Draw();
}
