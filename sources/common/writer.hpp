#pragma once

#include "common.hpp"

#include <string>

namespace common {

class text_writer;

/**
 * @brief writer class is designed as a centralized system of data writing
 * 
 */
class writer
{
public:
    static writer& get_instance();

public:

    /**
     * @brief 
     * 
     * @param msg_type type of the message that needs to be written
     * @param message meddage body that will be written
     */
    void write_message(message_type msg_type, const std::string& message);

    /**
     * @brief 
     * 
     * @param command string interpreation of command ideally this is gonna be ostream operator overloaded in each comamnd
     */
    void write_command(const std::string& command);

    ///@brief copy/move constructor and assignment deletion
    ///{
public:
    writer(const writer& other) = delete;
    writer(const writer&& other) = delete;

    writer& operator=(const writer& other) = delete;
    writer& operator=(const writer&& other) = delete;
    ///}

    ~writer();

private:
    writer();

private:
    text_writer* log_writer_;
    text_writer* jou_writer_;
};

} //end of namespace common