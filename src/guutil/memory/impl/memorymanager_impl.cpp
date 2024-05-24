#include <guutil/memory/impl/memorymanager_impl.h>

namespace guutil {
	log::Logger MemoryManagerImpl::logger("memory", log::Level::ALL, log::Target::CONSOLE);

	MemoryManagerImpl::MemoryManagerImpl(const uint64_t size) : capacity(size) {
	}

	MemoryManagerImpl::~MemoryManagerImpl() {
	}
}
