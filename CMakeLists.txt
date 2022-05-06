cmake_minimum_required(VERSION 3.7)

# プロジェクト
project(labdog VERSION 1.0.0)

# 環境を構築する
include(cmake/ProjectSetup.cmake)

# サブモジュールの外部ライブラリをビルド
add_subdirectory(external)

# サブディレクトリ
add_subdirectory(cmake/labdog)
add_subdirectory(example)
add_subdirectory(test)
