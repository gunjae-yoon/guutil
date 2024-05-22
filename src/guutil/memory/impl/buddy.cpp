#include <guutil/memory/impl/buddy.h>
#include <cmath>
#include <iostream>

Buddy::Buddy(uint64_t size) : MemoryManager(size) {
	printf("Buddy::Buddy(%lu)\n", size);
	baseMemory = static_cast<int8_t*>(std::malloc(size));
	head = create(baseMemory, 0, size);
}

Buddy::~Buddy() {
	std::unique_lock<std::mutex> guard(mutex);
	std::free(baseMemory);
}

void* Buddy::_allocate(const uint64_t size) {
	printf("Buddy::_allocate(%lu)\n", size);
	const uint64_t blockSize = std::pow(2, std::ceil(std::log2(size))); // Note: round up to the nearest power of two
	Block* block = find(blockSize);
	if (block == nullptr) {
		return nullptr;
	}
	block->free = false;
	split(block, blockSize);
	return static_cast<void*>(block + 1);
}

void Buddy::_deallocate(void* ptr) {
	printf("Buddy::_deallocate(%p)\n", ptr);
	if (ptr == nullptr) {
		return;
	}
	Block* block = static_cast<Block*>(ptr) - 1;
	block->free = true;
	merge(block);
}

Buddy::Block* Buddy::create(int8_t* base, uint64_t offset, const uint64_t size) {
	printf("Buddy::create(%lu)\n", size);
	Block* block = reinterpret_cast<Block*>(base + offset);
	block->size = size;
	block->free = true;
	block->next = nullptr;
	return block;
}

Buddy::Block* Buddy::find(const uint64_t size) {
	printf("Buddy::find(%lu)\n", size);
	Block* current = head;
	while (current != nullptr) {
		if (current->free && current->size >= size) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

void Buddy::split(Block* block, uint64_t size) {
	printf("Buddy::split(%p, %lu)\n", block, size);
	while (block->size > size) {
		uint64_t newSize = block->size / 2;
		Block* newBlock = create(baseMemory, reinterpret_cast<int8_t*>(block) - baseMemory + newSize, newSize);
		newBlock->next = block->next;
		block->next = newBlock;
		block->size = newSize;
	}
}

void Buddy::merge(Block* block) {
	printf("Buddy::merge(%p)\n", block);
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
