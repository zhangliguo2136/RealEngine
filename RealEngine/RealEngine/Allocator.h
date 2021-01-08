#pragma once
#include <cstddef>
#include <cstdint>

namespace RealEngine 
{
	struct BlockHeader{
		BlockHeader *pNext;
	};
	struct PageHeader {
		PageHeader *pNext;
		/*
		在这里this的类型是PageHeader，
		所以this+1就是跳过PageHeader，
		指向PageHeader之后的第一个字节，
		也就是这个Page当中第一个Block开始的地方。
		然后将指针强制转换成BlockHeader*类型返回。
		函数整体到功能就是返回当前Page当中第一个Block开始的地址
		*/
		BlockHeader* Blocks() {
			return reinterpret_cast<BlockHeader*>(this + 1);
		}
	};

	class Allocator 
	{
	public:
		Allocator(size_t data_size, size_t page_size, size_t alignment);
		~Allocator();


		void* Allocate();
		void Free(void* p);
	private:
		BlockHeader* NextBlock(BlockHeader* pBlock);

		PageHeader* m_pPageList;
		BlockHeader* m_pFreeList;

		// 总体数据的大小
		size_t m_szDataSize;
		// 页的大小
		size_t m_szPageSize;
		// 对齐的大小
		size_t m_szAlignmentSize;

		// block 的大小
		size_t m_szBlockSize;
		// 平均每个page 的大小
		size_t m_nBlockPerPage;

		// 总页数
		uint32_t m_nPages;
		// 总块数
		uint32_t m_nBlocks;
		// 空闲的块数
		uint32_t m_nFreeBlocks;

		Allocator(const Allocator& clone) = delete;
		Allocator& operator = (const Allocator &rhs) = delete;
	};
}