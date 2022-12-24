#include "parser.hpp"
#include "writer.hpp"
#include "commands/common.hpp"

#include <iostream>
#include <exception>

namespace {

const std::string whitespaces = " \t";
const std::string argument_marker = "--";

bool is_registered_type(const std::string& type_str)
{
    return (commands::type_from_string(type_str) != commands::type_t::UNKNOWN);
}

bool is_supported_key(const std::string& key)
{
    return (commands::shape_type_from_string(key) != commands::shape_type_t::UNKNOWN)
            || (commands::key_type_from_string(key) != commands::key_t::UNKNOWN);
}

} // unnamed namespace

namespace common {

parser &parser::get_instance()
{
    static parser instance;
    return instance;
}

void parser::parse(const std::string& input) const
{
    if (input.empty()) {
        return;
    }
    auto start_pos = input.find_first_not_of(whitespaces);
    if (start_pos == std::string::npos) {
        return;
    }
    auto end_pos = input.find_first_of(whitespaces, start_pos + 1);
    const std::string command_type = input.substr(start_pos, end_pos);
    std::cout << command_type << std::endl;
    if (is_registered_type(command_type)) {
        try {
            end_pos = input.find_first_not_of(whitespaces, end_pos);
            if (end_pos == std::string::npos) {
                common::writer::get_instance().write_message(common::message_type::ERROR, "missing parameters for command type: " + command_type);
            } else {
                extract_args(input.substr(end_pos));
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    } else {
        common::writer::get_instance().write_message(common::message_type::ERROR, "not supported command type: " + command_type);
    }
}

std::vector<std::string> parser::split(const std::string& text, const std::string& delims) const
{
    std::vector<std::string> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while((end = text.find_first_of(delims, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if(start != std::string::npos)
        tokens.push_back(text.substr(start));

    return tokens;
}

void parser::extract_args(const std::string& input) const
{
    auto arguments = split(input, "--");
    if (arguments.empty()) {
        common::writer::get_instance().write_message(common::message_type::ERROR, "missing arguments");
        return;
    }
    for (auto arg : arguments) {
        auto start_pos = arg.find_first_not_of(whitespaces);
        if (start_pos == std::string::npos) {
            common::writer::get_instance().write_message(common::message_type::ERROR, "missing argument key");
            return;
        }
        auto end_pos = arg.find_first_of(whitespaces, start_pos);
        std::string key = arg.substr(start_pos, end_pos - start_pos);
        if (end_pos == std::string::npos) {
            common::writer::get_instance().write_message(common::message_type::ERROR, "missing values for key " + key);
        }
        if (!is_supported_key(key)) {
            common::writer::get_instance().write_message(common::message_type::ERROR, "not supported key " + key);
            return;
        }
        if (commands::shape_type_from_string(key) != commands::shape_type_t::UNKNOWN) {
            continue;
        }
        auto values = split(arg.substr(end_pos), whitespaces);
        if (values.empty()) {
            common::writer::get_instance().write_message(common::message_type::ERROR, "missing values for key " + key);
        }
        for (auto value : values) {
            std::cout<< value << std::endl;
        }
    }
}

} // end of namespace common