#include <guutil/memory/impl/buddy.h>
#include <array>

using namespace guutil;

int main(int argc, char** argv) {
	Buddy buddy(1024);

	std::array<void*, 10> arr = {};
	for (void*& element : arr) {
		element = buddy.allocate(127);
	}
	for (void*& element : arr) {
		buddy.deallocate(element);
	}

	return 0;
}
