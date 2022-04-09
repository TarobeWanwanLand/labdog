# 外部ライブラリの更新
execute_process(COMMAND git submodule update --init --recursive)

# GoogleTestをビルド
set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
add_subdirectory(googletest)

# spdlogをビルド
set(SPDLOG_USE_STD_FORMAT TRUE)
set(SPDLOG_WCHAR_FILENAMES TRUE)
set(SPDLOG_WCHAR_SUPPORT TRUE)
add_subdirectory(spdlog)