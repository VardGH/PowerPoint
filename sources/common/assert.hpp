#pragma once

#ifdef AL_ASSERTIONS

#include <cassert>
#include <exception>
#include <string>

namespace common {

class fatal_exception: public std::exception {
public:
    fatal_exception(const std::string what, const std::string& file, int line)
        : what_{std::string("Assertion Failed: ") + what + "\nFile: " + file + "\nLine: " + std::to_string(line)}
    {}

    const char* what() const noexcept override
    {
        return what_.c_str();
    }

private:
    std::string what_;
};

} // end of namespace common

#define ASSERT_MESSAGE(expression, message) \
if (!(expression)) { \
    throw common::fatal_exception((message), __FILE__, __LINE__); \
}

#else
    #define ASSERT_MESSAGE(expression, message) \
        (void)0
#endif