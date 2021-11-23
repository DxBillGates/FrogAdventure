#pragma once
#include "Particle.h"
class SpeedUpParticle : public Particles
{
public:
	SpeedUpParticle(Dx12_ObjectFactory* objFactory, float size, const int amount);
	~SpeedUpParticle();
	void Initialize(Vector3 pos, Vector3 vel);
	void Update(const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& pro3d, Vector3 pos, Vector3 vel);
	void Draw(Dx12_Renderer* renderer, Dx12_CBVSRVUAVHeap* heap);
};

