#include "Gem.h"

Gem::Gem(Dx12_ObjectFactory * objFactory, Vector3 rpos,Dx12_Texture2D* tex):tex(tex),SIZE(64)
{
	objFactory->CreatePlane(SIZE, SIZE, &mesh, false);
	pos = { rpos.x, rpos.y, 0 };
}

Gem::~Gem()
{
}

void Gem::LoadAsset(Dx12_Device * device, Dx12_CBVSRVUAVHeap * heap)
{
}

void Gem::Initialize()
{
}

void Gem::Init(Vector3 pos)
{
	this->pos = pos;
	isLive = true;
}

void Gem::Update(const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pers, const DirectX::XMMATRIX & ortho)
{
	float static angle = 0;
	angle += 0.03f;
	mesh.Update({pos.x,pos.y,32}, {0,angle,0}, view, pers);
}

void Gem::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	renderer->Render(&mesh, tex, heap);
}

Vector3 Gem::GetPos()
{
	return pos;
}

float Gem::GetSize()
{
	return SIZE;
}

bool Gem::GetIsLive()
{
	return isLive;
}

void Gem::SetIsLive(bool flag)
{
	isLive = flag;
}
