#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <xaudio2.h>
#include <mmsystem.h>
class SoundData
{
private:
	WAVEFORMATEX waveFormatEx;
	XAUDIO2_BUFFER audioBuffer;
	char* buffer;
public:
	SoundData(const char* filepath);
	~SoundData();
	WAVEFORMATEX* GetWaveFormatEx();
	XAUDIO2_BUFFER* GetAudioBuffer();
	char* GetBuffer();
public:
	struct Chunk
	{
		char id[4];    //チャンク名
		int32_t size;    //チャンクサイズ
	};

	//"RIFF" チャンク用
	struct RiffHeader
	{
		Chunk chunk;
		char type[4];    //RIFFのタイプ
	};

	//"fmt "チャンク用
	struct FormatChunk
	{
		Chunk chunk;
		WAVEFORMAT fmt;
	};

	struct ListChunk
	{
		Chunk list;
		char format[4];
	};

	struct IsftChunk
	{
		Chunk isft;
		char data[128];
	};

	struct IgnrChunk
	{
		Chunk ignr;
		char format[128];
	};
};
