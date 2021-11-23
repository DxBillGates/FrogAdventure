#include "Gasoline.h"
Dx12_Texture2D* Gasoline::tex = nullptr;

Gasoline::Gasoline(Dx12_ObjectFactory * objFactory, float playerPosX) :RECOVERY(300),SIZE(64)
{
	//3Dオブジェクトの生成
	objFactory->CreatePlane(SIZE, SIZE, &mesh, false);
	pos = { playerPosX + 1280, 0, 0 };
}

Gasoline::~Gasoline()
{
}

void Gasoline::LoadAsset(Dx12_Device * device, Dx12_CBVSRVUAVHeap * heap)
{
}

void Gasoline::Initialize()
{
}

void Gasoline::Init(Vector3 pos)
{
	this->pos = pos;
	isLive = true;
}

void Gasoline::Update(const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pers, const DirectX::XMMATRIX & ortho)
{
	//3Dオブジェクトの更新
	static float angle = 0;
	angle += 0.01f;
	mesh.Update({ pos.x,pos.y,32}, {0,angle,0}, view, pers);
}

void Gasoline::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	//3Dオブジェクトの描画
	renderer->Render(&mesh, tex, heap);
}

Vector3 Gasoline::GetPos()
{
	//自身の座標を返す
	return pos;
}

int Gasoline::GetRecovery()
{
	//回復量を返す
	return RECOVERY;
}

float Gasoline::GetSize()
{
	//サイズを返す
	return SIZE;
}

bool Gasoline::GetIsLive()
{
	return isLive;
}

void Gasoline::SetIsLive(bool flag)
{
	isLive = flag;
}

void Gasoline::LoadStaticTexture(Dx12_Texture2D * newtex)
{
	//外部からテクスチャのインスタンスを受け取り、staticテクスチャで保持
	tex = newtex;
}

void Gasoline::DeleteStaticTexture()
{
	//staticテクスチャをdelete & nullptr
	if (tex)
	{
		delete tex;
		tex = nullptr;
	}
}
