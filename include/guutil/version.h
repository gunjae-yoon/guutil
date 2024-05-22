#ifndef __guutil_version_h__
#define __guutil_version_h__

#include <cstdint>
#include <string>

namespace guutil {
	namespace Version {
		extern const uint64_t major;
		extern const uint64_t minor;
		extern const uint64_t patch;

		extern const char* hashcode;
		extern const char* updated;

		extern const std::string full;
	}
}

#endif
