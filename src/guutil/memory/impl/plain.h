#ifndef __guutil_memory_impl_plain_h__
#define __guutil_memory_impl_plain_h__

#include <guutil/memory/impl/memorymanager_impl.h>

namespace guutil {
	class Plain : public MemoryManagerImpl {
	public:
		Plain(uint64_t size);
		~Plain();

	private:
		void* allocate(const uint64_t size) override;
		void deallocate(void* ptr) override;
	};
}

#endif
