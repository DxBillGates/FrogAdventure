#pragma once
#include "Dx12_Object3D.h"
#include "Dx12_ObjectFactory.h"
#include "Dx12_CBVSRVUAVHeap.h"
#include "Dx12_Renderer.h"
#include "Vector.h"
#include <vector>
struct Particle
{
	Vector3 pos;
	Vector3 vel;
	float size;
	Vector3 color;
	float alpha;
	bool isDraw;
};

class Particles
{
protected:
	std::vector<Particle> particle;
	std::vector<Dx12_Object3D> meshs;
public:
	Particles() {}
	virtual ~Particles() {}
	virtual void Initialize(Vector3 pos,Vector3 vel) = 0;
	virtual void Update(const DirectX::XMMATRIX& view,const DirectX::XMMATRIX& pro3d,Vector3 pos,Vector3 vel) = 0;
	virtual void Draw(Dx12_Renderer* renderer,Dx12_CBVSRVUAVHeap* heap) = 0;
};

