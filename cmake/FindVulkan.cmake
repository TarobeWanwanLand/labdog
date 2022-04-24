# Vulkan_FOUND
# Vulkan_INCLUDE_DIRS
# Vulkan_LIBRARIES

include(FindPackageMessage)
include(FindPackageHandleStandardArgs)

if(NOT DEFINED VULKAN_ROOT)
    set(VULKAN_ROOT $ENV{VULKAN_SDK})
endif()

if(WIN32)
    find_path(Vulkan_INCLUDE_DIR
        NAMES vulkan/vulkan.h
        HINTS
        "${VULKAN_ROOT}/Include"
    )
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        find_library(Vulkan_LIBRARY
            NAMES vulkan-1
            HINTS
            "${VULKAN_ROOT}/Lib"
            "${VULKAN_ROOT}/Bin"
        )
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(Vulkan_LIBRARY
            NAMES vulkan-1
            HINTS
            "${VULKAN_ROOT}/Lib32"
            "${VULKAN_ROOT}/Bin32"
        )
    endif()
else()
    find_path(Vulkan_INCLUDE_DIR
        NAMES vulkan/vulkan.h
        HINTS "${VULKAN_ROOT}/include"
    )
    find_library(Vulkan_LIBRARY
        NAMES vulkan
        HINTS "${VULKAN_ROOT}/lib"
    )
endif()

set(Vulkan_LIBRARIES ${Vulkan_LIBRARY})
set(Vulkan_INCLUDE_DIRS ${Vulkan_INCLUDE_DIR})

find_package_handle_standard_args(Vulkan DEFAULT_MSG Vulkan_INCLUDE_DIRS Vulkan_LIBRARIES)
mark_as_advanced(Vulkan_INCLUDE_DIRS Vulkan_LIBRARIES)

message(STATUS "Vulkan_FOUND = ${Vulkan_FOUND}")
message(STATUS "Vulkan_INCLUDE_DIRS = ${Vulkan_INCLUDE_DIRS}")
message(STATUS "Vulkan_LIBRARIES = ${Vulkan_LIBRARIES}")