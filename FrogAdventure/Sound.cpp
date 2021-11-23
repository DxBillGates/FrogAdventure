#include "Sound.h"

IXAudio2* Sound::xAudioEngine = nullptr;
IXAudio2MasteringVoice* Sound::masterVoice = nullptr;

Sound::Sound(SoundData * soundData)
	:
	sourceVoice(nullptr),
	pSoundData(soundData),
	isStart(false),
	isPlay(false),
	isEnd(false)
{
	CreateVoice();
}

Sound::~Sound()
{
	//pSoundData = nullptr;
	if (sourceVoice != nullptr)sourceVoice->Stop();
}

void Sound::SetAudioEngine()
{
	XAudio2Create(&xAudioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR);
	xAudioEngine->CreateMasteringVoice(&masterVoice);
}

void Sound::CreateVoice()
{
	xAudioEngine->CreateSourceVoice(&sourceVoice, pSoundData->GetWaveFormatEx(), 0, 2.0f, &(*this));
}

void Sound::Start()
{
	if (!isStart)
	{
		isEnd = false;
		sourceVoice->SubmitSourceBuffer(pSoundData->GetAudioBuffer());
		sourceVoice->Start();
	}
}

bool Sound::GetIsStart()
{
	return isStart;
}

bool Sound::GetIsPlay()
{
	//再生開始がされていて停止していないならisPlayをtrueにする
	if (isStart && !isEnd)
	{
		isPlay = true;
	}
	else if (!isStart)
	{
		isPlay = false;
	}

	return isPlay;
}

bool Sound::GetIsEnd()
{
	return isEnd;
}

//#include "Sound.h"
//#pragma comment(lib,"xaudio2.lib")
//IXAudio2* Sound::xAudioEngine = nullptr;
//IXAudio2MasteringVoice* Sound::masterVoice = nullptr;
//
//Sound::Sound(const char * filepath, int second)
//{
//	using namespace std;
//	RiffHeader riffHeader;
//	FormatChunk fmtChunk;
//	Chunk dataChunk;
//
//	//-----ファイル読み込み-----
//	ifstream file;
//	file.open(filepath, ios_base::binary);
//	if (file.fail())return;
//	file.read((char*)&riffHeader, sizeof(riffHeader));    //RIFFチャンクを読み込む
//	if (strncmp(riffHeader.chunk.id, "RIFF", 4) != 0)return;    //RIFFのタイプがWAVEじゃなければファイル読み込み終了
//	file.read((char*)&fmtChunk, sizeof(fmtChunk));
//	if (strncmp(fmtChunk.chunk.id, "fmt ", 4) != 0)return;    //チャンク名がfmt じゃなければファイル読み込み終了
//	file.read((char*)&dataChunk, sizeof(dataChunk));
//	if (strncmp(dataChunk.id, "data", 4) != 0)return;    //チャンク名がdataじゃなければファイル読み込み終了
//	//波形データの読み込み
//	buffer = new char[dataChunk.size];
//	file.read(buffer, dataChunk.size);
//	file.close();
//	//--------------------------
//	memcpy(&waveFormatEx, &fmtChunk.fmt, sizeof(fmtChunk.fmt));
//	waveFormatEx.wBitsPerSample = waveFormatEx.nBlockAlign * 8 / waveFormatEx.nChannels;
//
//	HRESULT result = xAudioEngine->CreateSourceVoice(&sourceVoice, &waveFormatEx);
//	audioBuffer.pAudioData = (BYTE*)buffer;
//	audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
//	audioBuffer.AudioBytes = dataChunk.size;
//	this->second = second;
//}
//
//Sound::~Sound()
//{
//	sourceVoice->Stop();
//	delete[] buffer;
//}
//
//void Sound::SetAudioEngine()
//{
//	XAudio2Create(&xAudioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR);
//	xAudioEngine->CreateMasteringVoice(&masterVoice);
//}
//
//void Sound::Start()
//{
//	sourceVoice->SubmitSourceBuffer(&audioBuffer);
//	sourceVoice->Start();
//}
