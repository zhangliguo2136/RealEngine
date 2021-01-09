#include "MemoryManager.h"
#include <new>
using namespace RealEngine;

namespace RealEngine
{
	static const uint32_t kBlockSizes[] =
	{
		// 4-increments
		4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
		52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,

		// 32-increments
		128, 160, 192, 224, 256, 288, 320, 352, 384,
		416, 448, 480, 512, 544, 576, 608, 640,

		// 64-increments
		704, 768, 832, 896, 960, 1024
	};

	// 页的大小
	static const uint32_t kPageSize = 8192;
	// 对齐大小
	static const uint32_t kAlignment = 4;

	static const uint32_t kNumBlockSizes = sizeof(kBlockSizes) / sizeof(kBlockSizes[0]);

	static const uint32_t kMaxBlockSize = kBlockSizes[kNumBlockSizes - 1];
}

Allocator* MemoryManager::m_pAllocator = nullptr;
size_t* MemoryManager::m_pBlockSizeLookup = nullptr;

int RealEngine::MemoryManager::Initialize() 
{
	static bool s_bInitialized = false;
	if (!s_bInitialized) {
		m_pBlockSizeLookup = new size_t[kMaxBlockSize + 1];
		size_t j = 0;

		for (size_t i = 0; i < kMaxBlockSize; i++) 
		{
			if (i > kBlockSizes[j]) ++j;

			m_pBlockSizeLookup[i] = j;
		}

		m_pAllocator = new Allocator[kNumBlockSizes];
		for (size_t i = 0; i < kNumBlockSizes; i++) 
		{
			m_pAllocator[i].Reset(kBlockSizes[i], kPageSize, kAlignment);
		}

		s_bInitialized = true;
	}

	return 0;
}

void RealEngine::MemoryManager::Finalize()
{
	delete[] m_pAllocator;
	delete[] m_pBlockSizeLookup;
}

void RealEngine::MemoryManager::Tick()
{

}

Allocator* RealEngine::MemoryManager::LookUpAllocator(size_t size)
{
	if (size <= kMaxBlockSize)
		return m_pAllocator + m_pBlockSizeLookup[size];
	else
		return nullptr;
}

void* RealEngine::MemoryManager::Allocate(size_t size)
{
	// 没有对应的分配器就使用系统的分配器
	Allocator* pAlloc = LookUpAllocator(size);
	if (pAlloc)
		return pAlloc->Allocate();
	else
		return malloc(size);
}

void RealEngine::MemoryManager::Free(void* p, size_t size) 
{
	Allocator* pAlloc = LookUpAllocator(size);
	if (pAlloc)
		pAlloc->Free(p);
	else
		free(p);
}

