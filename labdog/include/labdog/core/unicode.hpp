//=========================================================
//
//  unicode.hpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_UNICODE_HPP
#define LABDOG_UNICODE_HPP

#include "common.hpp"
#include "string.hpp"
#include "string_view.hpp"
#include <array>
#include <stdexcept>

namespace ld
{
    std::u16string utf32To16(const string_view sv);
} // namespace ld

#endif // LABDOG_UNICODE_HPP
