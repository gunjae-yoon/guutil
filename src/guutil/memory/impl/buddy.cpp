#include <guutil/memory/impl/buddy.h>
#include <cmath>
#include <iostream>

namespace guutil {
	Buddy::Buddy(uint64_t size) : MemoryManagerImpl(size) {
		logger.trace(__FUNCTION__, size);
		baseMemory = static_cast<int8_t*>(std::malloc(size));
		head = create(baseMemory, 0, size);
	}

	Buddy::~Buddy() {
		logger.trace(__FUNCTION__);
		std::free(baseMemory);
	}

	void* Buddy::allocate(const uint64_t size) {
		logger.trace(__FUNCTION__, size);
		const uint64_t blockSize = std::pow(2, std::ceil(std::log2(size))); // Note: round up to the nearest power of two
		Block* block = find(blockSize);
		if (block == nullptr) {
			logger.error("out of resources", "(failed to find free block)");
			return nullptr;
		}
		block->free = false;
		split(block, blockSize);
		return static_cast<void*>(block + 1);
	}

	void Buddy::deallocate(void* ptr) {
		logger.trace(__FUNCTION__, ptr);
		if (ptr == nullptr) {
			logger.error("invalid argument", "(tried to free nullptr)");
			return;
		}
		Block* block = static_cast<Block*>(ptr) - 1;
		block->free = true;
		merge(block);
	}

	Buddy::Block* Buddy::create(int8_t* base, const uint64_t offset, const uint64_t size) {
		logger.trace(__FUNCTION__, static_cast<void*>(base), offset, size);
		Block* block = reinterpret_cast<Block*>(base + offset);
		block->size = size;
		block->free = true;
		block->next = nullptr;
		return block;
	}

	Buddy::Block* Buddy::find(const uint64_t size) {
		logger.trace(__FUNCTION__, size);
		Block* current = head;
		while (current != nullptr) {
			if (current->free && current->size >= size) {
				logger.verbose("find free block", "( req:", size, "find:", current->size, ")");
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	void Buddy::split(Block* block, const uint64_t size) {
		logger.trace(__FUNCTION__, block, size);
		while (block->size > size) {
			uint64_t newSize = block->size / 2;
			Block* newBlock = create(baseMemory, reinterpret_cast<int8_t*>(block) - baseMemory + newSize, newSize);
			newBlock->next = block->next;
			block->next = newBlock;
			block->size = newSize;
		}
	}

	void Buddy::merge(Block* block) {
		logger.trace(__FUNCTION__, block);
		Block* current = head;
		while (current != nullptr) {
			if (current->free && current->next && current->next->free &&
				current->size == current->next->size) {
				current->size *= 2;
				Block* next = current->next;
				current->next = next->next;
			} else {
				current = current->next;
			}
		}
	}
}
