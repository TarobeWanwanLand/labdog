set(LABDOG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(LABDOG_HEADER_DIR "${CMAKE_SOURCE_DIR}/include")

# ソースファイル
set(SOURCES
    ${LABDOG_SOURCE_DIR}/foo.cpp
)

# 公開するヘッダファイル
set(HEADERS_PUBLIC
    ${LABDOG_HEADER_DIR}/labdog/foo.hpp
)

# 非公開のヘッダファイル
set(HEADERS_PRIVATE
)

# ライブラリを作成
add_library(${LIBRARY_NAME}
    ${SOURCES}
    ${HEADERS_PUBLIC}
    ${HEADERS_PRIVATE}
)

# ライブラリの別名を定義
add_library(${PROJECT_NAME}::${LIBRARY_NAME} 
    ALIAS ${LIBRARY_NAME}
)

# CMakeの生成ヘッダのディレクトリ
set(GENERATED_HEADER_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/header"
)

# version.hppを作成
configure_file(
    "${LABDOG_HEADER_DIR}/labdog/version.hpp.in"
    "${GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/version.hpp"
    @ONLY
)

# export.hppを作成
include("GenerateExportHeader")
generate_export_header(${LIBRARY_NAME})
file(RENAME 
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_export.h"
    "${GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/export.hpp"
)

# DEBUGプリプロセッサマクロの定義
target_compile_definitions(${LIBRARY_NAME} PUBLIC
    "${PROJECT_NAME_UPPERCASE}_DEBUG=$<CONFIG:Debug>"
)

# インクルードディレクトリを設定
target_include_directories(${LIBRARY_NAME} PUBLIC
    "$<BUILD_INTERFACE:${LABDOG_HEADER_DIR}>"
    "$<BUILD_INTERFACE:${EXTERNAL_INCLUDES}>"
    "$<BUILD_INTERFACE:${GENERATED_HEADER_DIR}>"
    "$<INSTALL_INTERFACE:.>"
)

# 外部ライブラリをリンク
target_link_libraries(${LIBRARY_NAME} PRIVATE 
    $<BUILD_INTERFACE:${EXTERNAL_LIBS}>
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
    FILES ${HEADERS_PUBLIC}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}"
)

# version.hppをインストール
install(
    FILES       "${GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/version.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}"
)

# export.hppをインストール
install(
    FILES "${GENERATED_HEADER_DIR}/${LIBRARY_FOLDER}/export.hpp" 
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
