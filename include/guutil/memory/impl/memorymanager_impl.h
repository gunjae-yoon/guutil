#ifndef __guutil_memory_impl_memory_manager_impl_h__
#define __guutil_memory_impl_memory_manager_impl_h__

#include <cstdint>
#include <guutil/log/logger.h>

namespace guutil {
	class MemoryManagerImpl {
	public:
		MemoryManagerImpl(const uint64_t size);
		virtual ~MemoryManagerImpl();
	
		virtual void* allocate(const uint64_t size) = 0;
		virtual void deallocate(void* ptr) = 0;

	protected:
		const uint64_t capacity;
		static log::Logger logger;
	};
}

#endif
