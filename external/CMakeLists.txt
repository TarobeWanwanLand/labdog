# 外部ライブラリの更新をプル
execute_process(COMMAND git submodule update --init --recursive)

# GoogleTestをビルド
set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
add_subdirectory(googletest)

# spdlogをビルド
set(SPDLOG_WCHAR_FILENAMES TRUE)
set(SPDLOG_WCHAR_SUPPORT TRUE)
add_subdirectory(spdlog)