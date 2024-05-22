#ifndef __guutil_memory_impl_buddy_h__
#define __guutil_memory_impl_buddy_h__

#include <guutil/memory/memorymanager.h>

namespace guutil {
	class Buddy : public MemoryManager {
	private:
		struct Block {
			uint64_t size;
			bool free;
			Block* next;
		};

	public:
		Buddy(uint64_t size);
		~Buddy();

	private:
		void* _allocate(const uint64_t size) override;
		void _deallocate(void* ptr) override;

		Block* create(int8_t* base, uint64_t offset, const uint64_t size);
		Block* find(const uint64_t size);
		void split(Block* block, uint64_t size);
		void merge(Block* block);
		
	private:
		Block* head;
		int8_t* baseMemory;
	};
}

#endif
