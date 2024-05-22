#ifndef __guutil_version_h__
#define __guutil_version_h__

#include <cstdint>
#include <string>

namespace guutil {
    namespace Version {
        static const uint64_t major;
        static const uint64_t minor;
        static const uint64_t patch;

        static const char* hashcode;
        static const char* updated;

        static const std::string full;
    }
}

#endif
