#include "Gasoline.h"
Dx12_Texture2D* Gasoline::tex = nullptr;

Gasoline::Gasoline(Dx12_ObjectFactory * objFactory, float playerPosX) :RECOVERY(300),SIZE(64)
{
	//3D�I�u�W�F�N�g�̐���
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
	//3D�I�u�W�F�N�g�̍X�V
	static float angle = 0;
	angle += 0.01f;
	mesh.Update({ pos.x,pos.y,32}, {0,angle,0}, view, pers);
}

void Gasoline::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	//3D�I�u�W�F�N�g�̕`��
	renderer->Render(&mesh, tex, heap);
}

Vector3 Gasoline::GetPos()
{
	//���g�̍��W��Ԃ�
	return pos;
}

int Gasoline::GetRecovery()
{
	//�񕜗ʂ�Ԃ�
	return RECOVERY;
}

float Gasoline::GetSize()
{
	//�T�C�Y��Ԃ�
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
	//�O������e�N�X�`���̃C���X�^���X���󂯎��Astatic�e�N�X�`���ŕێ�
	tex = newtex;
}

void Gasoline::DeleteStaticTexture()
{
	//static�e�N�X�`����delete & nullptr
	if (tex)
	{
		delete tex;
		tex = nullptr;
	}
}
