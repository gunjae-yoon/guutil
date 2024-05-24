#include <guutil/log/logger.h>
#include <guutil/log/stringify.h>

namespace guutil {
	namespace log {
		Logger::Logger(const std::string modulename, const Level level, const Target output, const std::filesystem::path directory, const uint64_t limit) : module(modulename), lv(level), target(output), file(directory, stringify::getCurrentTimeForFile() + "__" + modulename, limit) {
		}

		Logger::~Logger() {
		}
	}
}
