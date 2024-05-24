#include <guutil/log/stringify.h>
#include <iostream>
#include <chrono>
#include <iomanip>

namespace guutil {
	namespace log {
		namespace stringify {
			std::string getCurrentTimeAsStringInMilliseconds() {
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

			std::string getCurrentTimeAsStringInMicroseconds() {
				// Get the current time point from system clock
    			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    			std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    			// Convert to time_t which is compatible with C-style time functions
    			std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    			// Convert to tm structure
    			std::tm now_tm;
				localtime_r(&now_time_t, &now_tm); // POSIX specific function
				
				// Format the time as a string
   				std::ostringstream oss;
   				oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
   				oss << '.' << std::setw(6) << std::setfill('0') << us.count();
   				return oss.str();
			}

			std::string getCurrentTimeAsStringInNanoseconds() {
				// Get the current time point from system clock
    			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    			std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;

    			// Convert to time_t which is compatible with C-style time functions
    			std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    			// Convert to tm structure
    			std::tm now_tm;
				localtime_r(&now_time_t, &now_tm); // POSIX specific function
				
				// Format the time as a string
   				std::ostringstream oss;
   				oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
   				oss << '.' << std::setw(9) << std::setfill('0') << ns.count();
   				return oss.str();
			}

			std::string getCurrentTimeForFile() {
				// Get the current time point from system clock
    			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    			// Convert to time_t which is compatible with C-style time functions
    			std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    			// Convert to tm structure
    			std::tm now_tm;
				localtime_r(&now_time_t, &now_tm); // POSIX specific function
				
				// Format the time as a string
   				std::ostringstream oss;
   				oss << std::put_time(&now_tm, "%Y-%m-%d__%H-%M-%S");
   				return oss.str();
			}
		}
	}
}
