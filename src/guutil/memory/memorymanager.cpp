#include <guutil/memory/memorymanager.h>
#include <guutil/memory/memorymanager_impl/buddy.h>

namespace guutil {

	MemoryManager::MemoryManager(void) {
	}

	MemoryManager::~MemoryManager(void) {
	}

	bool MemoryManager::initialize(void) {
		return false;
	}

	void* MemoryManager::alloc(size_t aSize) {
		return NULL;
	}

	void* MemoryManager::realloc(void* aMem, size_t aSize) {
		return NULL;
	}

	void MemoryManager::free(void* aMem) {
	}

	size_t MemoryManager::getMaxSize(void) {
		return 0;
	}

	MemoryManager* MemoryManager::createInstance(MemoryManagerKind kind) {
		MemoryManager* newManager = NULL;

		// step 1. create new memroy manager instance
		switch(kind) {
			case MemoryManagerKind::BUDDY:
				newManager = new Buddy(1024, 17, ManagementKind::FIRST_FIT);	// 1,024(Bytes) * 2^17(Blocks) = 128(MB)
				break;
			default:
				newManager = NULL;
				break;
		}

		// step 2. initialize memory manager instance
		if(newManager != NULL) {
			if(newManager->initialize() == false) {
				// condition 2.1. initialization failed
				delete(newManager);
				newManager = NULL;
			}
		}

		return newManager;
	}

}
