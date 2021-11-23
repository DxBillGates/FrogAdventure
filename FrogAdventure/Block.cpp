#include "Block.h"

Dx12_Texture2D* Block::mtex = nullptr;
Dx12_Texture2D* Block::speedTex = nullptr;
Block::Block(Vector3 pos, Dx12_ObjectFactory * objFactory)
	:pos(pos), isLive(false)
{
	size = 64;
	objFactory->CreatePlane(size, size, &speedUpObj, false);
	objFactory->CreatePlane(size, size, &mesh, false);
}

Block::~Block()
{
}

void Block::LoadAsset(Dx12_Device * device, Dx12_CBVSRVUAVHeap * heap)
{
}

void Block::Initialize()
{

}

void Block::Init(Vector3 pos,float num,float num2)
{
	this->pos = pos;
	isLive = true;
	scale = num;
	scale2 = num2;
	if (scale < 1)
	{
		scale = 1;
	}
}

void Block::Update(const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pro3d, const DirectX::XMMATRIX & pro2d)
{
	speedUpObj.Update({ pos.x,pos.y,pos.z+1 }, { 0,0,0 }, view, pro3d, {}, { scale2,scale2,0 });
	mesh.Update({ pos.x,pos.y,pos.z }, { 0,0,0 }, view, pro3d, {}, { scale,scale,0 });
}

void Block::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	renderer->Render(&mesh, mtex, heap);
	renderer->Render(&speedUpObj, speedTex, heap);
}

void Block::SetStaticTexture(Dx12_Texture2D * tex, Dx12_Texture2D * speedUpTex)
{
	mtex = tex;
	speedTex = speedUpTex;
}

void Block::DeleteStaticTexture()
{
	delete mtex;
	delete speedTex;
}

Vector3 Block::GetPos()
{
	return pos;
}

float Block::GetSize()
{
	return size * scale;
}

float Block::GetSpeedUpWallSize()
{
	return size  * scale2;
}

bool Block::GetIsLive()
{
	return isLive;
}

void Block::SetIsLive(bool flag)
{
	isLive = flag;
}
