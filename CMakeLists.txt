cmake_minimum_required(VERSION 3.21)

# プロジェクト
project(labdog VERSION 1.0.0)

# 環境を構築する
include(cmake/environment_setting.cmake)

# 外部ライブラリをビルド
add_subdirectory(external)

# サブディレクトリ
add_subdirectory(cmake/labdog)
add_subdirectory(test)