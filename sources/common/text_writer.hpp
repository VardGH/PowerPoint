#pragma once

#include "common.hpp"

#include <fstream>
#include <iomanip>

namespace common
{

class text_writer
{
public:
    // static text_writer& get_instance();
    static text_writer* create_instance(const std::string& filename);

    ~text_writer();

public:
    void write_message(message_type msg_type, const std::string& msg);
    void write_command(const std::string& command);

    void display_message(message_type msg_type, const std::string& msg);

private:
	//! display info message
	virtual void display_info_message(const std::string& msg);

	//! display warning message
	virtual void display_warn_message(const std::string& msg);

	//! display error message
	virtual void display_error_message(const std::string& msg);

    ///@brief copy/move constructor and assignment deletion
    ///{
public:
    text_writer(const text_writer& other) = delete;
    text_writer(const text_writer&& other) = delete;

    text_writer& operator=(const text_writer& other) = delete;
    text_writer& operator=(const text_writer&& other) = delete;
    ///}

private:
    text_writer(const std::string& filename);

/// @brief more advanced logging options
/// {
private:
    std::string warn_start_;
	std::string warn_end_;

	std::string error_start_;
	std::string error_end_;

	std::string echo_start_;
	std::string echo_end_;

	std::string bold_start_;
	std::string bold_end_;
/// }

private:
    std::string file_name_;
    std::ofstream file_;
};


} // end of namespace common