#include "GamePlayScene.h"
#include <math.h>
GamePlayScene::GamePlayScene(Player * pPlayer, SceneToScene* sceneToScene, std::vector<Dx12_Texture2D*>* whiteNumberTextures) : player(pPlayer), pSceneToScene(sceneToScene), sceneToSceneFlag(false), pWhiteNumberTextures(whiteNumberTextures),
itemSEData("Resource/Music/Item.wav"), explosionSEData("Resource/Music/Explosion.wav"), hitSEData("Resource/Music/hit04.wav")
{
	objFactory->CreatePlane(1280, 640, &frontBObjLeft);
	objFactory->CreatePlane(1280, 640, &frontBObjCenter);
	objFactory->CreatePlane(1280, 640, &frontBObjRight);
	objFactory->CreatePlane(1280, 640, &centerBObjLeft);
	objFactory->CreatePlane(1280, 640, &centerBObjCenter);
	objFactory->CreatePlane(1280, 640, &centerBObjRight);
	objFactory->CreatePlane(1280, 640, &backBObjLeft);
	objFactory->CreatePlane(1280, 640, &backBObjCenter);
	objFactory->CreatePlane(1280, 640, &backBObjRight);
	objFactory->CreatePlane(1280, 640, &titleObj, false);
	meterObjects.resize(10);
	fuelValueObjects.resize(5);
	for (int i = 0; i < (int)meterObjects.size(); ++i)
	{
		objFactory->CreatePlane(44, 64, &meterObjects[i]);
	}
	for (int i = 0; i < (int)fuelValueObjects.size(); ++i)
	{
		objFactory->CreatePlane(44, 64, &fuelValueObjects[i]);
	}
	objFactory->CreatePlane(44, 64, &fuelObj);
	objFactory->CreatePlane(44, 64, &meterObj);
	//MAX_BLOCK�̐����u���b�N�𐶐�
	const int MAX_BLOCK = 10;
	blocks.resize(MAX_BLOCK);
	for (auto& x : blocks)
	{
		x = new Block(Vector3(), objFactory);
	}

	//MAX_GEM�̐����t�B�[�o�[�A�C�e���𐶐�
	gemTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/itemTexture.png", device->GetDevice(), heap));
	const int MAX_GEM = 10;
	gems.resize(MAX_GEM);
	for (auto& x : gems)
	{
		x = new Gem(objFactory, Vector3(), gemTextures[0]);
	}

	//MAX_FUEL�̐����K�\�����A�C�e���𐶐�
	const int MAX_FUEL = 10;
	gasolines.resize(MAX_FUEL);
	for (auto& x : gasolines)
	{
		x = new Gasoline(objFactory, 0);
	}
	inScene = true;

	voidGemsMesh.resize(3);
	getGems.resize(3);
	for (auto& x : voidGemsMesh)
	{
		objFactory->CreatePlane(64, 64, &x);
	}

	speedUpParticle = new SpeedUpParticle(objFactory, 64, 64);
}

GamePlayScene::~GamePlayScene()
{
	delete backGroundFrontTex;
	delete backGroundCenterTex;
	delete backGroundBackTex;
	Block::DeleteStaticTexture();
	Gasoline::DeleteStaticTexture();
	//�u���b�N��S������������������
	for (auto& x : blocks)
	{
		delete x;
	}
	//�A�C�e����S������������������
	for (auto& x : gems)
	{
		delete x;
	}
	//�A�C�e����S������������������
	for (auto& x : gasolines)
	{
		delete x;
	}
	for (auto& x : numberTextures)
	{
		delete x;
	}
	for (auto& x : gemTextures)
	{
		delete x;
	}
	delete spriteRenderer;
	delete itemSound;
	delete jetSound;
	delete explosionSound;
	delete fuelTex;
	delete titleTex;
	delete hitSound;
	delete meterTex;
	delete voidGemTex;
	delete speedUpParticle;
}

void GamePlayScene::LoadAsset()
{
	spriteRenderer = new Dx12_Renderer(new Dx12_Pipeline(device->GetDevice(), new Dx12_Shader(L"TexVS.hlsl", L"TexPS.hlsl"), new Dx12_RootSignature(device->GetDevice(), 2), 2, true),
		new Dx12_Pipeline(device->GetDevice(), new Dx12_Shader(L"basicVS.hlsl", L"basicPS.hlsl"), new Dx12_RootSignature(device->GetDevice(), 1), 1, true), device->GetCmdList());

	backGroundFrontTex = new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/front.png", device->GetDevice(), heap);
	backGroundCenterTex = new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/center.png", device->GetDevice(), heap);
	backGroundBackTex = new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/back.png", device->GetDevice(), heap);
	Gasoline::LoadStaticTexture(new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/FuelTexture.png", device->GetDevice(), heap));
	Block::SetStaticTexture(new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/Block01Texture.png", device->GetDevice(), heap), new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/SpeedUpTexture.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/0.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/1.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/2.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/3.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/4.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/5.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/6.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/7.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/8.png", device->GetDevice(), heap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/9.png", device->GetDevice(), heap));
	meterTex = new Dx12_Texture2D(L"Resource/Texture/Number/M.png", device->GetDevice(), heap);


	itemSound = new Sound(&itemSEData);
	explosionSound = new Sound(&explosionSEData);
	hitSound = new Sound(&hitSEData);

	fuelTex = new Dx12_Texture2D(L"Resource/Texture/fire.png", device->GetDevice(), heap);
	titleTex = new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/TitleTexture.png", device->GetDevice(), heap);

	voidGemTex = new Dx12_Texture2D(L"Resource/Texture/GamePlayScene/voidGemTexture.png", device->GetDevice(), heap);
}

void GamePlayScene::Initialize()
{
	f = 0;
	c = 0;
	b = 0;
	//�u���b�N�����ׂď�����
	for (auto& x : blocks)
	{
		x->Init(Vector3(), 1, 1);
		x->SetIsLive(false);
	}
	//�t�B�[�o�[�A�C�e�������ׂď�����
	for (auto& x : gems)
	{
		x->Init(Vector3());
		x->SetIsLive(false);
	}
	//�K�\�����A�C�e�������ׂď�����
	for (auto& x : gasolines)
	{
		x->Init(Vector3());
		x->SetIsLive(false);
	}

	player->Initialize();
	blockSize = 1.0f;
	speedUpSize = 14.0f;

	for (auto& x : gasolines)
	{
		if (!x->GetIsLive())
		{
			x->Init(Vector3(player->GetPos().x + 640, player->GetPos().y, 0));
			break;
		}
	}
	frontBObjPosCenter = { 0,0,0 };
	nextSceneFlag = false;
	shakeFlag = false;
	sceneToSceneFlag = false;
	playerPos2X = 0;

	randNum = 5;
	randXNum = (int)(std::rand() % 100) + 300;
	inScene = true;
	speedUpParticle->Initialize(player->GetPos(), Vector3());
}

void GamePlayScene::Update(DirectX::XMMATRIX & view, const DirectX::XMMATRIX & pro3d, const DirectX::XMMATRIX & pro2d)
{
	fuelObj.Update({ 44.0f * 5,64.0f * 9,0 }, pro2d);
	if (inScene)
	{
		pSceneToScene->DownScale();
		pSceneToScene->Update(view, pro3d, {});
		if (pSceneToScene->GetScale() < 0)
		{
			pSceneToScene->Initialize();
			inScene = false;
		}
	}
	shakeFlag = false;
	Vector3 playerPos = player->GetPos();
	float playerSize = player->GetSize();
	Vector3 gemPos = {};
	Vector3 gasolinePos = {};
	Vector3 blockPos = {};
	float playerToOtherDistance = 0;

	//�ⓖ���蔻��
	for (int i = 0; i < (int)blocks.size(); ++i)
	{
		//�u���b�N�������Ă��Ȃ��Ȃ炻�����������蔻������Ȃ�
		if (!blocks[i]->GetIsLive())
		{
			continue;
		}
		//�����Ă����ꍇ�̏���
		//�������v�Z
		blockPos = blocks[i]->GetPos();
		playerToOtherDistance = (playerPos.x - blockPos.x)*(playerPos.x - blockPos.x) + (playerPos.y - blockPos.y)*(playerPos.y - blockPos.y);
		//�u���b�N�Ƃ̋���������Ă�����u���b�N��j��
		if (playerToOtherDistance >= 1920 * 1920)
		{
			blocks[i]->SetIsLive(false);
		}
		//�X�s�[�h���オ��o���A�I�Ȃ̂Ƃ̓����蔻������������Ă���Ȃ�v���C���[�̑��x�x�N�g���𑝂₷
		if (playerToOtherDistance <= blocks[i]->GetSpeedUpWallSize() * (playerSize+16))
		{
			player->IncreaseVel({ 0,0,0 });
		}
		//�������ĂȂ��Ȃ�u���b�N�ɂ��瓖�����Ă��Ȃ��̂Ŏ��̃u���b�N�Ƃ̏�����
		else
		{
			continue;
		}
		if (playerToOtherDistance <= blocks[i]->GetSize() * playerSize - 48)
		{
			//�v���C���[���t�B�[�o�[���Ȃ�u���b�N��j��
			if (player->GetFeverMode())
			{
				explosionSound->Start();
				shakeFlag = true;
				blocks[i]->SetIsLive(false);
			}
			//����Ȃ��Ȃ玟�̃V�[����
			else
			{
				sceneToSceneFlag = true;
			}
		}
	}
	//�t�B�[�o�[�A�C�e�������蔻��
	for (auto& x : gems)
	{
		//���݂��Ă��Ȃ��Ȃ玟�̃A�C�e����
		if (!x->GetIsLive())
		{
			continue;
		}
		//���݂��Ă��ꍇ�̏���
		//�������v�Z
		gemPos = x->GetPos();
		playerToOtherDistance = (playerPos.x - gemPos.x)*(playerPos.x - gemPos.x) + (playerPos.y - gemPos.y)*(playerPos.y - gemPos.y);
		//����������Ă���ꍇ�͔j��
		if (playerToOtherDistance >= 1920 * 1920)
		{
			x->SetIsLive(false);
		}
		//�v���C���[���t�B�[�o�[���[�h�Ȃ炷�ׂẴt�B�[�o�[�A�C�e���͓����蔻�������Ӗ����Ȃ��̂ŏ������΂�
		if (player->GetFeverMode())
		{
			break;
		}
		//�������Ă���Ȃ�v���C���[�̃A�C�e���������𑝂₷
		//���̌�A�C�e����j��
		if (playerToOtherDistance <= x->GetSize() * playerSize)
		{
			itemSound->Start();
			player->IncreaseGemAmount();
			x->SetIsLive(false);
		}
	}
	//�K�\�����Ƃ̓����蔻��
	for (auto& x : gasolines)
	{
		//���݂��Ă��Ȃ��Ȃ玟�̃A�C�e����
		if (!x->GetIsLive())
		{
			continue;
		}
		//���݂��Ă����ꍇ�̏���
		//�������v�Z
		gasolinePos = x->GetPos();
		playerToOtherDistance = (playerPos.x - gasolinePos.x)*(playerPos.x - gasolinePos.x) + (playerPos.y - gasolinePos.y)*(playerPos.y - gasolinePos.y);
		//����������Ă���Ȃ�j��
		if (playerToOtherDistance >= 1920 * 1920)
		{
			x->SetIsLive(false);
		}
		//�������Ă���Ȃ�v���C���[�̔R������
		if (playerToOtherDistance <= x->GetSize() * playerSize)
		{
			itemSound->Start();
			player->IncreaceFuel(x->GetRecovery());
			x->SetIsLive(false);
		}
	}
	//�I�u�W�F�N�g�̒ǉ�---------------------------------------------------------------------------------

	if (playerPos.x > 3500)
	{
		randNum = 10;
	}
	if (playerPos.x > 10000)
	{
		blockSize = 1.5f;
		speedUpSize = 14.0f;
	}
	if (playerPos.x > 55000)
	{
		randNum = 12;
	}
	if (playerPos.x > 100000)
	{
		blockSize = 2.0f;
		speedUpSize = 14.0f;
	}
	if (playerPos.x > 120000)
	{
		blockSize = 2.5f;
		speedUpSize = 14.0f;
	}
	if (playerPos.x > 140000)
	{
		speedUpSize = 12.0f;
	}
	if (playerPos.x > 150000)
	{
		randNum = 20;
	}
	if (playerPos.x > 200000)
	{
		blockSize = (float)(std::rand() % 3 + 1);
		speedUpSize = blockSize * 5;
	}

	if (playerPos.x > playerPos2X + randXNum)
	{
		Vector3 vec = player->GetVel();
		if (vec.x > 0)
		{
			//�ǉ�������̂̃����_���l
			int random = std::rand() % randNum;
			//���������_��

			float randomY = (float)(std::rand() % 500);
			float randomY2 = (float)(std::rand() % 500);
			if (random % 2 == 1)
			{
				randomY *= -1;
				randomY2 *= -1;
			}
			switch (random)
			{
			case 0:
			case 1:
			case 13:
			case 14:
				for (auto& x : gasolines)
				{
					if (!x->GetIsLive())
					{
						x->Init(Vector3(player->GetPos().x + 1280, randomY2, 0));
						break;
					}
				}
				break;
			case 7:
			case 15:
				for (auto& x : gems)
				{
					if (!x->GetIsLive())
					{
						x->Init(Vector3(player->GetPos().x + 1280, randomY2, 0));
						break;
					}
				}
				break;
			default:
				for (auto& x : blocks)
				{
					if (!x->GetIsLive())
					{
						x->Init(Vector3(player->GetPos().x + 1280, randomY, 0), blockSize, speedUpSize);
						break;
					}
				}
				break;
			}
		}


		randXNum = (int)(std::rand() % 400) + 800;
		playerPos2X = playerPos.x;
	}

	//�w�i�I�u�W�F�N�g�̍X�V
	//Front
	frontBObjPosCenter.x = f - player->GetPos().x / 6.0f;
	if (frontBObjPosCenter.x < -1280)
	{
		f += 1280;
		frontBObjPosCenter.x = 0;
	}
	else if (frontBObjPosCenter.x > 1280)
	{
		f -= 1280;
		frontBObjPosCenter.x = 0;
	}
	//Center
	centerBObjPosCenter.x = c - player->GetPos().x / 8.0f;
	if (centerBObjPosCenter.x < -1280)
	{
		c += 1280;
		centerBObjPosCenter.x = 0;
	}
	else if (centerBObjPosCenter.x > 1280)
	{
		c -= 1280;
		centerBObjPosCenter.x = 0;
	}
	//Back
	backBObjPosCenter.x = b - player->GetPos().x / 10.0f;
	if (backBObjPosCenter.x < -1280)
	{
		b += 1280;
		backBObjPosCenter.x = 0;
	}
	else if (centerBObjPosCenter.x > 1280)
	{
		b -= 1280;
		backBObjPosCenter.x = 0;
	}

	//��ʗh��
	if (shakeFlag)
	{
		Vector3 shakeVec;
		shakeVec.x = (float)std::rand();
		shakeVec.y = (float)std::rand();
		shakeVec /= std::sqrt((shakeVec.x * shakeVec.x) + (shakeVec.y * shakeVec.y));
		shakeVec *= 50;
		DirectX::XMFLOAT3 eyepos = { playerPos.x + shakeVec.x,0 + shakeVec.y,-1000 };
		DirectX::XMFLOAT3 target = { playerPos.x + shakeVec.x,0 + shakeVec.y,1 };
		DirectX::XMFLOAT3 up = { 0,1,0 };
		view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eyepos), DirectX::XMLoadFloat3(&target), DirectX::XMLoadFloat3(&up));
	}

	//�I�u�W�F�N�g�̍X�V(���W�A��]�A�X�N���[��)
	//�t�B�[�o�[�A�C�e���̍X�V����
	for (auto& x : gems)
	{
		//���݂��Ă���Ȃ�X�V����
		if (x->GetIsLive())
		{
			x->Update(view, pro3d, pro2d);
		}
	}
	//�K�\�����A�C�e���̍X�V����
	for (auto& x : gasolines)
	{
		//���݂��Ă���Ȃ�X�V����
		if (x->GetIsLive())
		{
			x->Update(view, pro3d, pro2d);
		}
	}
	//�u���b�N�̍X�V����
	for (auto& x : blocks)
	{
		//�u���b�N�������Ă���Ȃ�X�V����
		if (x->GetIsLive())
		{
			x->Update(view, pro3d, pro2d);
		}
	}
	for (int i = 0; i < (int)meterObjects.size(); ++i)
	{
		meterObjects[i].Update({ 44.0f*i,0,0 }, pro2d);
	}
	meterObj.Update({ 44.0f * 10,0,0 }, pro2d);
	for (int i = 0; i < (int)fuelValueObjects.size(); ++i)
	{
		fuelValueObjects[i].Update({ 44.0f*i,64 * 9,0 }, pro2d);
	}
	frontBObjLeft.Update({ frontBObjPosCenter.x - 1280,0,0 }, pro2d);
	frontBObjCenter.Update({ frontBObjPosCenter.x,0,0 }, pro2d);
	frontBObjRight.Update({ frontBObjPosCenter.x + 1280,0,0 }, pro2d);
	centerBObjLeft.Update({ centerBObjPosCenter.x - 1280,0,0 }, pro2d);
	centerBObjCenter.Update({ centerBObjPosCenter.x,0,0 }, pro2d);
	centerBObjRight.Update({ centerBObjPosCenter.x + 1280,0,0 }, pro2d);
	backBObjLeft.Update({ backBObjPosCenter.x - 1280,0,0 }, pro2d);
	backBObjCenter.Update({ backBObjPosCenter.x,0,0 }, pro2d);
	backBObjRight.Update({ backBObjPosCenter.x + 1280,0,0 }, pro2d);
	if (!sceneToSceneFlag)
	{
		player->Update(view, pro3d, pro2d);
	}


	if (sceneToSceneFlag)
	{
		pSceneToScene->UpScale();
		pSceneToScene->Update(view, pro3d, Vector3(player->GetPos().x, 0, 0));
		if (pSceneToScene->GetScale() > 20)
		{
			nextSceneFlag = true;
		}
	}

	if (player->GetPos().y > 500)
	{
		player->SetVel(Vector3(player->GetVel().x, -player->GetVel().y, 0));
		player->SetPos(Vector3(player->GetPos().x, 495, 0));
		hitSound->Start();
	}
	else if (player->GetPos().y < -500)
	{
		player->SetVel(Vector3(player->GetVel().x, -player->GetVel().y, 0));
		player->SetPos(Vector3(player->GetPos().x, -495, 0));
		hitSound->Start();
	}
	if (player->GetPos().x <= -1280)
	{
		player->SetVel(Vector3(-player->GetVel().x, player->GetVel().y, 0));
		player->SetPos(Vector3(-1275, player->GetPos().y, 0));
		hitSound->Start();
	}
	if (player->GetFuelValue() == 0)
	{
		sceneToSceneFlag = true;
	}
	titleObj.Update({ 0,128,0 }, {}, view, pro3d);

	for (int i = 0; i < voidGemsMesh.size(); ++i)
	{
		voidGemsMesh[i].Update({ 44.0f*i,64 * 8,0 }, pro2d);
	}

	int a = player->GetGemAmount();
	if (a == 0)
	{
		for (auto x : getGems)
		{
			x = false;
		}
	}
	else if (a == 1)
	{
		getGems[0] = true;
	}
	else if (a == 2)
	{
		getGems[1] = true;
	}
	else if (a == 3)
	{
		getGems[2] = true;
	}

	Vector3 playerVel = player->GetVel();
	Vector3 setVel = Vector3();
	Vector3 setPos = player->GetPos();

	setVel += (playerVel.x > 0) ? Vector3(-playerVel.x-50, 0, 0) : Vector3(playerVel.x+50, 0, 0);
	setVel += (playerVel.y > 0) ? Vector3(0, -playerVel.y, 0) : Vector3(0, -playerVel.y, 0);
	setPos = (playerVel.x > 0) ? playerPos + Vector3(1000, 0, 0) : playerPos + Vector3(-1000, 0, 0);

	speedUpParticle->Update(view, pro3d, setPos,setVel);
}

void GamePlayScene::DrawSprite()
{
	//�w�i�`��
	spriteRenderer->Render(&frontBObjLeft, backGroundFrontTex, heap);
	spriteRenderer->Render(&frontBObjCenter, backGroundFrontTex, heap);
	spriteRenderer->Render(&frontBObjRight, backGroundFrontTex, heap);
	spriteRenderer->Render(&centerBObjLeft, backGroundCenterTex, heap);
	spriteRenderer->Render(&centerBObjCenter, backGroundCenterTex, heap);
	spriteRenderer->Render(&centerBObjRight, backGroundCenterTex, heap);
	spriteRenderer->Render(&backBObjLeft, backGroundBackTex, heap);
	spriteRenderer->Render(&backBObjCenter, backGroundBackTex, heap);
	spriteRenderer->Render(&backBObjRight, backGroundBackTex, heap);
	int meter = (int)player->GetPos().x * 1;
	device->ClearDepthBuffer();

	if (meter < 0)
	{
		meter = 0;
	}
	//Meter�`��
	for (int i = (int)meterObjects.size() - 1, j = 10, k = 1; i >= 0; --i, j *= 10, k *= 10)
	{
		spriteRenderer->Render(&meterObjects[i], (*pWhiteNumberTextures)[meter%j / k], heap);
	}
	spriteRenderer->Render(&meterObj, meterTex, heap);
	//�c��R���`��
	for (int i = (int)fuelValueObjects.size() - 1, j = 10, k = 1; i >= 0; --i, j *= 10, k *= 10)
	{
		spriteRenderer->Render(&fuelValueObjects[i], numberTextures[player->GetFuelValue() % j / k], heap);
	}
	spriteRenderer->Render(&fuelObj, fuelTex, heap);

	for (int i = 0; i < 3; ++i)
	{
		if (getGems[i])
		{
			spriteRenderer->Render(&voidGemsMesh[i], gemTextures[0], heap);
		}
		else
		{
			spriteRenderer->Render(&voidGemsMesh[i], voidGemTex, heap);
		}
	}
}

void GamePlayScene::Draw()
{
	//�W�F���A�C�e���`��
	for (auto& x : gems)
	{
		//���݂��Ă���Ȃ�`��
		if (x->GetIsLive())
		{
			x->Draw(renderer, heap);
		}
	}
	//�R���A�C�e���`��
	for (auto& x : gasolines)
	{
		//���݂��Ă���Ȃ�`��
		if (x->GetIsLive())
		{
			x->Draw(renderer, heap);
		}
	}
	//�v���C���[�`��
	player->Draw(renderer, heap);
	//�u���b�N�`��
	for (auto& x : blocks)
	{
		//�u���b�N�������Ă���Ȃ�`��
		if (x->GetIsLive())
		{
			x->Draw(renderer, heap);
		}
	}
	device->ClearDepthBuffer();
	if (sceneToSceneFlag)
	{
		pSceneToScene->Draw(renderer, heap);
	}
	if (inScene)
	{
		pSceneToScene->Draw(renderer, heap);
	}
	renderer->Render(&titleObj, titleTex, heap);

	//�ⓖ���蔻��
	Vector3 blockPos;
	float playerToOtherDistance;
	Vector3 playerPos;
	playerPos = player->GetPos();
	float playerSize = player->GetSize();
	for (int i = 0; i < (int)blocks.size(); ++i)
	{
		//�u���b�N�������Ă��Ȃ��Ȃ炻�����������蔻������Ȃ�
		if (!blocks[i]->GetIsLive())
		{
			continue;
		}
		//�����Ă����ꍇ�̏���
		//�������v�Z
		blockPos = blocks[i]->GetPos();
		playerToOtherDistance = (playerPos.x - blockPos.x)*(playerPos.x - blockPos.x) + (playerPos.y - blockPos.y)*(playerPos.y - blockPos.y);
		//�X�s�[�h���オ��o���A�I�Ȃ̂Ƃ̓����蔻������������Ă���Ȃ�v���C���[�̑��x�x�N�g���𑝂₷
		if (playerToOtherDistance <= blocks[i]->GetSpeedUpWallSize() * (playerSize + 80))
		{
			speedUpParticle->Draw(renderer, heap);
		}
	}
}

SceneName GamePlayScene::GetNextSceneName()
{
	return RESULT;
}
