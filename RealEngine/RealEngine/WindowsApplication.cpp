#include "WindowsApplication.h"
#include <tchar.h>
#include "InputManager.h"
#include "RealEngine.h"

using namespace RealEngine;

namespace RealEngine 
{
	WindowsApplication g_App;
	IApplication* g_pApp = &g_App;
}

struct Vertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
};

void RealEngine::WindowsApplication::CreateWindows()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = mhAppInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _T("RealEngine");

	RegisterClassEx(&wc);

	EConfig config;

	mhMainWnd = CreateWindowEx(0,
		_T(config.Name.c_str()),
		_T(config.Name.c_str()),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		config.Width,
		config.Height,
		NULL,
		NULL,
		mhAppInst,
		NULL);

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);
}

void RealEngine::WindowsApplication::CreateDXPipeline()
{
	UINT dxgiFactoryFlags = 0;

	// ����ʾ��ϵͳ�ĵ���֧��
#if defined(_DEBUG)
	{
		Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
	}
#endif

	//����DXGI Factory ����
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));
	// �ر�ALT+ENTER���л�ȫ���Ĺ��ܣ���Ϊ����û��ʵ��OnSize���������ȹر�
	ThrowIfFailed(factory->MakeWindowAssociation(mhMainWnd, DXGI_MWA_NO_ALT_ENTER));

	// ö������������ѡ����ʵ�������������3D�豸����
	{
		IDXGIAdapter1* pIAdapter1 = nullptr;
		DXGI_ADAPTER_DESC1 stAdapterDesc = {};
		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &pIAdapter1); ++adapterIndex)
		{
			pIAdapter1->GetDesc1(&stAdapterDesc);

			if (stAdapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{//������������������豸
				continue;
			}
			//�����������D3D֧�ֵļ��ݼ�������ֱ��Ҫ��֧��12.1��������ע�ⷵ�ؽӿڵ��Ǹ���������Ϊ��nullptr������
			//�Ͳ���ʵ�ʴ���һ���豸�ˣ�Ҳ�������ǆ��µ��ٵ���release���ͷŽӿڡ���Ҳ��һ����Ҫ�ļ��ɣ����ס��
			if (SUCCEEDED(D3D12CreateDevice(pIAdapter1, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
			{
				break;
			}
		}

		// ʹ�� D3D12CreateDevice �������� ID3D12Device,Device�ǿ����Ϊ���������Կ�
		// ����D3D12.1���豸���������������������豸��
		ThrowIfFailed(D3D12CreateDevice(pIAdapter1, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&pDevice)));
	}

	// �����������
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		ThrowIfFailed(pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue)));

		// �����������б������
		ThrowIfFailed(pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pCommandAllocator)));
	}

	// ����������
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.BufferCount = FRAME_BACK_BUFFER_COUNT;
		swapChainDesc.Width = 1920;
		swapChainDesc.Height = 1080;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.SampleDesc.Count = 1;
		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		ThrowIfFailed(factory->CreateSwapChainForHwnd(pCommandQueue.Get(), mhMainWnd, &swapChainDesc, nullptr, nullptr, &swapChain));
		ThrowIfFailed(swapChain.As(&pSwapChain));
		pFrameIndex = pSwapChain->GetCurrentBackBufferIndex();
	}
	
	// ���� RenderTargetView ��������(����ѵĺ���Ӧ�����Ϊ������߹̶���СԪ�صĹ̶���С�Դ��)
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = FRAME_BACK_BUFFER_COUNT;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&pRtvHeap)));

		//ȷ�ϸ�������������Ĵ�С
		//�����С�������������ǿ���֪������������ÿ��Ԫ�صĴ�С
		//����������Ҫ��������������:RTV����ȾĿ����ͼ��DSV(���ģ�建����ͼ) CbvSrvUav(�������壬��ɫ��Դ��ͼ�����������ͼ��
		pRtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// ����֡��Դ
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(pRtvHeap->GetCPUDescriptorHandleForHeapStart());

		// ������Ⱦ��ͼ
		for (UINT n = 0; n < FRAME_BACK_BUFFER_COUNT; n++)
		{
			ThrowIfFailed(pSwapChain->GetBuffer(n, IID_PPV_ARGS(&pRenderTargets[n])));
			pDevice->CreateRenderTargetView(pRenderTargets[n].Get(), nullptr, rtvHandle);
			rtvHandle.ptr += pRtvDescriptorSize;
		}
	}

	// ����Ƿ�֧��V1.1�汾�ĸ�ǩ��
	{
		D3D12_FEATURE_DATA_ROOT_SIGNATURE FeatureData = {};
		FeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;

		if (FAILED(pDevice->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &FeatureData, sizeof(FeatureData))))
		{
			FeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
		}
	}

	// ����һ���յĸ�ǩ��(�ø���ɫ��ʹ�õĲ���ǩ��)
	{
		D3D12_VERSIONED_ROOT_SIGNATURE_DESC RootSignatureDesc = {};
		RootSignatureDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
		RootSignatureDesc.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		RootSignatureDesc.Desc_1_1.NumParameters = 0;
		RootSignatureDesc.Desc_1_1.pParameters = nullptr;
		RootSignatureDesc.Desc_1_1.NumStaticSamplers = 0;
		RootSignatureDesc.Desc_1_1.pStaticSamplers = nullptr;

		Microsoft::WRL::ComPtr<ID3DBlob> signature;
		Microsoft::WRL::ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3D12SerializeVersionedRootSignature(&RootSignatureDesc, &signature, &error));
		ThrowIfFailed(pDevice->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&pRootSignature)));
	}

	// ������Ⱦ���߶���
	{
		Microsoft::WRL::ComPtr<ID3DBlob> VertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob> PixelShader;

#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif

		ThrowIfFailed(D3DCompileFromFile(L"../Resource/shaders/DX/shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &VertexShader, nullptr));
		ThrowIfFailed(D3DCompileFromFile(L"../Resource/shaders/DX/shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &PixelShader, nullptr));

		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC InputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { InputElementDescs, _countof(InputElementDescs) };
		psoDesc.pRootSignature = pRootSignature.Get();

		//psoDesc.VS = CD3DX12_SHADER_BYTECODE(VertexShader.Get());
		//psoDesc.PS = CD3DX12_SHADER_BYTECODE(PixelShader.Get());
		//psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		//psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

		psoDesc.VS.pShaderBytecode = VertexShader->GetBufferPointer();
		psoDesc.VS.BytecodeLength = VertexShader->GetBufferSize();

		psoDesc.PS.pShaderBytecode = PixelShader->GetBufferPointer();
		psoDesc.PS.BytecodeLength = PixelShader->GetBufferSize();

		psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;

		psoDesc.BlendState.AlphaToCoverageEnable = FALSE;
		psoDesc.BlendState.IndependentBlendEnable = FALSE;
		psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;

		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		ThrowIfFailed(pDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pPipelineState)));
	}

	// ���������б�
	ThrowIfFailed(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator.Get(), pPipelineState.Get(), IID_PPV_ARGS(&pCommandList)));
	ThrowIfFailed(pCommandList->Close());

	//�����Դ���Ͻṹ��Ϊ�����ѭ����׼����
	{
		BeginResBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		BeginResBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		BeginResBarrier.Transition.pResource = pRenderTargets[pFrameIndex].Get();
		BeginResBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		BeginResBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		BeginResBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		EndResBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		EndResBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		EndResBarrier.Transition.pResource = pRenderTargets[pFrameIndex].Get();
		EndResBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		EndResBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		EndResBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	}

	// ����һ��ͬ�����󡪡�Χ��
	{
		// Create synchronization objects and wait until assets have been uploaded to the GPU.
		ThrowIfFailed(pDevice->CreateFence(pFenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence)));
		pFenceValue++;

		//����һ��Eventͬ���������ڵȴ�Χ���¼�֪ͨ
		// Create an event handle to use for frame synchronization.
		pFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (pFenceEvent == nullptr)
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}

		// Wait for the command list to execute; we are reusing the same command 
		// list in our main loop but for now, we just want to wait for setup to 
		// complete before continuing.
		//��ʼͬ��GPU��CPU��ִ�У��ȼ�¼Χ�����ֵ
		//�����ͬ������һ��ѭ���ͻ�����Reset������������������ʱGPU��û��ִ��������͸�����ˣ��ͻ������

		// Schedule a Signal command in the queue.
		const UINT64 currentFenceValue = pFenceValue;
		ThrowIfFailed(pCommandQueue->Signal(pFence.Get(), currentFenceValue));


		// If the next frame is not ready to be rendered yet, wait until it is ready.
		if (pFence->GetCompletedValue() < pFenceValue)
		{
			ThrowIfFailed(pFence->SetEventOnCompletion(pFenceValue, pFenceEvent));
			WaitForSingleObjectEx(pFenceEvent, INFINITE, FALSE);
		}

		// Set the fence value for the next frame.
		pFenceValue = currentFenceValue + 1;
	}
}

void RealEngine::WindowsApplication::CreateDXAssets() 
{
	// ��������Buffer
	{
		// Define the geometry for a triangle.
		Vertex TriangleVertices[] =
		{
			{ { 0.0f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};
		UINT32 TriangleIndices[] = { 0,1,2 };

		// �������㻺��
		{
			const UINT VertexBufferSize = sizeof(TriangleVertices);

			D3D12_HEAP_PROPERTIES HeapProp = { D3D12_HEAP_TYPE_UPLOAD };
			D3D12_RESOURCE_DESC ResSesc = {};
			ResSesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			ResSesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			ResSesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			ResSesc.Format = DXGI_FORMAT_UNKNOWN;
			ResSesc.Width = VertexBufferSize;
			ResSesc.Height = 1;
			ResSesc.DepthOrArraySize = 1;
			ResSesc.MipLevels = 1;
			ResSesc.SampleDesc.Count = 1;
			ResSesc.SampleDesc.Quality = 0;

			ThrowIfFailed(pDevice->CreateCommittedResource(
				&HeapProp,
				D3D12_HEAP_FLAG_NONE,
				&ResSesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&pVertexBuffer)));

			// Copy the triangle data to the vertex buffer.
			UINT8* pVertexDataBegin;
			D3D12_RANGE readRange = { 0, 0 };        // We do not intend to read from this resource on the CPU.
			ThrowIfFailed(pVertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
			memcpy(pVertexDataBegin, TriangleVertices, sizeof(TriangleVertices));
			pVertexBuffer->Unmap(0, nullptr);

			// Initialize the vertex buffer view.
			pVertexBufferView.BufferLocation = pVertexBuffer->GetGPUVirtualAddress();
			pVertexBufferView.StrideInBytes = sizeof(Vertex);
			pVertexBufferView.SizeInBytes = VertexBufferSize;
		}

		// ������������
		{
			const UINT IndexBufferSize = sizeof(TriangleIndices);
			
			D3D12_HEAP_PROPERTIES HeapProp = { D3D12_HEAP_TYPE_UPLOAD };
			D3D12_RESOURCE_DESC ResDesc = {};
			ResDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			ResDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
			ResDesc.Width = IndexBufferSize;
			ResDesc.Height = 1;
			ResDesc.DepthOrArraySize = 1;
			ResDesc.MipLevels = 1;
			ResDesc.Format = DXGI_FORMAT_UNKNOWN;
			ResDesc.SampleDesc.Count = 1;
			ResDesc.SampleDesc.Quality = 0;
			ResDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			ResDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			
			// Note: using upload heaps to transfer static data like vert buffers is not 
			// recommended. Every time the GPU needs it, the upload heap will be marshalled 
			// over. Please read up on Default Heap usage. An upload heap is used here for 
			// code simplicity and because there are very few verts to actually transfer.
			ThrowIfFailed(pDevice->CreateCommittedResource(
				&HeapProp,
				D3D12_HEAP_FLAG_NONE,
				&ResDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&pIndexBuffer)));
			
			UINT8* pIndexDataBegin = nullptr;
			D3D12_RANGE stReadRange = { 0, 0 };		// We do not intend to read from this resource on the CPU.
			ThrowIfFailed(pIndexBuffer->Map(0, &stReadRange, reinterpret_cast<void**>(&pIndexDataBegin)));
			memcpy(pIndexDataBegin, TriangleIndices, IndexBufferSize);
			pIndexBuffer->Unmap(0, nullptr);
			
			pIndexBufferView.BufferLocation = pIndexBuffer->GetGPUVirtualAddress();
			pIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
			pIndexBufferView.SizeInBytes = IndexBufferSize;
		}
	}
}

void RealEngine::WindowsApplication::OnRender()
{
	//�����������Resetһ�£�����׼����������ĸ���̨������
	ThrowIfFailed(pCommandAllocator->Reset());
	 
	//Reset�����б�������ָ�������������PSO����
	ThrowIfFailed(pCommandList->Reset(pCommandAllocator.Get(), pPipelineState.Get()));

	//��ȡ�µĺ󻺳���ţ���ΪPresent�������ʱ�󻺳����ž͸�����
	pFrameIndex = pSwapChain->GetCurrentBackBufferIndex();

	// ͨ����Դ�����ж��󻺳��Ѿ��л���Ͽ��Կ�ʼ��Ⱦ��
	BeginResBarrier.Transition.pResource = pRenderTargets[pFrameIndex].Get();
	pCommandList->ResourceBarrier(1, &BeginResBarrier);

	// Set necessary state.
	pCommandList->SetGraphicsRootSignature(pRootSignature.Get());
	pCommandList->RSSetViewports(1, &pViewPort);
	pCommandList->RSSetScissorRects(1, &pScissorRect);


	//ƫ��������ָ�뵽ָ��֡������ͼλ��
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = pRtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (pFrameIndex * pRtvDescriptorSize);
	//������ȾĿ��
	pCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	// Draw!!!!!!!
	const float ClearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	pCommandList->ClearRenderTargetView(rtvHandle, ClearColor, 0, nullptr);
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pCommandList->IASetVertexBuffers(0, 1, &pVertexBufferView);
	pCommandList->IASetIndexBuffer(&pIndexBufferView);
	pCommandList->DrawIndexedInstanced(3, 1, 0, 0, 0);

	//��Դ���ϣ�����ȷ����Ⱦ�Ѿ����������ύ����ȥ��ʾ�ˣ��������Ϊ���ý�������ɽ�������ֹ��Դͬʱ����д�Ĵ������
	EndResBarrier.Transition.pResource = pRenderTargets[pFrameIndex].Get();
	pCommandList->ResourceBarrier(1, &EndResBarrier);

	//�ر������б�����ȥִ����
	ThrowIfFailed(pCommandList->Close());

	//ִ�������б�
	ID3D12CommandList* ppCommandLists[] = { pCommandList.Get() };
	pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// �ύ����
	ThrowIfFailed(pSwapChain->Present(1, 0));

	//��ʼͬ��GPU��CPU��ִ�У��ȼ�¼Χ�����ֵ
	//�����ͬ������һ��ѭ���ͻ�����Reset������������������ʱGPU��û��ִ��������͸�����ˣ��ͻ������
	// Schedule a Signal command in the queue.
	const UINT64 currentFenceValue = pFenceValue;
	ThrowIfFailed(pCommandQueue->Signal(pFence.Get(), currentFenceValue));

	// If the next frame is not ready to be rendered yet, wait until it is ready.
	if (pFence->GetCompletedValue() < pFenceValue)
	{
		ThrowIfFailed(pFence->SetEventOnCompletion(pFenceValue, pFenceEvent));
		WaitForSingleObjectEx(pFenceEvent, INFINITE, FALSE);
	}

	// Set the fence value for the next frame.
	pFenceValue = currentFenceValue + 1;
}

int RealEngine::WindowsApplication::Initialize()
{
	int result = BaseApplication::Initialize();

	if (result != 0) 
	{
		printf("WindowApplication:Initialize faild, will be exit.");
		exit(result);
	}

	this->CreateWindows();
	this->CreateDXPipeline();
	this->CreateDXAssets();

	return result;
}

void RealEngine::WindowsApplication::Finalize()
{
	BaseApplication::Finalize();

	//��ʼͬ��GPU��CPU��ִ�У��ȼ�¼Χ�����ֵ
	//�����ͬ������һ��ѭ���ͻ�����Reset������������������ʱGPU��û��ִ��������͸�����ˣ��ͻ������

	// Schedule a Signal command in the queue.
	const UINT64 currentFenceValue = pFenceValue;
	ThrowIfFailed(pCommandQueue->Signal(pFence.Get(), currentFenceValue));


	// If the next frame is not ready to be rendered yet, wait until it is ready.
	if (pFence->GetCompletedValue() < pFenceValue)
	{
		ThrowIfFailed(pFence->SetEventOnCompletion(pFenceValue, pFenceEvent));
		WaitForSingleObjectEx(pFenceEvent, INFINITE, FALSE);
	}

	// Set the fence value for the next frame.
	pFenceValue = currentFenceValue + 1;

	CloseHandle(pFenceEvent);
}

void RealEngine::WindowsApplication::Tick()
{
	//BaseApplication::Tick();

	this->OnRender();

	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK RealEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	InputManager& pManager = InputManager::getInstance();

	switch (message)
	{
	case WM_PAINT:
	{
			
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		BaseApplication::m_bQuit = true;

		return 0;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		pManager.InputKeyDown(wParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		pManager.InputKeyUp(wParam);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		pManager.InputKeyDown(wParam);
	}
	break;
	case WM_RBUTTONUP:
	{
		pManager.InputKeyUp(wParam);
	}
	break;
	case WM_KEYDOWN:
	{
		pManager.InputKeyDown(wParam);
	}
	break;
	case WM_KEYUP:
	{
		pManager.InputKeyUp(wParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		pManager.InputCursor(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	}
	break;
	case WM_MOUSEWHEEL:
	{
		printf("%hd\n", (int)GET_WM_VSCROLL_POS(wParam, lParam));
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}