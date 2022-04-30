//=========================================================
//
//  charset_converter.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_UNICODE_CONVERT_HPP
#define LABDOG_UNICODE_CONVERT_HPP

#include "common.hpp"
#include <string>
#include <string_view>
#include <array>

namespace ld
{
    std::u32string utf8_to_utf32(const std::u8string_view sv);
}

#endif // LABDOG_UNICODE_CONVERT_HPP
