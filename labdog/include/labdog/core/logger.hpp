#ifndef LABDOG_LOGGER_HPP
#define LABDOG_LOGGER_HPP

#include "common.hpp"
#include "string_view.hpp"
#include <memory>
#include <spdlog/spdlog.h>

namespace ld
{
    class logger final
    {
    public:
        static void trace(string_view msg);
        static void info(string_view msg);
        static void debug(string_view msg);
        static void warning(string_view msg);
        static void critical(string_view msg);

    private:
        class impl;
        static std::unique_ptr<impl> impl_;
    };
}

#endif // LABDOG_LOGGER_HPP