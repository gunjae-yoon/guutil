#ifndef __guutil_log_kind_h__
#define __guutil_log_kind_h__

#include <cstdint>

namespace guutil {
	namespace log {
		enum class Level : uint32_t {
			FATAL,
			ERROR,
			WARNING,
			INFO,
			DEBUG,
			VERBOSE,
			TRACE
		};
		
		enum class Target : uint32_t {
			FILE = 1,
			CONSOLE = 2,
			ALL = 3
		};
	}
}

#endif
