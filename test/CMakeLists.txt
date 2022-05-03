# テストプログラム名
set(TESTS_NAME "${PROJECT_NAME}_test")

# ヘッダとソースファイル
set(TESTS_SOURCES
    # ヘッダ
    "${CMAKE_CURRENT_SOURCE_DIR}/test.hpp"
    # ソース
    "${CMAKE_CURRENT_SOURCE_DIR}/string_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unicode_convert_test.cpp"
)

# テストプログラムを作成
add_executable(${TESTS_NAME} ${TESTS_SOURCES})

# ビルドタイプごとのポストフィックスを設定
set_target_properties(${TESTS_NAME} PROPERTIES
    DEBUG_POSTFIX "-d"
    RELEASE_POSTFIX ""
    MINSIZEREL_POSTFIX "-mr"
    RELWITHDEBINFO_POSTFIX "-rd"
)

# ライブラリをリンク
target_link_libraries(${TESTS_NAME} PRIVATE
    -static gcc stdc++ winpthread
    ${PROJECT_NAME}::${PROJECT_NAME}
    GTest::gmock
    GTest::gtest
    GTest::gmock_main
)

include(GoogleTest)
gtest_add_tests(TARGET ${TESTS_NAME})

# プログラムをインストール
install(
    TARGETS ${TESTS_NAME}
    RUNTIME DESTINATION bin
)