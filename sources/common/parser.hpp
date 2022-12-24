#pragma once

#include <string>
#include <vector>

namespace common {

/**
 * @brief parser class is designed to get command line arguments and parse the commands and arguments
 * 
 */
class parser
{
public:
    static parser& get_instance();

    /**
     * @brief parse function to extract command line arguments
     * 
     */
    void parse(const std::string& input) const;

    ///@brief copy/move constructor and assignment deletion
    ///{
public:
    parser(const parser& other) = delete;
    parser(const parser&& other) = delete;

    parser& operator=(const parser& other) = delete;
    parser& operator=(const parser&& other) = delete;
    ///}

private:
    void extract_args(const std::string& input) const;
    std::vector<std::string> split(const std::string& text, const std::string& delims) const;

private:
    parser() = default;
};

} //end of namespace common