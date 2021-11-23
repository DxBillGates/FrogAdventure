#pragma once
#include"Dx12_Object3D.h"
#include"Dx12_ObjectFactory.h"
#include"Dx12_CBVSRVUAVHeap.h"
#include"Dx12_Renderer.h"
#include"Vector.h"
class SceneToScene
{
private:
	Dx12_Object3D mesh;
	Vector3 pos;
	float scale;
	float increaseScale;
public:
	SceneToScene(Dx12_ObjectFactory* objFactory);
	~SceneToScene();
	void Initialize();
	void UpScale();
	void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d,Vector3 pos);
	void DownScale();
	void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap);
	float GetScale();
};

