# サンプル名
set(TESTS_NAME "test")

# リンクするライブラリのリスト
set(TESTS_LIBS
    "${PROJECT_NAME}::${LIBRARY_NAME}"
    GTest::gmock
    GTest::gtest
    GTest::gmock_main
)

# 外部ライブラリのインクルードディレクトリのリスト
set(TESTS_INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/external/spdlog/include"
    "${CMAKE_SOURCE_DIR}/external/googletest/googletest/include"
    "${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include"
)

message("dirs : ${TESTS_INCLUDE_DIRS}")

# 実行ファイルを作成
add_executable(${TESTS_NAME}
    "test.cpp"
)

# ライブラリをリンク
target_link_libraries(${TESTS_NAME} PRIVATE 
    ${TESTS_LIBS}
)

# インクルードディレクトリをセット
target_include_directories(${TESTS_NAME} PUBLIC
    ${TESTS_INCLUDE_DIRS}
)

# GoogleTestの各テストケースごとにテストを作成する
include(GoogleTest)
gtest_add_tests(TARGET ${TESTS_NAME})

# インストール
install(
  TARGETS ${EXAMPLE_NAME}
  RUNTIME DESTINATION bin
)
