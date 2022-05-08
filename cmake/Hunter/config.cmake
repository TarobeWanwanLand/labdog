hunter_config(
    Boost
    VERSION 1.79.0
    URL https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz
    SHA1 28B4C71B7D9B8E323D40748F14E5C6D390E19720
)

hunter_config(
    spdlog
    VERSION 1.9.2-p0
    CMAKE_ARGS
        SPDLOG_BUILD_EXAMPLE=OFF
        SPDLOG_FMT_EXTERNAL=ON
)