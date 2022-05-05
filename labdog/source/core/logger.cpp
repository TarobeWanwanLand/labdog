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
            std::vector<spdlog::sink_ptr> logger_sinks;
            logger_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
            logger_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("labdog.log", true));

            logger_ = std::make_shared<spdlog::logger>("logger", logger_sinks.begin(), logger_sinks.end());
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

    void logger::trace(const string& msg)
    {
        spdlog::trace(msg.to_multi_byte());
    }

    void logger::info(const string &msg)
    {
        spdlog::info(msg.to_multi_byte());
    }

    void logger::debug(const string &msg)
    {
        spdlog::debug(msg.to_multi_byte());
    }

    void logger::warning(const string &msg)
    {
        spdlog::warn(msg.to_multi_byte());
    }

    void logger::critical(const string &msg)
    {
        spdlog::critical(msg.to_multi_byte());
    }
}