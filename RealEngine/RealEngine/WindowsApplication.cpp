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

	// 打开显示子系统的调试支持
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

	//创建DXGI Factory 对象
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));
	// 关闭ALT+ENTER键切换全屏的功能，因为我们没有实现OnSize处理，所以先关闭
	ThrowIfFailed(factory->MakeWindowAssociation(mhMainWnd, DXGI_MWA_NO_ALT_ENTER));

	// 枚举适配器，并选择合适的适配器来创建3D设备对象
	{
		IDXGIAdapter1* pIAdapter1 = nullptr;
		DXGI_ADAPTER_DESC1 stAdapterDesc = {};
		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &pIAdapter1); ++adapterIndex)
		{
			pIAdapter1->GetDesc1(&stAdapterDesc);

			if (stAdapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{//跳过软件虚拟适配器设备
				continue;
			}
			//检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
			//就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！
			if (SUCCEEDED(D3D12CreateDevice(pIAdapter1, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
			{
				break;
			}
		}

		// 使用 D3D12CreateDevice 函数创建 ID3D12Device,Device是可理解为软件层面的显卡
		// 创建D3D12.1的设备，这里是真正创建出来设备。
		ThrowIfFailed(D3D12CreateDevice(pIAdapter1, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&pDevice)));
	}

	// 创建命令队列
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		ThrowIfFailed(pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pCommandQueue)));

		// 创建名命令列表分配器
		ThrowIfFailed(pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pCommandAllocator)));
	}

	// 创建交换链
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
	
	// 创建 RenderTargetView 堆描述符(这里堆的含义应当理解为数组或者固定大小元素的固定大小显存池)
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = FRAME_BACK_BUFFER_COUNT;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&pRtvHeap)));

		//确认各种描述符句柄的大小
		//这个大小的作用是让我们可以知道描述符堆中每个元素的大小
		//我们现在需要的描述符有三种:RTV（渲染目标视图）DSV(深度模板缓冲视图) CbvSrvUav(常量缓冲，着色资源视图和随机访问视图）
		pRtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// 创建帧资源
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(pRtvHeap->GetCPUDescriptorHandleForHeapStart());

		// 创建渲染视图
		for (UINT n = 0; n < FRAME_BACK_BUFFER_COUNT; n++)
		{
			ThrowIfFailed(pSwapChain->GetBuffer(n, IID_PPV_ARGS(&pRenderTargets[n])));
			pDevice->CreateRenderTargetView(pRenderTargets[n].Get(), nullptr, rtvHandle);
			rtvHandle.ptr += pRtvDescriptorSize;
		}
	}

	// 检测是否支持V1.1版本的根签名
	{
		D3D12_FEATURE_DATA_ROOT_SIGNATURE FeatureData = {};
		FeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;

		if (FAILED(pDevice->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &FeatureData, sizeof(FeatureData))))
		{
			FeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
		}
	}

	// 创建一个空的根签名(拿给着色器使用的参数签名)
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

	// 创建渲染管线对象
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

	// 创建命令列表
	ThrowIfFailed(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator.Get(), pPipelineState.Get(), IID_PPV_ARGS(&pCommandList)));
	ThrowIfFailed(pCommandList->Close());

	//填充资源屏障结构，为下面的循环所准备的
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

	// 创建一个同步对象——围栏
	{
		// Create synchronization objects and wait until assets have been uploaded to the GPU.
		ThrowIfFailed(pDevice->CreateFence(pFenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence)));
		pFenceValue++;

		//创建一个Event同步对象，用于等待围栏事件通知
		// Create an event handle to use for frame synchronization.
		pFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (pFenceEvent == nullptr)
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}

		// Wait for the command list to execute; we are reusing the same command 
		// list in our main loop but for now, we just want to wait for setup to 
		// complete before continuing.
		//开始同步GPU与CPU的执行，先记录围栏标记值
		//如果不同步，下一轮循环就会马上Reset命令分配器，而如果此时GPU还没有执行完命令就给清空了，就会出问题

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
	// 创建顶点Buffer
	{
		// Define the geometry for a triangle.
		Vertex TriangleVertices[] =
		{
			{ { 0.0f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};
		UINT32 TriangleIndices[] = { 0,1,2 };

		// 创建顶点缓冲
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

		// 创建索引缓冲
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
	//命令分配器先Reset一下，并且准备好输出到哪个后台缓冲区
	ThrowIfFailed(pCommandAllocator->Reset());
	 
	//Reset命令列表，并重新指定命令分配器和PSO对象
	ThrowIfFailed(pCommandList->Reset(pCommandAllocator.Get(), pPipelineState.Get()));

	//获取新的后缓冲序号，因为Present真正完成时后缓冲的序号就更新了
	pFrameIndex = pSwapChain->GetCurrentBackBufferIndex();

	// 通过资源屏障判定后缓冲已经切换完毕可以开始渲染了
	BeginResBarrier.Transition.pResource = pRenderTargets[pFrameIndex].Get();
	pCommandList->ResourceBarrier(1, &BeginResBarrier);

	// Set necessary state.
	pCommandList->SetGraphicsRootSignature(pRootSignature.Get());
	pCommandList->RSSetViewports(1, &pViewPort);
	pCommandList->RSSetScissorRects(1, &pScissorRect);


	//偏移描述符指针到指定帧缓冲视图位置
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = pRtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (pFrameIndex * pRtvDescriptorSize);
	//设置渲染目标
	pCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	// Draw!!!!!!!
	const float ClearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	pCommandList->ClearRenderTargetView(rtvHandle, ClearColor, 0, nullptr);
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pCommandList->IASetVertexBuffers(0, 1, &pVertexBufferView);
	pCommandList->IASetIndexBuffer(&pIndexBufferView);
	pCommandList->DrawIndexedInstanced(3, 1, 0, 0, 0);

	//资源屏障，用于确定渲染已经结束可以提交画面去显示了，这里就是为了让交换链完成交换，防止资源同时被读写的错误情况
	EndResBarrier.Transition.pResource = pRenderTargets[pFrameIndex].Get();
	pCommandList->ResourceBarrier(1, &EndResBarrier);

	//关闭命令列表，可以去执行了
	ThrowIfFailed(pCommandList->Close());

	//执行命令列表
	ID3D12CommandList* ppCommandLists[] = { pCommandList.Get() };
	pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// 提交画面
	ThrowIfFailed(pSwapChain->Present(1, 0));

	//开始同步GPU与CPU的执行，先记录围栏标记值
	//如果不同步，下一轮循环就会马上Reset命令分配器，而如果此时GPU还没有执行完命令就给清空了，就会出问题
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

	//开始同步GPU与CPU的执行，先记录围栏标记值
	//如果不同步，下一轮循环就会马上Reset命令分配器，而如果此时GPU还没有执行完命令就给清空了，就会出问题

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