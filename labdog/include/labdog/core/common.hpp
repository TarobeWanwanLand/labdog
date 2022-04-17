//=========================================================
//
//	common.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once

//=========================================================
//  Platform
//=========================================================
#define LD_PLATFORM_WINDOWS     0
#define LD_PLATFORM_MACOS       0
#define LD_PLATFORM_LINUX       0

#if defined(_WIN32)
    #undef  LD_PLATFORM_WINDOWS
    #define LD_PLATFORM_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
    #undef  LD_PLATFORM_MACOS
    #define LD_PLATFORM_MACOS   1
#elif defined(__linux__)
    #undef  LD_PLATFORM_LINUX
    #define LD_PLATFORM_LINUX   1
#else
    #error "Unsupported platform"
#endif

//=========================================================
//  Compiler
//=========================================================
#define LD_COMPILER_GNU         0
#define LD_COMPILER_MSVC        0

#if defined(__GNUC__)
    #undef  LD_COMPILER_GNU
    #define LD_COMPILER_GNU     1
#elif defined(_MSC_VER)
    #undef  LD_COMPILER_MSVC
    #define LD_COMPILER_MSVC    1
#else
    #error "Unsupported compiler"
#endif

//=========================================================
//  Architecture
//=========================================================
#if defined(_WIN64) || defined(__x86_64__)
    #define LD_X64  1
#else
    #define LD_X64  0
#endif

//=========================================================
//  Build type
//=========================================================
#if defined(_DEBUG) || defined(DEBUG)
    #define LD_DEBUG 1
#else
    #define LD_DEBUG 0
#endif

//=========================================================
//  STL Version
//=========================================================
#if defined(_MSC_VER)
    #define LD_STL_LANG _MSVC_LANG
#elif defined(__cplusplus)
    #define LD_STL_LANG __cplusplus
#else
    #define LD_STL_LANG 0L
#endif

//=========================================================
//  Attribute
//=========================================================
// [[likely]] and [[unlikely]] attributes
# if __has_cpp_attribute(likely)    \
 && __has_cpp_attribute(unlikely)   \
 && !LD_COMPILER_GNU
    #define LD_LIKELY [[likely]]
    #define LD_UNLIKELY [[unlikely]]
#else
    #define LD_LIKELY
    #define LD_UNLIKELY
#endif

//=========================================================
//  Types
//=========================================================
namespace ld
{
    using int8 = char;
    using int16 = short;
    using int32 = int;
    using int64 = long long;

    static_assert(sizeof(int16) == 2);
    static_assert(sizeof(int32) == 4);

    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long long;

    static_assert(sizeof(uint16) == 2);
    static_assert(sizeof(uint32) == 4);

    using char8 = char;
    using char16 = char16_t;
    using char32 = char32_t;

    static_assert(sizeof(char16) == 2);
    static_assert(sizeof(char32) == 4);
}