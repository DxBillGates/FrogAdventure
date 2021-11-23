#include "Player.h"
#include <cmath>

Player::Player(Dx12_ObjectFactory * objFactory, Keyboard* pKeyboard, Xinput* pCtrler)
	: keyboard(pKeyboard), ctrler(pCtrler), SIZE(128)
{
	objFactory->CreatePlane(SIZE, SIZE, &mesh, false);
	particle = new RocketParticle(objFactory, 48, 256);
}

Player::~Player()
{
	delete mtex;
	delete particle;
}

void Player::LoadAsset(Dx12_Device * device, Dx12_CBVSRVUAVHeap * heap)
{
	mtex = new Dx12_Texture2D(L"Resource/Texture/rocket2.png", device->GetDevice(), heap);
}

void Player::Initialize()
{
	pos = { 0,-256,0 };
	vel = { 0,0,0 };
	fuel = 1800;
	gemAmount = 0;
	feverMode = false;
	freqVector = { 0,0,0 };
	freqCount = 0;
	decayCount = 0;
	particle->Initialize(pos, vel);
	feverCount = 0;
	count = 0;
	finishFeverMode = false;
	finishFeverModeCount = 0;
	inputFlag = false;
}

void Player::Update(const DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pro3d, const DirectX::XMMATRIX & pro2d)
{
	float r = 10;
	if (!keyboard->CheakHitKey(Key::SPACE) || !ctrler->CheckHitKey(XinputPadKey::XINPUT_B))
	{
		inputFlag = false;
	}
	if (keyboard->CheakHitKey(Key::SPACE) || ctrler->CheckHitKey(XinputPadKey::XINPUT_B))
	{
		inputFlag = true;
	}
	//キーを押していないときは移動方向を計算
	if (!feverMode)
	{
		if (!inputFlag)
		{
			freqVector.x = r * std::sin(DirectX::XM_2PI / 360 * freqCount) + pos.x;
			freqVector.y = r * std::cos(DirectX::XM_2PI / 360 * freqCount) + pos.y;
			freqVector.z = 0;
			freqCount+=6.7f;
			directionVector = freqVector - pos;
			directionVector /= std::sqrt(directionVector.x*directionVector.x) + (directionVector.y*directionVector.y) / 10;
			decayCount = 0;
			if (vel.Length() > 0)
			{
				++decayCount;
				vel -= vel / 130;
				/*if (decayCount > 90)
				{
					vel = { 0,0,0 };
					decayCount = 0;
				}*/
			}
		}
		//押しているときは向いている方向に加速
		else
		{
			--fuel;
			if (fuel < 0)
			{
				fuel = 0;
				if (vel.Length() > 0)
				{
					++decayCount;
					vel -= vel / 100;
					if (decayCount > 120)
					{
						vel = { 0,0,0 };
						decayCount = 0;
					}
				}
			}
			if (fuel > 0)
			{
				vel -= vel / 18;
				vel += directionVector/1.5f;
			}
			
		}
		if (vel.x > 80)
		{
			vel.x = 80;
		}
	}
	else
	{
		if (!finishFeverMode)
		{
			directionVector = Vector3(1, 0, 0);
			vel += directionVector / 5;
			pos += vel;
		}
		else
		{
			if (vel.Length() > 0)
			{
				++decayCount;
				vel -= vel / 10;
				if (decayCount > 120)
				{
					vel = { 0,0,0 };
					decayCount = 0;
				}
			}
		}
	}
	if (feverMode)
	{
		particle->RainbowUpdate(view, pro3d, pos - directionVector * 128, { -vel.x,-vel.y,0 });
	}
	else
	{
		particle->Update(view, pro3d, pos - directionVector * 128, { -vel.x,-vel.y,0 });
	}

	//所持ジェム数が一定値になったらフィーバー
	const int MAX_GEM = 3;
	if (gemAmount >= MAX_GEM)
	{
		feverMode = true;
	}
	const int FEVER_COUNT = 7;
	if (feverMode)
	{
		if (feverCount > FEVER_COUNT)
		{
			feverCount = 0;
			finishFeverMode = true;
		}
		if (count > 60)
		{
			count = 0;
			++feverCount;
		}
		++count;
	}

	if (finishFeverMode)
	{
		++finishFeverModeCount;
		if (finishFeverModeCount > 60)
		{
			finishFeverModeCount = 0;
			finishFeverMode = false;
			feverMode = false;
			gemAmount = 0;
		}
	}

	pos += vel;
	mesh.Update({ pos.x,pos.y,pos.z }, { 0,0,atan2f(directionVector.y,directionVector.x) }, view, pro3d);
}

void Player::Draw(Dx12_Renderer * renderer, Dx12_CBVSRVUAVHeap * heap)
{
	renderer->Render(&mesh, mtex, heap);
	particle->Draw(renderer, heap);
}

Vector3 Player::GetPos()
{
	return pos;
}

Vector3 Player::GetVel()
{
	return vel;
}

void Player::IncreaseVel(const Vector3 & iVel)
{
	Vector3 vector = vel / 50;
	vel += vector;
}

void Player::IncreaceFuel(int value)
{
	fuel += value;
}

int Player::GetFuelValue()
{
	return fuel;
}

float Player::GetSize()
{
	return SIZE;
}

void Player::IncreaseGemAmount()
{
	++gemAmount;
}

bool Player::GetFeverMode()
{
	return feverMode;
}

void Player::SetVel(Vector3 vel)
{
	this->vel = vel;
}

void Player::SetPos(Vector3 pos)
{
	this->pos = pos;
}

