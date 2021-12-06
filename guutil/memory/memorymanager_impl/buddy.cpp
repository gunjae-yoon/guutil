#include <guutil/memory/memorymanager_impl/buddy.h>

#if defined(__linux__)
#include <stdlib.h>
#include <stdio.h>
#endif

namespace guutil {

	Buddy::Buddy(size_t aMinBlockSize, size_t aBlockCountMultiplier, ManagementKind aKind):MemoryManager() {
		minimumBlockSize = aMinBlockSize;
		maximumBlockCount = 1;
		for(size_t iMultiplier = 0; iMultiplier < aBlockCountMultiplier; iMultiplier++) {
			maximumBlockCount *= 2;
		}
		capacity = (minimumBlockSize + sizeof(BuddyNode)) * maximumBlockCount;
		memory = NULL;
		mutex = NULL;
		freeBlockTree = NULL;
		kind = aKind;
	}

	Buddy::~Buddy(void) {
		if(mutex != NULL) {
			delete(mutex);
		}
		if(memory != NULL) {
			free(memory);
		}
	}

	bool Buddy::initialize(void) {
		// step 1. create mutex
		mutex = Mutex::createInstance();
		if(mutex == NULL) {
			return false;
		}

		// step 2. allocate memory space
		mutex->lock();
		memory = malloc(capacity);
		if(memory == NULL) {
			mutex->unlock();
			return false;
		}

		// step 3. set tree node for free space
		freeBlockTree = (BuddyNode*)memory;
		freeBlockTree->linkedBlockCount = capacity / (minimumBlockSize + sizeof(BuddyNode));
		freeBlockTree->less = NULL;
		freeBlockTree->more = NULL;
		mutex->unlock();
		return true;
	}

	void* Buddy::alloc(BuddyNode*& aNode, size_t aBlockCount) {
		BuddyNode* block = NULL;
		if(aNode->linkedBlockCount < aBlockCount) {
			if(aNode->less != NULL) {
				block = (BuddyNode*)alloc(aNode->less, aBlockCount);
			}
			if(block == NULL && aNode->more != NULL) {
				block = (BuddyNode*)alloc(aNode->more, aBlockCount);
			}
		}
		else if(aNode->linkedBlockCount == aBlockCount) {
			block = aNode;

			BuddyNode* child = NULL;
			if(aNode->less != NULL && aNode->more != NULL) {
				child = aNode->less;
				while(child->more != NULL) {
					child = child->more;
				}
				child->more = aNode->more;
				aNode = child;
			}
			else if(aNode->less != NULL) {
				aNode = aNode->less;
			}
			else if(aNode->more != NULL) {
				aNode = aNode->more;
			}
			else {
				aNode = NULL;
			}
		}
		else {
			block = aNode;

			aNode = aNode + (aBlockCount * (minimumBlockSize + sizeof(BuddyNode)));
			aNode->linkedBlockCount -= aBlockCount;

			block->linkedBlockCount = aBlockCount;
		}

		// debugging message
		if(block != NULL) {
			printf("[DEBUG] allocated block count: %lu\n", block->linkedBlockCount);
		}
		return block;
	}

	void* Buddy::alloc(size_t aSize) {
		// step 1. check memory size
		if(aSize > (minimumBlockSize * maximumBlockCount)) {
			// condition. allocating size is larger than the total memory size
			printf("[ERROR] allocating size is larger than the total memroy size\n");
			return NULL;
		}

		// step 2. calculate allocation block count
		size_t blockCount = 0;
		if(aSize % minimumBlockSize > 0) {
			blockCount = (aSize / minimumBlockSize) + 1;
		}
		else {
			blockCount = (aSize / minimumBlockSize);
		}

		// step 3. find allocation block
		BuddyNode* allocatedBlock = NULL;
		mutex->lock();
		allocatedBlock = (BuddyNode*)alloc(freeBlockTree, blockCount);
		mutex->unlock();

		if(allocatedBlock != NULL) {
			return allocatedBlock->mem;
		}

		printf("[ERROR] alloc() returns nil\n");
		return NULL;
	}

	void* Buddy::realloc(void* aMem, size_t aSize) {
		if(aMem == NULL) {
			return NULL;
		}

		// step 1. spoil node pointer
		BuddyNode* node = (BuddyNode*)((char*)aMem - sizeof(BuddyNode));

		// step 2. check allocated memory block size
		if(aSize <= (node->linkedBlockCount * minimumBlockSize)) {
			return node->mem;
		}

		// step 3. realloc
		mutex->lock();
		switch(kind) {
			case ManagementKind::BEST_FIT:
				break;
			case ManagementKind::WORST_FIT:
				break;
			case ManagementKind::FIRST_FIT:
				break;
		}
		mutex->unlock();

		return NULL;
	}

	void Buddy::free(void* aMem) {
		if(aMem == NULL) {
			return;
		}

		// step 1. spoil node pointer
		BuddyNode* node = (BuddyNode*)((char*)aMem - sizeof(BuddyNode));

		mutex->lock();
		switch(kind) {
			case ManagementKind::BEST_FIT:
				break;
			case ManagementKind::WORST_FIT:
				break;
			case ManagementKind::FIRST_FIT:
				break;
		}
		mutex->unlock();
	}

	size_t Buddy::getMaxSize(void) {
		return capacity;
	}
}
