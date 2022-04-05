# 外部ライブラリの更新
execute_process(COMMAND git submodule update --init --recursive)

# spdlogをビルド
set(SPDLOG_WCHAR_FILENAMES TRUE)
set(SPDLOG_WCHAR_SUPPORT TRUE)
add_subdirectory(spdlog)