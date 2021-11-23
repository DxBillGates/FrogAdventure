#include "SoundData.h"

SoundData::SoundData(const char * filepath)
{
	using namespace std;
	RiffHeader riffHeader;
	FormatChunk fmtChunk;
	ListChunk listChunk;
	IgnrChunk ignrChunk;
	IsftChunk isftChunk;
	Chunk dataChunk;

	//-----�t�@�C���ǂݍ���-----
	ifstream file;
	file.open(filepath, ios_base::binary);
	if (file.fail())return;
	file.read((char*)&riffHeader, sizeof(riffHeader));    //RIFF�`�����N��ǂݍ���
	if (strncmp(riffHeader.chunk.id, "RIFF", 4) != 0)return;    //RIFF�̃^�C�v��WAVE����Ȃ���΃t�@�C���ǂݍ��ݏI��
	file.read((char*)&fmtChunk, sizeof(fmtChunk));
	if (strncmp(fmtChunk.chunk.id, "fmt ", 4) != 0)return;    //�`�����N����fmt ����Ȃ���΃t�@�C���ǂݍ��ݏI��
	file.read((char*)&dataChunk, sizeof(dataChunk));
	if (strncmp(dataChunk.id, "data", 4) != 0)
	{
		if (strncmp(dataChunk.id, "LIST", 4) != 0)
		{
			return;
		}
		else
		{
			listChunk.list.id[0] = dataChunk.id[0];
			listChunk.list.id[1] = dataChunk.id[1];
			listChunk.list.id[2] = dataChunk.id[2];
			listChunk.list.id[3] = dataChunk.id[3];
			listChunk.list.size = dataChunk.size;
			file.read((char*)&listChunk.format, sizeof(listChunk.format));

			file.read((char*)&ignrChunk.ignr, sizeof(ignrChunk.ignr));
			file.read((char*)&ignrChunk.format, ignrChunk.ignr.size);

			file.read((char*)&isftChunk.isft, sizeof(isftChunk.isft));
			file.read((char*)&isftChunk.data, isftChunk.isft.size);
			file.read((char*)&dataChunk, sizeof(dataChunk));
			if (strncmp(dataChunk.id, "data", 4) != 0)
			{
				return;
			}
		}
	}
	//�g�`�f�[�^�̓ǂݍ���
	buffer = new char[dataChunk.size];
	file.read(buffer, dataChunk.size);
	file.close();
	//--------------------------
	memcpy(&waveFormatEx, &fmtChunk.fmt, sizeof(fmtChunk.fmt));
	waveFormatEx.wBitsPerSample = waveFormatEx.nBlockAlign * 8 / waveFormatEx.nChannels;

	audioBuffer.pAudioData = (BYTE*)buffer;
	audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	audioBuffer.AudioBytes = dataChunk.size;
}

SoundData::~SoundData()
{
	delete buffer;
}

WAVEFORMATEX* SoundData::GetWaveFormatEx()
{
	return &waveFormatEx;
}

XAUDIO2_BUFFER* SoundData::GetAudioBuffer()
{
	return &audioBuffer;
}

char * SoundData::GetBuffer()
{
	return buffer;
}