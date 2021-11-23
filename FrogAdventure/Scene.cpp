#include "Scene.h"
Keyboard* Scene::keyboard = nullptr;
Xinput* Scene::ctrler = nullptr;
Dx12_Device* Scene::device = nullptr;
Dx12_CBVSRVUAVHeap* Scene::heap = nullptr;
Dx12_ObjectFactory* Scene::objFactory = nullptr;
Dx12_Renderer* Scene::renderer = nullptr;

Scene::Scene()
{
}

Scene::~Scene()
{
}

SceneName Scene::GetSceneName()
{
	return sceneName;
}

void Scene::SetSceneName(SceneName sceneName)
{
	this->sceneName = sceneName;
}

bool Scene::GetNextSceneFlag()
{
	return nextSceneFlag;
}

void Scene::SetMember(Keyboard * pKeyboard, Xinput * pCtrler, Dx12_Device * pDevice, Dx12_CBVSRVUAVHeap * pHeap, Dx12_ObjectFactory * pObjFactory, Dx12_Renderer * pRenderer)
{
	keyboard = pKeyboard;
	ctrler = pCtrler;
	device = pDevice;
	heap = pHeap;
	objFactory = pObjFactory;
	renderer = pRenderer;
}
