#pragma once

#include <string>

namespace common {

enum class verbosity : unsigned char
{
    quiet    = 0,
    normal   = 1,
    verbose  = 2,
    all      = 3
};

enum class message_type : unsigned char
{
    INFO  = 0,
    WARN  = 1,
    ERROR = 2
};

inline std::string message_type_to_string(message_type msg_type)
{
    switch (msg_type) {
    case message_type::INFO:
        return "INFO";
    case message_type::WARN:
        return "WARNING";
    case message_type::ERROR:
    default:
        return "ERROR";
    }
}

} // end namespace common