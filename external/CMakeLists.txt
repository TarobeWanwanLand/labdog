execute_process(COMMAND git submodule update --init --recursive)

set(SPDLOG_USE_STD_FORMAT TRUE)
add_subdirectory(spdlog)