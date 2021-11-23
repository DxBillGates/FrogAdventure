#include "Dx12_Shader.h"
#include "COMRelease.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
Dx12_Shader::Dx12_Shader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	ID3DInclude* include = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	UINT flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	ID3DBlob* errorBlob = nullptr;
	HRESULT result;
	result = D3DCompileFromFile(vsFilename, nullptr, include, "main", "vs_5_0", flag, 0, &mVsBlob, &errorBlob);
	result = D3DCompileFromFile(psFilename, nullptr, include, "main", "ps_5_0", flag, 0, &mPsBlob, &errorBlob);
	COM_RELEASE(errorBlob);
}

Dx12_Shader::~Dx12_Shader()
{
	COM_RELEASE(mVsBlob);
	COM_RELEASE(mPsBlob);
}

ID3DBlob * Dx12_Shader::GetVsBlob()
{
	return mVsBlob;
}

ID3DBlob * Dx12_Shader::GetPsBlob()
{
	return mPsBlob;
}

