#ifndef __guutil_log_stringify_h__
#define __guutil_log_stringify_h__

#include <guutil/log/kind.h>
#include <string>
#include <sstream>

namespace guutil {
	namespace log {
		namespace stringify {
			std::string getCurrentTimeAsString();
			
			template <typename... Args>
			std::string fatal(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [FATAL  ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string error(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [ERROR  ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string warning(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [WARNING] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string info(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [INFO   ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string debug(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [DEBUG  ] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string verbose(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [VERBOSE] [" << module << "]";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}

			template <typename... Args>
			std::string trace(const char* module, Args... args) {
				std::stringstream ss;
				ss << getCurrentTimeAsString() << " [TRACE  ] [" << module << "] ";
				auto insertWithSpace = [&ss](const auto& arg) { ss << ' ' << arg; };
				(insertWithSpace(args), ...);
				ss << std::endl;
				return ss.str();
			}
		}
	}
}

#endif
