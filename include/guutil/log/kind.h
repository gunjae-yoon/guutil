#ifndef __guutil_log_kind_h__
#define __guutil_log_kind_h__

#include <cstdint>
#include <iostream>

namespace guutil {
	namespace log {
		enum class Level : uint32_t {
			FATAL,
			ERROR,
			WARNING,
			INFO,
			DEBUG,
			VERBOSE,
			TRACE,
			ALL = 0xffffffff
		};
		
		enum class Target : uint32_t {
			FILE = 0x00000001,
			CONSOLE = 0x00000002,
			ALL = 0xffffffff
		};
		
		inline Target operator & (Target lhs, Target rhs) {
			return static_cast<Target>(
				static_cast<std::underlying_type_t<Target>>(lhs) &
				static_cast<std::underlying_type_t<Target>>(rhs)
			);
		}
	}
}

#endif
