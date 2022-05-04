#include "labdog/core/logger.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <ranges>
#include <chrono>
#include <fstream>

namespace ld
{
    class logger::impl final
    {
    public:
        impl()
        {
            namespace fs = std::filesystem;
            namespace vs = std::views;
            namespace ch = std::chrono;

            const fs::path dir(FILE_DIR);
            if (!fs::is_directory(dir))
            {
                //INFO("�w�肳�ꂽ���O�i�[�p�̃f�B���N�g���͑��݂��܂���B�V���ɍ쐬���܂��B�p�X: {}", dir.string());
                fs::create_directory(dir);
            }

            if (std::vector logFiles(fs::directory_iterator(dir), {}); logFiles.size() >= MAX_FILE)
            {
                for (const auto& f : vs::counted(logFiles.begin(), logFiles.size() - (MAX_FILE - 1)))
                {
                    fs::remove(f);
                }
            }

            const auto now = ch::system_clock::now();
            const auto in_time_t = ch::system_clock::to_time_t(now);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
            auto a = ss.str();

            std::vector<spdlog::sink_ptr> loggerSink;
            loggerSink.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

            logger_ = std::make_shared<spdlog::logger>("logger", loggerSink.begin(), loggerSink.end());
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
        impl_->get_logger().trace(msg.to_multi_byte());
    }
}