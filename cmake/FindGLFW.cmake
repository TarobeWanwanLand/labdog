# GLFW_FOUND
# GLFW_INCLUDE_DIRS
# GLFW_LIBRARIES

include(FindPackageHandleStandardArgs)

if(EXISTS ${GLFW_ROOT})
    set(GLFW_ROOT $ENV{GLFW_ROOT} CACHE STRING "GLFW root directory.")
endif()

find_path(GLFW_INCLUDE_DIR
    NAMES GLFW/glfw3.h
    PATHS
    "${GLFW_ROOT}/include"
    /usr/X11R6/include
    /usr/include/X11
    /usr/local/include
    /usr/include/GL
    /usr/include
    /opt/graphics/OpenGL/include
    /opt/graphics/OpenGL/contrib/libglfw
)

if(WIN32)
    if(MSVC11 OR (MSVC_VERSION EQUAL 1700))
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-vc2012"
            DOCS
            "The GLFW library"
        )
    elseif(MSVC12 OR (MSVC_VERSION EQUAL 1800))
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-vc2013"
            DOCS
            "The GLFW library"
        )
    elseif(MSVC14 OR (MSVC_VERSION EQUAL 1900))
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-vc2015"
        )
    elseif(MSVC15 OR ((MSVC_VERSION GREATER_EQUAL 1910) AND (MSVC_VERSION LESS 1920)))
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-vc2017"
        )
    elseif(MSVC16 OR ((MSVC_VERSION GREATER_EQUAL 1920) AND (MSVC_VERSION LESS 1930)))
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-vc2019"
        )
    elseif(MSVC17)
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-vc2022"
        )
    elseif(MINGW)
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
            "${GLFW_ROOT}/lib-mingw-w64"
        )
    else()
        find_library(GLFW_LIBRARIES
            NAMES
            glfw3
            PATHS
            "${GLFW_ROOT}/lib"
        )
    endif()
else()
    find_library(GLFW_LIBRARIES
        NAMES
        glfw
        glfw3
        PATHS
        "${GLFW_ROOT}/lib"
        "${GLFW_ROOT}/lib/x11"
        /usr/lib64
        /usr/lib
        /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}
        /usr/local/lib64
        /usr/local/lib
        /usr/local/lib/${CMAKE_LIBRARY_ARCHITECTURE}
        /usr/X11R6/lib
    )
    if(APPLE)
        list(APPEND GLFW_LIBRARIES
            "-framework Cocoa"
            "-framework CoreVideo"
            "-framework IOKit"
        )
    else()
        find_package(Threads REQUIRED)

        find_package(X11 REQUIRED)

        # Set up library and include paths
        list(APPEND GLFW_INCLUDE_DIR "${X11_X11_INCLUDE_PATH}")
        list(APPEND GLFW_LIBRARIES "${X11_X11_LIB}" "${CMAKE_THREAD_LIBS_INIT}" "${CMAKE_DL_LIBS}")

        # Check for XRandR (modern resolution switching and gamma control)
        if(NOT X11_Xrandr_FOUND)
            message(FATAL_ERROR "The RandR library and headers were not found")
        endif()

        list(APPEND GLFW_INCLUDE_DIR "${X11_Xrandr_INCLUDE_PATH}")
        list(APPEND GLFW_LIBRARIES "${X11_Xrandr_LIB}")

        # Check for Xinerama (legacy multi-monitor support)
        if(NOT X11_Xinerama_FOUND)
            message(FATAL_ERROR "The Xinerama library and headers were not found")
        endif()

        list(APPEND GLFW_INCLUDE_DIR "${X11_Xinerama_INCLUDE_PATH}")
        list(APPEND GLFW_LIBRARIES "${X11_Xinerama_LIB}")

        # Check for Xkb (X keyboard extension)
        if(NOT X11_Xkb_FOUND)
            message(FATAL_ERROR "The X keyboard extension headers were not found")
        endif()

        list(APPEND GLFW_INCLUDE_DIR "${X11_Xkb_INCLUDE_PATH}")

        # Check for Xcursor
        if(NOT X11_Xcursor_FOUND)
            message(FATAL_ERROR "The Xcursor libraries and headers were not found")
        endif()

        list(APPEND GLFW_INCLUDE_DIR "${X11_Xcursor_INCLUDE_PATH}")
        list(APPEND GLFW_LIBRARIES "${X11_Xcursor_LIB}")

        # Check for Xrandr
        if(NOT X11_Xrandr_FOUND)
            message(FATAL_ERROR "Xrandr library not found - required for GLFW")
        endif()

        list(APPEND GLFW_LIBRARIES "${X11_Xrandr_LIB}")

        # Check for xf86vmode
        if(NOT X11_xf86vmode_FOUND)
            message(FATAL_ERROR "xf86vmode library not found - required for GLFW")
        endif()

        list(APPEND GLFW_LIBRARIES "${X11_Xxf86vm_LIB}")
    endif()
endif()

set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})

find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIRS)
mark_as_advanced(GLFW_INCLUDE_DIRS GLFW_LIBRARIES)

message(STATUS "GLFW_FOUND = ${GLFW_FOUND}")
message(STATUS "GLFW_INCLUDE_DIRS = ${GLFW_INCLUDE_DIRS}")
message(STATUS "GLFW_LIBRARIES = ${GLFW_LIBRARIES}")