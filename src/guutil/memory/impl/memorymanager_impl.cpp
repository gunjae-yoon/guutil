#include <guutil/memory/impl/memorymanager_impl.h>

namespace guutil {
	MemoryManagerImpl::MemoryManagerImpl(const uint64_t size) : capacity(size) {
	}

	MemoryManagerImpl::~MemoryManagerImpl() {
	}
}
