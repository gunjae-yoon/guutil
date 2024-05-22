#include <guutil/memory/impl/plain.h>
#include <cstdlib>
#include <iostream>

namespace guutil {
	Plain::Plain(uint64_t size) : MemoryManagerImpl(0) {
		// Note. ignore argument size
	}

	Plain::~Plain() {
	}

	void* Plain::allocate(const uint64_t size) {
		printf("Plain::allocate(%lu)\n", size);
		return malloc(size);
	}

	void Plain::deallocate(void* ptr) {
		printf("Buddy::deallocate(%p)\n", ptr);
		if (ptr == nullptr) {
			return;
		}
		
		free(ptr);
	}
}
