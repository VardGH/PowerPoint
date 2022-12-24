#include "writer.hpp"
#include "text_writer.hpp"
#include "assert.hpp"

namespace common {

writer::writer()
    : log_writer_(text_writer::create_instance("power_point.log"))
    , jou_writer_(text_writer::create_instance("power_point.jou"))
{}

writer &writer::get_instance()
{
    static writer instance;
    return instance;
}

writer::~writer()
{
    delete log_writer_;
    delete jou_writer_;
}

void writer::write_message(message_type msg_type, const std::string& message)
{
    log_writer_->write_message(msg_type, message);
}

void writer::write_command(const std::string& command)
{
    jou_writer_->write_command(command);
}

} // end of namespace common