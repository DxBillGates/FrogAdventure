#pragma once
#include<d3d12.h>
class Dx12_Shader
{
private:
	ID3DBlob* mVsBlob;
	ID3DBlob* mPsBlob;
public:
	Dx12_Shader(const wchar_t* vsFilename, const wchar_t* psFilename);
	~Dx12_Shader();
	ID3DBlob* GetVsBlob();
	ID3DBlob* GetPsBlob();
};

