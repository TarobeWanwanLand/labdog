# サンプルプログラム名
set(EXAMPLE_NAME "example")

# サンプルプログラムを作成
add_executable(${EXAMPLE_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/bar.cpp"
)

# ビルドタイプごとのポストフィックスを設定
set_target_properties(${EXAMPLE_NAME} PROPERTIES
    DEBUG_POSTFIX "-d"
    RELEASE_POSTFIX ""
    MINSIZEREL_POSTFIX "-mr"
    RELWITHDEBINFO_POSTFIX "-rd"
)

#find_package(GTest REQUIRED)
#find_package(Boost REQUIRED COMPONENTS system)

# ライブラリをリンク
target_link_libraries(${EXAMPLE_NAME} PRIVATE
    #${PROJECT_NAME}::${PROJECT_NAME}
    ${EXTERNAL_LIBRARIES}
)

# サンプルプログラムをインストール
install(
  TARGETS ${EXAMPLE_NAME}
  RUNTIME DESTINATION bin
)
