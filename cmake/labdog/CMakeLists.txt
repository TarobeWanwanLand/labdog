# ヘッダとソースのディレクトリ
set(LABDOG_HEADER_DIR "${CMAKE_SOURCE_DIR}/labdog/include")
set(LABDOG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/labdog/source")

# ヘッダファイル
set(LABDOG_HEADERS
    "${LABDOG_HEADER_DIR}/labdog/core/application.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/assertion.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/charset_convert.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/common.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/concept.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/dispatcher.hpp"
        #    "${LABDOG_HEADER_DIR}/labdog/core/logger.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/mouse.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/string.hpp"
    "${LABDOG_HEADER_DIR}/labdog/core/string_view.hpp"

    "${LABDOG_HEADER_DIR}/labdog/core/detail/utf8_to_utf32.ipp"
    "${LABDOG_SOURCE_DIR}/labdog/core/detail/utf16_to_utf32.ipp"
    "${LABDOG_HEADER_DIR}/labdog/core/detail/utf32_to_utf8.ipp"
    "${LABDOG_HEADER_DIR}/labdog/core/detail/utf32_to_utf16.ipp"

    "${LABDOG_HEADER_DIR}/labdog/graphics/graphics.hpp"
    "${LABDOG_HEADER_DIR}/labdog/graphics/window.hpp"
)

# ソースファイル
set(LABDOG_SOURCES
    "${LABDOG_SOURCE_DIR}/core/application.cpp"
    "${LABDOG_SOURCE_DIR}/core/mouse.cpp"
#    "${LABDOG_SOURCE_DIR}/core/logger.cpp"
    "${LABDOG_SOURCE_DIR}/core/string.cpp"
    "${LABDOG_SOURCE_DIR}/core/string_view.cpp"

    "${LABDOG_SOURCE_DIR}/graphics/graphics.cpp"
    "${LABDOG_SOURCE_DIR}/graphics/window.cpp"
)

# ライブラリを作成
add_library(${PROJECT_NAME} STATIC ${LABDOG_SOURCES})

# ライブラリの別名を定義
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

# staticビルド時にポストフィックスを設定
if(BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LD_EXPORTS)
else()
    set(STATIC_POSTFIX -static)
endif()

# ビルドタイプごとのポストフィックスを設定
set_target_properties(${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX "${STATIC_POSTFIX}-d"
    RELEASE_POSTFIX "${STATIC_POSTFIX}"
    MINSIZEREL_POSTFIX "${STATIC_POSTFIX}-mr"
    RELWITHDEBINFO_POSTFIX "${STATIC_POSTFIX}-rd"
)

# ソースファイルをライブラリに追加
target_sources(${PROJECT_NAME} PRIVATE ${LABDOG_SOURCES})

# インクルードディレクトリを設定
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${LABDOG_HEADER_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

# ライブラリをリンク
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${EXTERNAL_LIBRARIES}
)

# ヘッダファイルをインストール
install(
    DIRECTORY "${LABDOG_HEADER_DIR}/labdog"
    DESTINATION include
)

# ライブラリをインストール
install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}_config"
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION "include/${PROJECT_NAME}"
)

# コンフィグファイルをインストール
install(EXPORT "${PROJECT_NAME}_config"
    NAMESPACE "${PROJECT_NAME}::"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
)