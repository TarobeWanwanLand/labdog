#include <labdog/foo.hpp>
#include <spdlog/spdlog.h>

void log(std::string_view msg)
{
	spdlog::default_logger()->info(msg);
}
