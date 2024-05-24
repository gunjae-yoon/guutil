#include <guutil/memory/memorymanager.h>
#include <guutil/log/logger.h>
#include <array>
#include <iostream>

using namespace guutil;

int main(int argc, char** argv) {
	MemoryManager mm(MMKind::PLAIN, 1024);
	guutil::log::Logger logger("tester", log::Level::ALL, log::Target::ALL);

	std::array<void*, 10> arr = {};
	for (void*& element : arr) {
		element = mm.allocate(127);
		logger.info("log level info: ptr: ", element);
	}
	for (void*& element : arr) {
		logger.info("log level debug: ptr: ", element);
		mm.deallocate(element);
	}

	return 0;
}
