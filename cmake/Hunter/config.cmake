hunter_config(
    Boost
    VERSION 1.65.0
    CMAKE_ARGS
        Boost_USE_STATIC=ON
)

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

hunter_config(
    GTest
    VERSION 1.11.0
    CMAKE_ARGS
        gmock_build_tests=OFF
        gtest_build_samples=OFF
        gtest_build_tests=OFF
)