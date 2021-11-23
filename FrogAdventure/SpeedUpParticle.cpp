#include "SpeedUpParticle.h"

SpeedUpParticle::SpeedUpParticle(Dx12_ObjectFactory * objFactory, float size, const int amount)
{
	particle.resize(amount);
	meshs.resize(amount);
	for (auto& x : meshs)
	{
		float random = (float)(std::rand() % 8);
		objFactory->CreateCube(size / (random), size / (random + 8), size / (random + 8), &x);
	}
}

SpeedUpParticle::~SpeedUpParticle()
{
}

void SpeedUpParticle::Initialize(Vector3 pos, Vector3 vel)
{
	for (int i = 0; i < (int)particle.size(); ++i)
	{
		particle[i] = { pos,vel,64,Vector3(),0,true };
	}
}

void SpeedUpParticle::Update(const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pro3d, Vector3 pos, Vector3 vel)
{
	for (int i = 0; i < (int)particle.size(); ++i)
	{
		if (particle[i].alpha < 0)
		{
			particle[i].pos = Vector3(pos.x, pos.y, pos.z);
			particle[i].vel = Vector3();
			particle[i].color = Vector3(1, 1, 1);
			particle[i].alpha = std::rand() % 255 / 255.0f;
			float range = 2500;
			particle[i].pos.y = (float)std::rand() / RAND_MAX * range - range / 2.0f;
		}
		particle[i].vel = vel;
		particle[i].pos += particle[i].vel;
		particle[i].alpha -= 0.01f;
		meshs[i].Update({ particle[i].pos.x,particle[i].pos.y,1 }, {}, view, pro3d, { particle[i].color.x,particle[i].color.y,particle[i].color.z,particle[i].alpha });
	}
	//printf("%f\n", particle[0].vel.x);
}

void SpeedUpParticle::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	for (int i = 0; i < (int)meshs.size(); ++i)
	{
		renderer->Render(&meshs[i], nullptr, heap);
	}
}
