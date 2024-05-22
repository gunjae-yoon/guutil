#include <guutil/memory/memorymanager.h>
#include <array>
#include <iostream>

using namespace guutil;

int main(int argc, char** argv) {
	MemoryManager mm(MMKind::BUDDY, 1024);

	std::array<void*, 10> arr = {};
	for (void*& element : arr) {
		element = mm.allocate(127);
	}
	for (void*& element : arr) {
		mm.deallocate(element);
	}

	return 0;
}
