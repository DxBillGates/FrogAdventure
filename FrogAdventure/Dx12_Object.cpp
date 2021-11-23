#include "Dx12_Object.h"

D3D12_VERTEX_BUFFER_VIEW * Dx12_Object::GetVBuffView()
{
	return &vbView;
}

D3D12_INDEX_BUFFER_VIEW * Dx12_Object::GetIBuffView()
{
	return &ibView;
}

int Dx12_Object::GetCBVNumber()
{
	return cbvNumber;
}

int Dx12_Object::GetIndexCount()
{
	return indexCount;
}
