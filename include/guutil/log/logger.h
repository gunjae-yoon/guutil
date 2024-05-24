#ifndef __guutil_log_logger_h__
#define __guutil_log_logger_h__

#include <guutil/log/kind.h>
#include <guutil/log/stringify.h>
#include <guutil/io/console.h>
#include <guutil/io/file.h>
#include <string>
#include <mutex>

namespace guutil {
	namespace log {
		class Logger {
		public:
			Logger(const std::string modulename, const Level level = Level::ALL, const Target output = Target::CONSOLE, const std::filesystem::path directory = (std::filesystem::current_path()/"log"), const uint64_t limit = 0xffffffffffffffff);
			~Logger();
			
			template <typename... Args> void fatal(Args... args);
			template <typename... Args> void error(Args... args);
			template <typename... Args> void warning(Args... args);
			template <typename... Args> void info(Args... args);
			template <typename... Args> void debug(Args... args);
			template <typename... Args> void verbose(Args... args);
			template <typename... Args> void trace(Args... args);
		
		private:
			const std::string module;
			Level lv;
			Target target;
			std::mutex mutex;
			File file;
		};
	}
}

namespace guutil {
	namespace log {
		template <typename... Args>
		void Logger::fatal(Args... args) {
			if (lv < Level::FATAL) {
				return;
			}
			std::string txt = stringify::fatal(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}

		template <typename... Args>
		void Logger::error(Args... args) {
			if (lv < Level::ERROR) {
				return;
			}
			std::string txt = stringify::error(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}

		template <typename... Args>
		void Logger::warning(Args... args) {
			if (lv < Level::WARNING) {
				return;
			}
			std::string txt = stringify::warning(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}

		template <typename... Args>
		void Logger::info(Args... args) {
			if (lv < Level::INFO) {
				return;
			}
			std::string txt = stringify::info(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}

		template <typename... Args>
		void Logger::debug(Args... args) {
			if (lv < Level::DEBUG) {
				return;
			}
			std::string txt = stringify::debug(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}

		template <typename... Args>
		void Logger::verbose(Args... args) {
			if (lv < Level::VERBOSE) {
				return;
			}
			std::string txt = stringify::verbose(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}

		template <typename... Args>
		void Logger::trace(Args... args) {
			if (lv < Level::TRACE) {
				return;
			}
			std::string txt = stringify::trace(module.c_str(), args...);
			if ((target & Target::CONSOLE) == Target::CONSOLE) {
				console::print(txt);
			}
			if ((target & Target::FILE) == Target::FILE) {
				file.print(txt);
			}
		}
	}
}

#endif
