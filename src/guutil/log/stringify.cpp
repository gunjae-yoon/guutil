#include <guutil/log/stringify.h>
#include <iostream>
#include <chrono>
#include <iomanip>

namespace guutil {
	namespace log {
		namespace stringify {
			std::string getCurrentTimeAsString() {
				// Get the current time point from system clock
    			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    			std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    			// Convert to time_t which is compatible with C-style time functions
    			std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    			// Convert to tm structure
    			std::tm now_tm;
				localtime_r(&now_time_t, &now_tm); // POSIX specific function
				
				// Format the time as a string
   				std::ostringstream oss;
   				oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
   				oss << '.' << std::setw(3) << std::setfill('0') << ms.count();
   				return oss.str();
			}
		}
	}
}
