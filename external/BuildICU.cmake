# ヘッダとソースのディレクトリ
set(ICU_COMMON_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/icu/icu4c/source")

file(GLOB ICU_COMMON_SOURCES
    "${ICU_COMMON_SOURCE_DIR}/common/*.cpp"
    "${ICU_COMMON_SOURCE_DIR}/stubdata/*.cpp"
)

file(GLOB ICU_COMMON_HEADERS
    "${ICU_COMMON_SOURCE_DIR}/common/*.h"
    "${ICU_COMMON_SOURCE_DIR}/stubdata/*.h"
)

add_library(icu_common ${ICU_COMMON_SOURCES})
add_library("icu::common" ALIAS icu_common)

# インクルードディレクトリを設定
target_include_directories(icu_common PUBLIC
    icu/icu4c/source/common
    icu/icu4c/source/common/unicode
    icu/icu4c/source/stubdata
)

# ソースファイルをライブラリに追加
target_sources(icu_common PRIVATE ${ICU_COMMON_SOURCES})

# インクルードディレクトリを設定
target_include_directories(icu_common PUBLIC
    $<BUILD_INTERFACE:"${ICU_COMMON_SOURCE_DIR}/common">
    $<BUILD_INTERFACE:"${ICU_COMMON_SOURCE_DIR}/stubdata">
    $<INSTALL_INTERFACE:"include/unicode">
)

target_compile_definitions(icu_common PUBLIC
    -DU_STATIC_IMPLEMENTATION=1
    -DPIC
    -DU_COMMON_IMPLEMENTATION
)

# icu_commonにはc++17では不正なnoexceptの使用があるため、代わりにc++14としてビルドする
set_target_properties(icu_common PROPERTIES CXX_STANDARD 14)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(icu_common
        PRIVATE
        -wd4267
        -wd4244
    )
endif()

# ヘッダファイルをインストール
install(
    FILES ${ICU_COMMON_HEADERS}
    DESTINATION "include/unicode"
)

# ライブラリをインストール
install(
    TARGETS icu_common
    EXPORT "icu_common_config"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    PUBLIC_HEADER DESTINATION "include/unicode"
)

# コンフィグファイルをインストール
install(EXPORT "icu_common_config"
    NAMESPACE "icu::"
    DESTINATION "lib/cmake/icu_common"
)