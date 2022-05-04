# spdlog_FOUND
# spdlog_INCLUDE_DIRS
# spdlog_LIBRARIES

include(FindPackageMessage)
include(FindPackageHandleStandardArgs)

find_path(spdlog_INCLUDE_DIRS
    NAMES spdlog/spdlog.h
    PATHS
        "${spdlog_INCLUDE_DIR}"
        "${spdlog_ROOT}/include"
        "$ENV{spdlog_INCLUDE_DIR}"
        "$ENV{spdlog_ROOT}/include"
)

find_library(spdlog_LIBRARIES
    NAMES spdlog
    PATHS
        "${spdlog_LIBRARY_DIR}"
        "${spdlog_ROOT}/lib"
        "$ENV{spdlog_LIBRARY_DIR}"
        "$ENV{spdlog_ROOT}/lib"
)

find_package_handle_standard_args(spdlog DEFAULT_MSG spdlog_INCLUDE_DIRS spdlog_LIBRARIES)
mark_as_advanced(spdlog_INCLUDE_DIRS spdlog_LIBRARIES)

message(STATUS "spdlog_FOUND = ${spdlog_FOUND}")
message(STATUS "spdlog_INCLUDE_DIRS = ${spdlog_INCLUDE_DIRS}")
message(STATUS "spdlog_LIBRARIES = ${spdlog_LIBRARIES}")