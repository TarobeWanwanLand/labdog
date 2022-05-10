//=========================================================
//
//  assertion.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_ASSERTION_HPP
#define LABDOG_ASSERTION_HPP

#include "common.hpp"
#include "logger.hpp"
#include <iostream>

#if LD_DEBUG
    #define LD_ASSERT(expr)         \
        do                          \
        {                           \
            LD_LIKELY (!!(expr))    \
                ? (static_cast<void>(0))    \
                : (ld::detail::assertion_failed(#expr, __FILE__, __func__, __LINE__), debugbreak());  \
        } while(false)
#else
    #define LD_ASSERT(expr) (static_cast<void>(0))
#endif

namespace ld
{
    namespace detail
    {
        inline void assertion_failed(const char* expr, const char* file, const char* func, const size_t line) noexcept
        {
            std::cerr <<
                "==============< Assertion failed ! >==============\n"
                "Expr: " << expr << "\n"
                "File: " << file << "\n"
                "Func: " << func << "\n"
                "Line: " << line << "\n"
                "==================================================\n";
        }
    }
}

#endif //LABDOG_ASSERTION_HPP
