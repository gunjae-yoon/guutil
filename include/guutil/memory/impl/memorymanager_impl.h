#ifndef __guutil_memory_impl_memory_manager_impl_h__
#define __guutil_memory_impl_memory_manager_impl_h__

#include <cstdint>

namespace guutil {
	class MemoryManagerImpl {
	public:
		MemoryManagerImpl(const uint64_t size);
		virtual ~MemoryManagerImpl();
	
		virtual void* allocate(const uint64_t size) = 0;
		virtual void deallocate(void* ptr) = 0;

	protected:
		const uint64_t capacity;
	};
}

#endif
