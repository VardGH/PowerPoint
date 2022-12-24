#pragma once

#include "common.hpp"
#include <string>
#include <vector>

namespace commands {

class argument;

class command
{
public:
    command(const std::string& name,
            const std::string& description,
            category_t cat = category_t::COMMAND_LINE,
            type_t tp = type_t::CREATE);

    virtual ~command();

    virtual bool execute() = 0;

    virtual const std::string& name() const;
    virtual const std::string& description() const;
    virtual type_t type() const;
    virtual category_t category() const;

    void add_argument(argument* arg);

private:
    std::string m_name;
    std::string m_description;
    category_t m_category;
    type_t m_type;

    std::vector<argument*> arguments_;
};

} // end namespace commands