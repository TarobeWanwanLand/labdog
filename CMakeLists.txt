cmake_minimum_required(VERSION 3.9)

# プロジェクト名とバージョンの設定
project(labdog VERSION 1.0.0)

# C++バージョンを指定
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

# 環境を構築
include(${PROJECT_SOURCE_DIR}/cmake/SetupEnvironment.cmake)

# 外部ライブラリをビルド
add_subdirectory(external)

# spdlogの情報
set(SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/spdlog/include")
set(SPDLOG_LIBRARY spdlog::spdlog)

# 外部ライブラリのリスト
set(EXTERNAL_LIBS
    ${SPDLOG_LIBRARY}
)

# 外部ライブラリのインクルードディレクトリのリスト
set(EXTERNAL_INCLUDES
    ${SPDLOG_INCLUDE_DIR}
)

# ライブラリをビルド
add_subdirectory(cmake/labdog)

# サンプルをビルド
add_subdirectory(example)