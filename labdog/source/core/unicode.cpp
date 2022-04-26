//=========================================================
//
//  unicode.cpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/unicode.hpp"
#include <cstdlib>

namespace ld
{
    // 🦴 U+1F9B4
    // code point         000   01 1111   10 0110   11 0100
    //              1111 0    10        10        10
    // UTF-8        1111 0000 1001 1111 1010 0110 1011 0100
    // UTF-32       0000 0000 0000 0001 1111 1001 1011 0100

    static constexpr std::array<uint8, 7> first_byte_mask
    {
        0x00u, // 0: 0000 0000
        0x00u, // 1: 0000 0000
        0xC0u, // 2: 1100 0000
        0xE0u, // 3: 1110 0000
        0xF0u, // 4: 1111 0000
        0xF8u, // 5: 1111 1000
        0xFCu  // 6: 1111 1100
    };

    constexpr std::array<uint32, 6> utf8_offsets
    {
        0x00000000u, // 0: 0000 0000 0000 0000 0000 0000 0000 0000
        0x00003080u, // 1: 0000 0000 0000 0000 0011 0000 1000 0000
        0x000E2080u, // 2: 0000 0000 0000 1110 0010 0000 1000 0000
        0x03C82080u, // 3: 0000 0011 1100 1000 0010 0000 1000 0000
        0xFA082080u, // 4: 1111 1010 0000 1000 0010 0000 1000 0000
        0x82082080u  // 5: 1000 0010 0000 1000 0010 0000 1000 0000
    };

    [[nodiscard]] constexpr uint8 utf8_bytes(const uint8 code_unit) noexcept
    {
        if(code_unit < 0xC0u) // ~ 1100 0000
            return 0u;
        if(code_unit < 0xE0u) // ~ 1110 0000
            return 1u;
        if(code_unit < 0xF0u) // ~ 1111 0000
            return 2u;
        if(code_unit < 0xF8u) // ~ 1111 1000
            return 3u;
        if(code_unit < 0xFCu) // ~ 1111 1100
            return 4u;
        return 5u;            // ~ 1111 1111
    }

    std::u16string utf32To16(const string_view sv)
    {
        return std::u16string();
    }
} // namespace ld