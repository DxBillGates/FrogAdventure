#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<vector>
#include<DirectXMath.h>
class Dx12_Device
{
private:
	D3D12_VIEWPORT	             mViewport;
	D3D12_RECT                   mRect;
	IDXGIFactory6*               mDxgiFactory;
	IDXGIAdapter*                mUseAdapter;
	std::vector<IDXGIAdapter*>   mEnumAdapter;
	ID3D12Device*                mDevice;
	ID3D12CommandAllocator*      mCmdAlloc;
	ID3D12GraphicsCommandList*   mCmdList;
	ID3D12CommandQueue*          mCmdQueue;
	IDXGISwapChain4*             mSwapChain;
	std::vector<ID3D12Resource*> mFrameBuff;
	ID3D12DescriptorHeap*        mRtvHeap;
	ID3D12Resource*              mDepthBuff;
	ID3D12DescriptorHeap*        mDsvHeap;
	ID3D12Fence*                 mFence;
	UINT64                       mFenceValue;
public:
	Dx12_Device(HWND hwnd, int width, int height);
	~Dx12_Device();
	void ClearScreen(DirectX::XMFLOAT4 color);
	void ClearDepthBuffer();
	void ScreenFlip();
	ID3D12Device*              GetDevice();
	ID3D12GraphicsCommandList* GetCmdList();
	void WaitExcuteCommand();
private:
	void SetViewport(int width, int height);
	void CreateDxgiFactory();
	void CreateDevice();
	void CreateCmdList();
	void CreateSwapChain(HWND hwnd);
	void CreateRtvHeap();
	void CreateDsvHeap();
	void CreateFence();
	void SetResourceBarrier(D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);
};

