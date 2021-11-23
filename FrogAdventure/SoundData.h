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
		char id[4];    //�`�����N��
		int32_t size;    //�`�����N�T�C�Y
	};

	//"RIFF" �`�����N�p
	struct RiffHeader
	{
		Chunk chunk;
		char type[4];    //RIFF�̃^�C�v
	};

	//"fmt "�`�����N�p
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
