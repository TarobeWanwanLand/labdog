set(LABDOG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(LABDOG_HEADER_DIR "${CMAKE_SOURCE_DIR}/include")

# Set SOURCES variable
set(SOURCES
  ${LABDOG_SOURCE_DIR}/foo.cpp
)

# Set HEADERS_PUBLIC variable
set(HEADERS_PUBLIC
  ${LABDOG_HEADER_DIR}/labdog/foo.hpp
)

# Set HEADERS_PRIVATE variable
set(HEADERS_PRIVATE
)

# Target
add_library(${LIBRARY_NAME}
  ${SOURCES}
  ${HEADERS_PUBLIC}
  ${HEADERS_PRIVATE}
  )

# Alias:
#   - labdog::labdog alias of labdog
add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

# Generated headers folder
set(GENERATED_HEADERS_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_headers"
)

# Create 'version.h'
configure_file(
  "${LABDOG_HEADER_DIR}/labdog/version.hpp.in"
  "${GENERATED_HEADERS_DIR}/${LIBRARY_FOLDER}/version.hpp"
  @ONLY
)

include("GenerateExportHeader")
generate_export_header(${LIBRARY_NAME})
file(RENAME 
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_export.h"
    "${GENERATED_HEADERS_DIR}/${LIBRARY_FOLDER}/export.hpp"
)

# C++バージョンを指定
set_target_properties(${LIBRARY_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Add definitions for targets
# Values:
#   - Debug  : -DLABDOG_DEBUG=1
#   - Release: -DLABDOG_DEBUG=0
#   - others : -DLABDOG_DEBUG=0
target_compile_definitions(${LIBRARY_NAME} PUBLIC
  "${PROJECT_NAME_UPPERCASE}_DEBUG=$<CONFIG:Debug>")

# Global includes. Used by all targets
# Note:
#   - header can be included by C++ code `#include <labdog/labdog.h>`
#   - header location in project: ${CMAKE_CURRENT_BINARY_DIR}/generated_headers
target_include_directories(
  ${LIBRARY_NAME} PUBLIC
    "$<BUILD_INTERFACE:${LABDOG_HEADER_DIR}>"
    "$<BUILD_INTERFACE:${GENERATED_HEADERS_DIR}>"
    "$<INSTALL_INTERFACE:.>"
)

# Targets:
#   - <prefix>/lib/liblabdog.a
#   - header location after install: <prefix>/labdog/labdog.h
#   - headers can be included by C++ code `#include <labdog/labdog.h>`
install(
    TARGETS              "${LIBRARY_NAME}"
    EXPORT               "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
#   - labdog/*.h -> <prefix>/include/labdog/*.h
install(
    FILES ${HEADERS_PUBLIC}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}"
)

# Headers:
#   - generated_headers/labdog/version.h -> <prefix>/include/labdog/version.hpp
install(
    FILES       "${GENERATED_HEADERS_DIR}/${LIBRARY_FOLDER}/version.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}/core"
)

# Headers:
#   - labdog_export.h -> <prefix>/include/labdog/export.hpp
install(
    FILES "${GENERATED_HEADERS_DIR}/${LIBRARY_FOLDER}/export.hpp" 
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_FOLDER}/detail"
)

# Config
#   - <prefix>/lib/cmake/labdog/labdogConfig.cmake
#   - <prefix>/lib/cmake/labdog/labdogConfigVersion.cmake
install(
    FILES       "${PROJECT_CONFIG_FILE}"
                "${VERSION_CONFIG_FILE}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

# Config
#   - <prefix>/lib/cmake/labdog/labdogTargets.cmake
install(
  EXPORT      "${TARGETS_EXPORT_NAME}"
  FILE        "${PROJECT_NAME}Targets.cmake"
  DESTINATION "${CONFIG_INSTALL_DIR}"
  NAMESPACE   "${PROJECT_NAME}::"
)
