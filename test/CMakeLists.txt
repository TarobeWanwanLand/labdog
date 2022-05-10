# テストプログラム名
set(TESTS_NAME "${PROJECT_NAME}_test")

# ヘッダとソースファイル
set(TESTS_SOURCES
    # ヘッダ
    "${CMAKE_CURRENT_SOURCE_DIR}/test.hpp"
    # ソース
    "${CMAKE_CURRENT_SOURCE_DIR}/string_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/charset_convert_test.cpp"
        ../labdog/include/labdog/core/event.hpp)

# テストプログラムを作成
add_executable(${TESTS_NAME} ${TESTS_SOURCES})

# ビルドタイプごとのポストフィックスを設定
set_target_properties(${TESTS_NAME} PROPERTIES
    DEBUG_POSTFIX "-d"
    RELEASE_POSTFIX ""
    MINSIZEREL_POSTFIX "-mr"
    RELWITHDEBINFO_POSTFIX "-rd"
)

# googletestを探す
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# ライブラリをリンク
target_link_libraries(${TESTS_NAME} PRIVATE
    ${PROJECT_NAME}::${PROJECT_NAME}
    ${EXTERNAL_LIBRARIES}
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