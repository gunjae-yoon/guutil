#ifndef __guutil_io_file_h__
#define __guutil_io_file_h__

#include <string>
#include <sstream>
#include <mutex>
#include <filesystem>
#include <cstdint>

namespace guutil {
	class File {
	public:
		File(const std::filesystem::path directory, const std::string filename, const uint64_t maxsize = 0xffffffffffffffff);
		~File();

		void print(const std::string& value);
	
	private:
		std::filesystem::path path;
		std::filesystem::path dir;
		std::string name;
		const uint64_t limit;
		uint64_t count;
		std::mutex mutex;
	};
}

#endif
