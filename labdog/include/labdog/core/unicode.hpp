//=========================================================
//
//  unicode.hpp is part of the labdog project.
<<<<<<< Updated upstream
//  Copyright(c) 2022 Tomomi murakami.
=======
//  Copyright (C) 2022 TarobeWanwanLand.
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    std::u16string utf32To16(const string_view sv);
=======
    std::u16string utf32_to_utf16(const std::u32string_view sv);
>>>>>>> Stashed changes
} // namespace ld

#endif // LABDOG_UNICODE_HPP
