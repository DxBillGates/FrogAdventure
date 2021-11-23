#include "Application.h"
#include "GamePlayScene.h"
#include "ResultScene.h"
#include "SoundData.h"
#pragma comment(lib,"winmm.lib")


Application::Application(int windowWidth, int windowHeight, const char * title)
	:gameWindow(windowWidth, windowHeight, title), device(gameWindow.GetHWND(), windowWidth, windowHeight), cbvSrvHeap(device.GetDevice(), 12800, 64),
	objFactory(device.GetDevice(), &cbvSrvHeap), keyboard(gameWindow.GetHWND(), gameWindow.GetHINSTANCE()), player(&objFactory, &keyboard, &ctrler), jetSEData("Resource/Music/Jet.wav"),
	bgmData("Resource/Music/Minig_Low.wav")
{
	eyepos = { 0,0,-1000 };
	target = { 0,0,1 };
	up = { 0,1,0 };
	projection2D = DirectX::XMMatrixOrthographicOffCenterLH(0, (float)windowWidth, (float)windowHeight, 0, 0, 1);
	view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eyepos), DirectX::XMLoadFloat3(&target), DirectX::XMLoadFloat3(&up));
	projection3D = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), (float)windowWidth / windowHeight, 0.1f, 10000);
	Sound::SetAudioEngine();
	LoadAsset();
	//シーンの追加
	sceneToScene = new SceneToScene(&objFactory);
	Scene::SetMember(&keyboard, &ctrler, &device, &cbvSrvHeap, &objFactory, renderer);
	sceneManager.Add(new GamePlayScene(&player, sceneToScene, &numberTextures), GAME_PLAY);
	sceneManager.Add(new ResultScene(&player, &numberTextures, sceneToScene), RESULT);
	fps = 0;
	fpsObjects.resize(3);
	for (int i = 0; i < (int)fpsObjects.size(); ++i)
	{
		objFactory.CreatePlane(32, 32, &fpsObjects[i]);
	}
	objFactory.CreatePlane(64, 64, &botanObj);
}

Application::~Application()
{
	for (auto& x : numberTextures)
	{
		delete x;
	}
	delete renderer;
	delete sceneToScene;
	delete botanTexture;
	delete botanUpTexture;
	delete jetSound;
	delete bgm;
}

void Application::LoadAsset()
{
	renderer = new Dx12_Renderer(new Dx12_Pipeline(device.GetDevice(), new Dx12_Shader(L"TexVS.hlsl", L"TexPS.hlsl"), new Dx12_RootSignature(device.GetDevice(), 2), 2, true),
		new Dx12_Pipeline(device.GetDevice(), new Dx12_Shader(L"basicVS.hlsl", L"basicPS.hlsl"), new Dx12_RootSignature(device.GetDevice(), 1), 1, true), device.GetCmdList());
	player.LoadAsset(&device, &cbvSrvHeap);
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white0.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white1.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white2.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white3.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white4.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white5.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white6.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white7.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white8.png", device.GetDevice(), &cbvSrvHeap));
	numberTextures.emplace_back(new Dx12_Texture2D(L"Resource/Texture/Number/white9.png", device.GetDevice(), &cbvSrvHeap));
	botanTexture = new Dx12_Texture2D(L"Resource/Texture/botan.png", device.GetDevice(), &cbvSrvHeap);
	botanUpTexture = new Dx12_Texture2D(L"Resource/Texture/botanUp.png", device.GetDevice(), &cbvSrvHeap);
	jetSound = new Sound(&jetSEData);
	bgm = new Sound(&bgmData);
}

bool Application::Init()
{
	gameWindow.DisplayWindow();
	player.Initialize();
	sceneToScene->Initialize();
	//現在のシーンの初期化
	sceneManager.ChangeScene(GAME_PLAY);
	sceneManager.Initialize();
	count = 0;
	return true;
}

void Application::Run()
{
	int count = 0;
	const float FRAME_TIME = 1.0f / 60;
	double frameTime = 0;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	QueryPerformanceFrequency(&timeFreq);
	QueryPerformanceCounter(&timeStart);

	sceneManager.LoadAsset();


	while (!keyboard.CheakHitKey(Key::ESCAPE))
	{
		QueryPerformanceCounter(&timeEnd);
		frameTime = static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<double>(timeFreq.QuadPart);
		if (frameTime < FRAME_TIME)
		{
			//Sleepの時間を計算
			DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - frameTime) * 1000);
			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
			continue;
		}
		timeStart = timeEnd;
		fps = 1.0f / frameTime;

		keyboard.Update();
		ctrler.Update();
		Update();
		Draw();
		if (!gameWindow.ProcessMessage())break;
	}
}

void Application::Update()
{
	eyepos.x = player.GetPos().x;
	target.x = player.GetPos().x;
	view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eyepos), DirectX::XMLoadFloat3(&target), DirectX::XMLoadFloat3(&up));
	if (keyboard.KeyPressTrigger(Key::D1))Init();
	//現在のシーンから次のシーンへ移るフラグが送られたらそのシーンから
	//次のシーンの名前を受け取りシーンを遷移しシーンを初期化する
	if (sceneManager.GetNowScene())
	{
		if (sceneManager.GetNowScene()->GetNextSceneFlag())
		{
			sceneManager.ChangeScene(sceneManager.GetNowScene()->GetNextSceneName());
			sceneManager.Initialize();
		}
	}
	//現在のシーンの更新処理
	sceneManager.Update(view, projection3D, projection2D);
	/*for (int i = 0, j = 37; i < (int)fpsObjects.size(); ++i, ++j)
	{
		fpsObjects[i].Update({ 32.0f*j,0,0 }, projection2D);
	}*/
	botanObj.Update({ 64 * 19,64 * 9,0 }, projection2D);

	if (player.GetVel().Length() > 1 )
	{
		//jetSound->Start();
		/*if(count == 0)
		++count;
		if (count == 90)
		{
			count = 0;
		}*/
	}
	bgm->Start();
	
}

void Application::Draw()
{
	device.ClearScreen({ 0 / 255.0f,0 / 255.0f,0 / 255.0f,1 });
	//現在のシーンの描画処理
	//for (int i = (int)fpsObjects.size() - 1, j = 10, k = 1; i >= 0; --i, j *= 10, k *= 10)
	//{
	//	renderer->Render(&fpsObjects[i], numberTextures[(int)fps%j / k], &cbvSrvHeap);
	//}
	if (ctrler.CheckHitKey(XinputPadKey::XINPUT_B)) renderer->Render(&botanObj, botanTexture, &cbvSrvHeap);
	else renderer->Render(&botanObj, botanUpTexture, &cbvSrvHeap);
	sceneManager.DrawSprite();
	/*device.ClearDepthBuffer();*/
	sceneManager.Draw();
	device.ScreenFlip();
};