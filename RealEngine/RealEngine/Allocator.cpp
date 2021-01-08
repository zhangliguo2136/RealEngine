#include "Allocator.h"

RealEngine::Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment)
{
	m_szDataSize = data_size;
	m_szPageSize = page_size;

	// 数据大小是否超过最小块的大小
	size_t minimal_size = (sizeof(BlockHeader) > m_szDataSize) ? sizeof(BlockHeader) : m_szDataSize;

	//获得满足对齐要求的数据块最小尺寸
	m_szBlockSize =(minimal_size + alignment - 1)& ~(alignment - 1);

	// 块对齐所浪费的大小
	m_szAlignmentSize = m_szBlockSize - minimal_size;

	m_nBlockPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}

RealEngine::Allocator::~Allocator()
{
	PageHeader* pPage = m_pPageList;
	while (pPage) 
	{
		PageHeader* _p = pPage;
		pPage = pPage->pNext;

		delete[] reinterpret_cast<uint8_t*>(_p);
	}
	m_pPageList = nullptr;
	m_pFreeList = nullptr;

	m_nPages = 0;
	m_nBlocks = 0;
	m_nFreeBlocks = 0;
}

void* RealEngine::Allocator::Allocate()
{
	// 没有空闲内存
	if (!m_pFreeList) 
	{
		// 先申请一页
		PageHeader* pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);
		++m_nPages;

		m_nBlocks += m_nBlockPerPage;
		m_nFreeBlocks += m_nBlockPerPage;

		// 放入页链中
		if (m_pPageList)
		{
			pNewPage->pNext = m_pPageList;
		}
		m_pPageList = pNewPage;

		// 将页按块大小分开
		BlockHeader* pBlock = pNewPage->Blocks();
		for (uint32_t i = 0; i < m_nBlockPerPage; i++) 
		{
			pBlock->pNext = NextBlock(pBlock);
			pBlock = NextBlock(pBlock);
		}
		pBlock->pNext = nullptr;

		m_pFreeList = pNewPage->Blocks();
	}

	BlockHeader* freeBlock = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	--m_nFreeBlocks;

	return reinterpret_cast<void*>(freeBlock);
}

void RealEngine::Allocator::Free(void* p) 
{
	BlockHeader* pBlock = reinterpret_cast<BlockHeader*>(p);

	pBlock->pNext = m_pFreeList;
	m_pFreeList = pBlock;

	++m_nFreeBlocks;
}