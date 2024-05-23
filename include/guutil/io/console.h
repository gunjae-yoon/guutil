#ifndef __guutil_io_console_h__
#define __guutil_io_console_h__

#include <string>
#include <sstream>
#include <mutex>

namespace guutil {
	class console {
	public:
		static console& getInstance();
		static void print(const std::string& value);
	
	private:
		console();
		~console();
	
	private:
		static console instance;
		static std::mutex mutex;
	};
}

#endif
