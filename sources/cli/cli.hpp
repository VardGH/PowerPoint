#pragma once

namespace cli {

/**
 * @brief cli class is designed to get command line arguments and interpriet as a commands in application
 * 
 */
class cli
{
public:
    static cli& get_instance();

    /**
     * @brief starts the cli engine
     * 
     */
    void start();

    /**
     * @brief stop the cli engine
     * 
     */
    void stop();

    ///@brief copy/move constructor and assignment deletion
    ///{
public:
    cli(const cli& other) = delete;
    cli(const cli&& other) = delete;

    cli& operator=(const cli& other) = delete;
    cli& operator=(const cli&& other) = delete;
    ///}

private:
    cli() = default;
};

} // end namespace cli