#include "SceneToScene.h"

SceneToScene::SceneToScene(Dx12_ObjectFactory * objFactory):increaseScale(0.1f)
{
	objFactory->CreatePlane(128, 64, &mesh, false);
}

SceneToScene::~SceneToScene()
{
}

void SceneToScene::Initialize()
{
	scale = 0;
	increaseScale = 0.01f;
}

void SceneToScene::UpScale()
{
	increaseScale += 0.01f;
	scale += increaseScale;
}

void SceneToScene::Update(const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pro3d, Vector3 pos)
{
	mesh.Update({pos.x,pos.y,-32}, {}, view, pro3d, { 0,0,0,1 }, { scale,scale,1 });
}

void SceneToScene::DownScale()
{
	increaseScale += 0.01f;
	scale -= increaseScale;
}

void SceneToScene::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	renderer->Render(&mesh, nullptr, heap);
}

float SceneToScene::GetScale()
{
	return scale;
}
