#pragma once

#include "BaseApplication.h"

#include <windows.h>
#include <windowsx.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include <string>
#include <wrl.h>
#include <shellapi.h>

#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

namespace RealEngine {
	class WindowsApplication :public BaseApplication 
	{
	public:
		WindowsApplication()
			:BaseApplication() {};

		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

		static LRESULT CALLBACK WindowProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);

	private:
		void CreateWindows();

		void CreateDXPipeline();

		void CreateDXAssets();

	private:
		void OnRender();

	private:
		static const UINT FRAME_BACK_BUFFER_COUNT = 2;
		UINT pFrameIndex = 0;

		HANDLE pFenceEvent;
		UINT64 pFenceValue;
		Microsoft::WRL::ComPtr<ID3D12Fence> pFence;

	private:
		HINSTANCE mhAppInst = nullptr; // application instance handle
		HWND      mhMainWnd = nullptr; // main window handle

	private:
		Microsoft::WRL::ComPtr<ID3D12Device> pDevice;
		Microsoft::WRL::ComPtr<IDXGISwapChain3> pSwapChain;

		UINT pRtvDescriptorSize;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pRtvHeap;

		Microsoft::WRL::ComPtr<ID3D12Resource> pRenderTargets[FRAME_BACK_BUFFER_COUNT];

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> pCommandQueue;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> pCommandList;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> pCommandAllocator;

		Microsoft::WRL::ComPtr<ID3D12RootSignature> pRootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pPipelineState;

		Microsoft::WRL::ComPtr<ID3D12Resource> pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> pIndexBuffer;
		D3D12_VERTEX_BUFFER_VIEW pVertexBufferView;
		D3D12_INDEX_BUFFER_VIEW pIndexBufferView;

		// ◊ ‘¥∆¡’œ
		D3D12_RESOURCE_BARRIER BeginResBarrier = {};
		D3D12_RESOURCE_BARRIER EndResBarrier = {};

		D3D12_VIEWPORT	pViewPort = { 0.0f, 0.0f, static_cast<float>(1920), static_cast<float>(1080), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
		D3D12_RECT		pScissorRect = { 0, 0, static_cast<LONG>(1920), static_cast<LONG>(1080) };
	};
}


inline std::string HrToString(HRESULT hr)
{
	char s_str[64] = {};
	sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
	return std::string(s_str);
}

class HrException : public std::runtime_error
{
public:
	HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
	HRESULT Error() const { return m_hr; }
private:
	const HRESULT m_hr;
};

#define SAFE_RELEASE(p) if (p) (p)->Release()

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw HrException(hr);
	}
}