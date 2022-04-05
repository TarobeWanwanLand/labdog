cmake_minimum_required(VERSION 3.9)

# プロジェクト名とバージョンの設定
project(labdog VERSION 1.0.0)

# vcpkgを利用するようにする
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
endif()

# 環境を構築
include(${PROJECT_SOURCE_DIR}/cmake/SetupEnvironment.cmake)

add_subdirectory(external)

set(SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/spdlog/include")
set(SPDLOG_LIBRARY spdlog::spdlog)

set(EXTERNAL_LIBS
    ${SPDLOG_LIBRARY}
)

set(EXTERNAL_INCLUDES
    ${SPDLOG_INCLUDE_DIR}
)

add_subdirectory(cmake/labdog)
add_subdirectory(example)