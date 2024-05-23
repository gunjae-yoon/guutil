#include <guutil/log/logger.h>
#include <guutil/log/stringify.h>

namespace guutil {
	namespace log {
		Logger::Logger(const std::string modulename, const Level level, const Target output) : module(modulename), lv(level), target(output) {
		}

		Logger::~Logger() {
		}
	}
}
