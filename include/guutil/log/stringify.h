#ifndef __guutil_log_stringify_h__
#define __guutil_log_stringify_h__

#include <guutil/log/kind.h>
#include <string>
#include <sstream>

namespace guutil {
	namespace log {
		namespace stringify {
			std::string getCurrentTimeAsStringInMilliseconds();
			std::string getCurrentTimeAsStringInMicroseconds();
			std::string getCurrentTimeAsStringInNanoseconds();
			
			template <typename... Args>
			std::string fatal(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [FATAL  ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string error(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [ERROR  ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string warning(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [WARNING] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string info(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [INFO   ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string debug(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [DEBUG  ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string verbose(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [VERBOSE] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string trace(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsStringInMicroseconds() << " [TRACE  ] [" << module << "] ";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}
		}
	}
}

#endif
