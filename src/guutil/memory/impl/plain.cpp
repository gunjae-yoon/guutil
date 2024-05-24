#include <guutil/memory/impl/plain.h>
#include <cstdlib>
#include <iostream>

namespace guutil {
	Plain::Plain(uint64_t size) : MemoryManagerImpl(0) {
		logger.trace(__FUNCTION__, size);
		// Note. ignore argument size
	}

	Plain::~Plain() {
		logger.trace(__FUNCTION__);
	}

	void* Plain::allocate(const uint64_t size) {
		logger.trace(__FUNCTION__, size);
		return malloc(size);
	}

	void Plain::deallocate(void* ptr) {
		logger.trace(__FUNCTION__, ptr);
		if (ptr == nullptr) {
			logger.error("invalid argument", "(tried to free nullptr)");
			return;
		}
		
		free(ptr);
	}
}
