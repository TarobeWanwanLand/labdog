cmake_minimum_required(VERSION 3.7)

# プロジェクト
project(labdog VERSION 1.0.0)

# 環境を構築する
include(cmake/ProjectSetup.cmake)

# 外部ライブラリをビルド
include(cmake/FindVulkan.cmake)
include(cmake/FindGLFW.cmake)
include(cmake/FindSpdlog.cmake)

# 外部ライブラリのインクルードディレクトリを設定
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${spdlog_INCLUDE_DIRS}
)

# 外部ライブラリをリンク
link_libraries(
    ${Vulkan_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${spdlog_LIBRARIES}
)

# サブモジュールの外部ライブラリをビルド
add_subdirectory(external)

# サブディレクトリ
add_subdirectory(cmake/labdog)
add_subdirectory(example)
add_subdirectory(test)
