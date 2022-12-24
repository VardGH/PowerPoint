#pragma once
#include <string>

namespace commands {

class argument
{
public:
    argument(const std::string& name, const std::string& description);

    inline const std::string& name() const
    {
        return name_;
    }

    inline const std::string& description() const
    {
        return description_;
    }

private:
    std::string name_;
    std::string description_;
};

} // end of namespace commands