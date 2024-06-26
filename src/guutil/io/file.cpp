#include <guutil/io/file.h>
#include <fstream>

namespace guutil {
	File::File(const std::filesystem::path directory, const std::string filename, const uint64_t maxsize) : 
		path(directory / (filename + ".txt")),
		dir(directory),
		name(filename),
		limit(maxsize),
		count(0) {
		if (std::filesystem::exists(directory) == false) {
			std::filesystem::create_directories(directory);
		}
		std::ofstream stream(path, std::ios::app);
		if (stream.is_open()) {
			stream.close();
		}
	}

	File::~File() {
		// Remove empty file
		std::uint64_t stored = std::filesystem::file_size(path);
		if (stored == 0) {
			std::filesystem::remove(path);
		}
	}

	void File::print(const std::string& value) {
		std::unique_lock<std::mutex> guard(mutex);

		if (value.length() > limit) {
			return;
		}

		std::uint64_t stored = std::filesystem::file_size(path);

		if ((stored + value.length()) < limit) {
			std::ofstream stream(path, std::ios::app);
			if (stream.is_open() == false) {
				return;
			}
			stream << value;
			stream.close();
		} else {
			path = dir / (name + std::to_string(++count) + ".txt");
			guard.unlock();
			print(value);
		}
	}
}
