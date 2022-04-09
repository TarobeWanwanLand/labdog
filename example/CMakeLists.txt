# サンプル名
set(EXAMPLE_NAME "example")

# 実行ファイルを作成
add_executable(${EXAMPLE_NAME}
    bar.cpp
)

# ライブラリをリンク
target_link_libraries(${EXAMPLE_NAME} PRIVATE 
    "${PROJECT_NAME}::${LIBRARY_NAME}"
)

# インストール
install(
  TARGETS ${EXAMPLE_NAME}
  RUNTIME DESTINATION bin
)
