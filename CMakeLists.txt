cmake_minimum_required(VERSION 3.7)

# Hunterを利用できるようにする
set(HUNTER_STATUS_DEBUG ON)
include(cmake/HunterGate.cmake)

set(HUNTER_ROOT "${CMAKE_SOURCE_DIR}/.hunter")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.24.2.tar.gz"
    SHA1 "17fd3b9f0b8c271eac9b71e30a6aa1b9fecab299"
    LOCAL
)

# プロジェクト
project(labdog VERSION 1.0.0)

# 環境を構築する
include(cmake/ProjectSetup.cmake)

hunter_add_package(Boost COMPONENTS system thread)
find_package(Boost CONFIG REQUIRED system thread)

find_package(Vulkan REQUIRED)

hunter_add_package(glfw)
find_package(glfw3 REQUIRED)

hunter_add_package(glm)
find_package(glm CONFIG REQUIRED)

hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)

hunter_add_package(spdlog)
find_package(spdlog CONFIG REQUIRED)

hunter_add_package(EnTT)
find_package(EnTT CONFIG REQUIRED)

# 外部ライブラリのリスト
set(EXTERNAL_LIBRARIES
    Boost::system
    Boost::thread
    Vulkan::Vulkan
    glfw
    glm
    fmt::fmt
    spdlog::spdlog
    EnTT::EnTT
)

# サブディレクトリ
add_subdirectory(cmake/labdog)
add_subdirectory(example)
add_subdirectory(test)