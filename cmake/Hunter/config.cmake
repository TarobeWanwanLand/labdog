if(${MINGW})
    hunter_config(
        Boost
        VERSION 1.64.0
        CMAKE_ARGS
            Boost_USE_STATIC=ON
    )
else()
    if(${WIN32})
        hunter_config(
            Boost
            VERSION 1.79.0
            URL https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.zip
            SHA1 1C9715FDD9A503FD0576F0FB6DCAF965AD5BDF04
            CMAKE_ARGS
                Boost_USE_STATIC=ON
        )
    else()
        hunter_config(
            Boost
            VERSION 1.79.0-unix
            URL https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz
            SHA1 28B4C71B7D9B8E323D40748F14E5C6D390E19720
            CMAKE_ARGS
                Boost_USE_STATIC=ON
        )
    endif()
endif()

hunter_config(
    glfw
    VERSION 3.3.7
    URL https://github.com/glfw/glfw/releases/download/3.3.7/glfw-3.3.7.zip
    SHA1 B7B05EE954D93C66AD431DD750CC47CA08F9F9EE
    CMAKE_ARGS
        GLFW_BUILD_EXAMPLES=OFF
        GLFW_BUILD_TESTS=OFF
)

hunter_config(
    fmt
    VERSION 8.1.1
    CMAKE_ARGS
        FMT_TEST=OFF
)

hunter_config(
    spdlog
    VERSION 1.10.0
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz
    SHA1 A1F1ABC03A6B66158578321F100E5E31E3806601
    CMAKE_ARGS
        SPDLOG_BUILD_EXAMPLE=OFF
        SPDLOG_FMT_EXTERNAL=ON
)

if(${MSVC80})
    hunter_config(
        GTest
        VERSION 1.7.0-hunter-6
        CMAKE_ARGS
            gmock_build_tests=OFF
            gtest_build_samples=OFF
            gtest_build_tests=OFF
    )
else()
    hunter_config(
        GTest
        VERSION 1.11.0
        CMAKE_ARGS
            gmock_build_tests=OFF
            gtest_build_samples=OFF
            gtest_build_tests=OFF
    )
endif()