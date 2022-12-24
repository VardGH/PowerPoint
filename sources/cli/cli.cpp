#include "cli.hpp"

#include <common/parser.hpp>
#include <common/writer.hpp>
#include <iostream>

namespace
{
    const std::string close_command = std::string("quit");
    const std::string shorten_close_command = std::string("q");
}

namespace cli
{

cli &cli::get_instance()
{
    static cli instance;
    return instance;
}

void cli::start()
{
    std::cout << "starting cli" << std::endl;
    std::string line;

    do {
        std::cout << "power_point> ";
        std::getline(std::cin, line);
        if (line.empty()) {
            continue;
        }
        common::writer::get_instance().write_message(common::message_type::INFO, line);
        common::parser::get_instance().parse(line);
    } while (!(line == close_command || line == shorten_close_command));
}

void cli::stop()
{
    std::cout << "stoping cli" << std::endl;
}

} // end namespace cli