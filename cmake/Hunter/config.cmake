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
            VERSION 1.79.0-win
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

if(${ANDROID})
    hunter_config(
        glm
        VERSION 0.9.9.8
        URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
        SHA1 45408897F419944FB28D8FD835791F237BE2EC19
        CMAKE_ARGS
            BUILD_STATIC_LIBS=ON
    )
else()
    hunter_config(
        glm
        VERSION 0.9.9.2
        CMAKE_ARGS
            BUILD_STATIC_LIBS=ON
    )
endif()

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
    EnTT
    VERSION 3.10.0
    URL https://github.com/skypjack/entt/archive/refs/tags/v3.10.1.tar.gz
    SHA1 B7E287CB691B2A741C01CB757BAE5702319D3B34
    CMAKE_ARGS
        ENTT_USE_ATOMIC=ON
)

hunter_config(
    magic_enum
    VERSION 0.8.0
    URL https://github.com/Neargye/magic_enum/archive/refs/tags/v0.8.0.tar.gz
    SHA1 C77709F80C72A545DF83738838A64F6F2438AE25
    CMAKE_ARGS
        MAGIC_ENUM_OPT_ENABLE_NONASCII=ON
        MAGIC_ENUM_OPT_BUILD_EXAMPLES=OFF
        MAGIC_ENUM_OPT_BUILD_TESTS=OFF
        MAGIC_ENUM_OPT_INSTALL=ON
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