#ifndef LABDOG_LOGGER_HPP
#define LABDOG_LOGGER_HPP

#include "common.hpp"
#include "string.hpp"
#include <memory>

namespace ld
{
    class logger final
    {
    public:
        static constexpr const char* FILE_DIR = ".\\log";

        static void trace(const string& msg);
        static void info(const string& msg);
        static void debug(const string& msg);
        static void warning(const string& msg);
        static void critical(const string& msg);

    private:
        class impl;
        static std::unique_ptr<impl> impl_;
    };
}

#endif // LABDOG_LOGGER_HPP