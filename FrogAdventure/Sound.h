#pragma once
#include "SoundData.h"

class Sound : public IXAudio2VoiceCallback
{
private:
	static IXAudio2* xAudioEngine;
	static IXAudio2MasteringVoice* masterVoice;
	IXAudio2SourceVoice* sourceVoice;
	SoundData* pSoundData;
	bool isStart;
	bool isPlay;
	bool isEnd;
public:
	Sound(SoundData* soundData);
	~Sound();
	static void SetAudioEngine();
	void CreateVoice();
	void Start();
	bool GetIsStart();
	bool GetIsPlay();
	bool GetIsEnd();
private:
	void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
	STDMETHOD_(void, OnStreamEnd) (THIS) {};
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext)
	{
		isStart = true;
		isEnd = false;
	};
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
	{
		isStart = false;
		isEnd = true;
	};
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

//#pragma once
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <xaudio2.h>
//#include <mmsystem.h>
//
//struct Chunk
//{
//	char id[4];    //チャンク名
//	int32_t size;    //チャンクサイズ
//};
//
////"RIFF" チャンク用
//struct RiffHeader
//{
//	Chunk chunk;
//	char type[4];    //RIFFのタイプ
//};
//
////"fmt "チャンク用
//struct FormatChunk
//{
//	Chunk chunk;
//	WAVEFORMAT fmt;
//};
//
//struct FactChunk
//{
//	Chunk chunk;
//	int32_t size;
//};
//class Sound
//{
//private:
//	static IXAudio2* xAudioEngine;
//	static IXAudio2MasteringVoice* masterVoice;
//	IXAudio2SourceVoice* sourceVoice;
//	WAVEFORMATEX waveFormatEx;
//	XAUDIO2_BUFFER audioBuffer;
//	int second;
//	int count;
//	int mcount;
//	char* buffer;
//public:
//	Sound(const char* filepath, int second);
//	~Sound();
//	static void SetAudioEngine();
//	void Start();
//};
//
