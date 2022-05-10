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
        static void trace(const string_view msg);
        static void info(const string_view msg);
        static void debug(const string_view msg);
        static void warning(const string_view msg);
        static void critical(const string_view msg);

    private:
        static constexpr const char* FILE_DIR = ".\\log";

        class impl;
        static std::unique_ptr<impl> impl_;
    };
}

#endif // LABDOG_LOGGER_HPP