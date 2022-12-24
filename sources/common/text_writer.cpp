#include "text_writer.hpp"
#include "assert.hpp"
#include <iostream>

namespace common
{

    text_writer::text_writer(const std::string &filename)
        : warn_start_("<font color=#FF8C00>"), warn_end_("</font>"), error_start_("<b> <font color=#FF0000>"), error_end_("</font> </b>"), echo_start_("<font color=#0000FF>"), echo_end_("</font>"), bold_start_("<b>"), bold_end_("</b>"), file_name_(filename), file_(file_name_, std::ios::out)
    {
    }

    text_writer::~text_writer()
    {
        file_.close();
    }

    text_writer *text_writer::create_instance(const std::string &filename)
    {
        return new text_writer(filename);
    }

    void text_writer::write_message(message_type msg_type, const std::string &msg)
    {
        file_ << message_type_to_string(msg_type) << ' ' << msg << "\n" << std::flush;
    }

    void text_writer::write_command(const std::string &command)
    {
        file_ << command << "\n" << std::flush;
    }

    void text_writer::display_message(message_type msg_type, const std::string &msg)
    {
        switch (msg_type)
        {
        case message_type::INFO:
            display_info_message(msg);
            break;
        case message_type::WARN:
            display_warn_message(msg);
            break;
        case message_type::ERROR:
        default:
            display_error_message(msg);
        }
    }

    void text_writer::display_info_message(const std::string &msg)
    {
    }

    void text_writer::display_warn_message(const std::string &msg)
    {
    }

    void text_writer::display_error_message(const std::string &msg)
    {
    }

} // end of namespace common