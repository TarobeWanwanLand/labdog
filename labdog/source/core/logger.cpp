#include "labdog/core/logger.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace ld
{
    class logger::impl final
    {
    public:
        impl()
        {
            spdlog::sink_ptr logger_sinks[] {
                std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
                std::make_shared<spdlog::sinks::basic_file_sink_mt>("labdog.log", true)
            };

            logger_ = std::make_shared<spdlog::logger>(
                "logger", std::begin(logger_sinks), std::end(logger_sinks));
            logger_->set_level(spdlog::level::trace);
            logger_->flush_on(spdlog::level::trace);

            set_default_logger(logger_);
        }

        ~impl()
        {
            spdlog::shutdown();
        }

        spdlog::logger& get_logger() noexcept
        {
            return *logger_;
        }

    private:
        std::shared_ptr<spdlog::logger> logger_;
    };

    std::unique_ptr<logger::impl> logger::impl_{ std::make_unique<logger::impl>() };

    void logger::trace(const string_view msg)
    {
        spdlog::trace(std::string_view(
            reinterpret_cast<const char*>(msg.data()), msg.size()));
    }

    void logger::info(const string_view msg)
    {
        spdlog::info(std::string_view(
            reinterpret_cast<const char*>(msg.data()), msg.size()));
    }

    void logger::debug(const string_view msg)
    {
        spdlog::debug(std::string_view(
            reinterpret_cast<const char*>(msg.data()), msg.size()));
    }

    void logger::warning(const string_view msg)
    {
        spdlog::warn(std::string_view(
            reinterpret_cast<const char*>(msg.data()), msg.size()));
    }

    void logger::critical(const string_view msg)
    {
        spdlog::critical(std::string_view(
            reinterpret_cast<const char*>(msg.data()), msg.size()));
    }
}