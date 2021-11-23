#pragma once
#include<d3d12.h>
class Dx12_Object
{
protected:
	ID3D12Resource* vBuff;
	ID3D12Resource* iBuff;
	ID3D12Resource* cBuff;
	D3D12_VERTEX_BUFFER_VIEW vbView;
	D3D12_INDEX_BUFFER_VIEW ibView;
	int cbvNumber;
	int indexCount;
public:
	D3D12_VERTEX_BUFFER_VIEW* GetVBuffView();
	D3D12_INDEX_BUFFER_VIEW* GetIBuffView();
	int GetCBVNumber();
	int GetIndexCount();
};

