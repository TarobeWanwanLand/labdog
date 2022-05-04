# Vulkan_FOUND
# Vulkan_INCLUDE_DIRS
# Vulkan_LIBRARIES

include(FindPackageMessage)
include(FindPackageHandleStandardArgs)

if(WIN32)
    find_path(Vulkan_INCLUDE_DIRS
        NAMES vulkan/vulkan.h
        PATHS
            "$ENV{VULKAN_SDK}/Include"
    )
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        find_library(Vulkan_LIBRARIES
            NAMES vulkan-1
            PATHS
                "$ENV{VULKAN_SDK}/Lib"
                "$ENV{VULKAN_SDK}/Bin"
        )
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(Vulkan_LIBRARIES
            NAMES vulkan-1
            PATHS
                "$ENV{VULKAN_SDK}/Lib32"
                "$ENV{VULKAN_SDK}/Bin32"
        )
    endif()
else()
    find_path(Vulkan_INCLUDE_DIRS
        NAMES vulkan/vulkan.h
        PATHS
            "$ENV{VULKAN_SDK}/include"
    )
    find_library(Vulkan_LIBRARIES
        NAMES vulkan
        PATHS
            "$ENV{VULKAN_SDK}/lib"
    )
endif()

find_package_handle_standard_args(Vulkan DEFAULT_MSG Vulkan_INCLUDE_DIRS Vulkan_LIBRARIES)
mark_as_advanced(Vulkan_INCLUDE_DIRS Vulkan_LIBRARIES)

message(STATUS "Vulkan_FOUND = ${Vulkan_FOUND}")
message(STATUS "Vulkan_INCLUDE_DIRS = ${Vulkan_INCLUDE_DIRS}")
message(STATUS "Vulkan_LIBRARIES = ${Vulkan_LIBRARIES}")