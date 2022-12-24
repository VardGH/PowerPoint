#include "command.hpp"
#include "argument.hpp"

namespace commands {

command::command(const std::string& name,
                const std::string& description,
                category_t category,
                type_t type)
        : m_name(name)
        , m_description(description)
        , m_category(category)
        , m_type(type)
{
}

command::~command()
{
    for (auto& iter : arguments_) {
        delete iter;
    }
}

const std::string& command::name() const
{
    return m_name;
}

const std::string& command::description() const
{
    return m_description;
}

type_t command::type() const
{
    return m_type;
}

category_t command::category() const
{
    return m_category;
}

void command::add_argument(argument* arg)
{
    arguments_.emplace_back(arg);
}

} // end namespace commands