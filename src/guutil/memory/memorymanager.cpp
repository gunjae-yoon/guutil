#include <guutil/memory/memorymanager.h>
#include <guutil/memory/impl/buddy.h>

namespace guutil {
	MemoryManager::MemoryManager(const MMKind kind, const uint64_t size) {
		switch (kind) {
		case MMKind::PLAIN:
			break;
		case MMKind::BUDDY:
			impl = std::make_unique<Buddy>(size);
			break;
		default:
			break;
		}
	}

	MemoryManager::~MemoryManager() {
		std::unique_lock<std::mutex> guard(mutex);
		impl.reset();
	}

	void* MemoryManager::allocate(const uint64_t size) {
		std::unique_lock<std::mutex> guard(mutex);
		return impl->allocate(size);
	}

	void MemoryManager::deallocate(void* ptr) {
		std::unique_lock<std::mutex> guard(mutex);
		impl->deallocate(ptr);
	}
}
