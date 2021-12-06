#ifndef __guutil_memory_memorymanager_impl_buddy_h__
#define __guutil_memory_memorymanager_impl_buddy_h__

#include <guutil/memory/memorymanager.h>
#include <guutil/thread/mutex.h>

namespace guutil {
	enum class ManagementKind {
		BEST_FIT,
		WORST_FIT,
		FIRST_FIT,
	};

	class BuddyNode {
	public:
		BuddyNode* less;
		BuddyNode* more;
		size_t linkedBlockCount;
		char mem[0];
	};

	class Buddy : public MemoryManager {
	private:
		size_t capacity;
		size_t minimumBlockSize;
		size_t maximumBlockCount;
		Mutex* mutex;
		void* memory;
		BuddyNode* freeBlockTree;
		ManagementKind kind;

	private:
		void* alloc(BuddyNode*& aNode, size_t aBlockCount);

	public:
		Buddy(size_t aMinBlockSize, size_t aBlockCountMultiplier, ManagementKind aKind);
		virtual ~Buddy(void);

		virtual bool initialize(void);

		virtual void* alloc(size_t aSize);
		virtual void* realloc(void* aMem, size_t aSize);
		virtual void free(void* aMem);

		virtual size_t getMaxSize(void);
	};
}

#endif
