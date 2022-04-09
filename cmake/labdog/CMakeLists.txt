set(LABDOG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(LABDOG_HEADER_DIR "${CMAKE_SOURCE_DIR}/include")

# ソースファイル
set(LABDOG_SOURCES
    "${LABDOG_SOURCE_DIR}/log.cpp"
)

# 公開するヘッダファイル
set(LABDOG_HEADERS_PUBLIC
    "${LABDOG_HEADER_DIR}/labdog/core/common.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/platform.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/primitive_type.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/string.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/string_view.hpp"
    "${LABDOG_HEADER_DIR}/labdog/logging/log.hpp"
    "${LABDOG_HEADER_DIR}/labdog/math/scalar.hpp"
    "${LABDOG_HEADER_DIR}/labdog/memory/alignment.hpp"
    "${LABDOG_HEADER_DIR}/labdog/util/assert.hpp"
)

# 非公開のヘッダファイル
set(LABDOG_HEADERS_PRIVATE
    "${LABDOG_HEADER_DIR}/labdog/core/detail/string.ipp"
    "${LABDOG_HEADER_DIR}/labdog/core/detail/string_view.ipp"
    "${LABDOG_HEADER_DIR}/labdog/memory/detail/alignment.ipp"
)

# 外部ライブラリのリスト
set(LABDOG_EXTERNAL_LIBS
    spdlog::spdlog
)

# 外部ライブラリのインクルードディレクトリのリスト
set(LADOG_EXTERNAL_INCLUDES
    "${CMAKE_SOURCE_DIR}/external/spdlog/include"
)

# ライブラリを作成
add_library(${LIBRARY_NAME}
    ${LABDOG_SOURCES}
    ${LABDOG_HEADERS_PUBLIC}
    ${LABDOG_HEADERS_PRIVATE}
)

# ライブラリの別名を定義
add_library(${PROJECT_NAME}::${LIBRARY_NAME} 
    ALIAS ${LIBRARY_NAME}
)

# CMakeの生成ヘッダのディレクトリ
set(LABDOG_GENERATED_HEADER_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/header"
)

# version.hppを作成
configure_file(
    "${LABDOG_HEADER_DIR}/labdog/version.hpp.in"
    "${LABDOG_GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/version.hpp"
    @ONLY
)

# export.hppを作成
include("GenerateExportHeader")
generate_export_header(${LIBRARY_NAME})
file(RENAME 
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_export.h"
    "${LABDOG_GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/export.hpp"
)

# DEBUGプリプロセッサマクロの定義
target_compile_definitions(${LIBRARY_NAME} PUBLIC
    "${PROJECT_NAME_UPPERCASE}_DEBUG=$<CONFIG:Debug>"
)

# インクルードディレクトリを設定
target_include_directories(${LIBRARY_NAME} PUBLIC
    "$<BUILD_INTERFACE:${LABDOG_HEADER_DIR}>"
    "$<BUILD_INTERFACE:${LADOG_EXTERNAL_INCLUDES}>"
    "$<BUILD_INTERFACE:${LABDOG_GENERATED_HEADER_DIR}>"
    "$<INSTALL_INTERFACE:.>"
)

# 外部ライブラリをリンク
target_link_libraries(${LIBRARY_NAME} PRIVATE 
    $<BUILD_INTERFACE:${LABDOG_EXTERNAL_LIBS}>
)

# ライブラリをインストール
install(
    TARGETS              "${LIBRARY_NAME}"
    EXPORT               "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# ヘッダをインストール
install(
    FILES ${LABDOG_HEADERS_PUBLIC}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}"
)

# version.hppをインストール
install(
    FILES       "${LABDOG_GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/version.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}"
)

# export.hppをインストール
install(
    FILES "${LABDOG_GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/export.hpp" 
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}"
)

# コンフィグをインストール
install(
    FILES       "${PROJECT_CONFIG_FILE}"
                "${VERSION_CONFIG_FILE}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

# ターゲットのコンフィグをインストール
install(
    EXPORT      "${TARGETS_EXPORT_NAME}"
    FILE        "${PROJECT_NAME}Targets.cmake"
    DESTINATION "${CONFIG_INSTALL_DIR}"
    NAMESPACE   "${PROJECT_NAME}::"
)
