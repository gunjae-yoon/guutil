#include <guutil/io/console.h>
#include <iostream>

namespace guutil {
	std::mutex console::mutex;
	console console::instance;

	console::console() {
	}

	console::~console() {
	}

	console& console::getInstance() {
		return instance;
	}

	void console::print(const std::string& value) {
		std::unique_lock<std::mutex> guard(mutex);
		std::cout << value;
	}
}
