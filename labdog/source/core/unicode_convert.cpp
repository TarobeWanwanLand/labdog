//=========================================================
//
//  charset_converter.cpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/unicode_convert.hpp"
#include <stdexcept>
#include <bit>

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

    static constexpr std::array<uint32, 6> utf8_offsets
        {
            0x00000000u, // 0: 0000 0000 0000 0000 0000 0000 0000 0000
            0x00003080u, // 1: 0000 0000 0000 0000 0011 0000 1000 0000
            0x000E2080u, // 2: 0000 0000 0000 1110 0010 0000 1000 0000
            0x03C82080u, // 3: 0000 0011 1100 1000 0010 0000 1000 0000
            0xFA082080u, // 4: 1111 1010 0000 1000 0010 0000 1000 0000
            0x82082080u  // 5: 1000 0010 0000 1000 0010 0000 1000 0000
        };

    /// @brief 置換文字
    static constexpr uint16 replacement_char{ 0xFFFDu }; // 1111 1111 1111 1101

    /// @brief 文字コードの上限値
    static constexpr uint32 max_utf32{ 0x10FFFFu }; // 0000 0000 0001 0000 1111 1111 1111 1111

    template <typename Iterator>
    char32 utf8_to_utf32(Iterator& begin, const Iterator end)
    {
        char32 res = 0;

        if(begin == end)
            return res;

        const auto first_code_unit = std::bit_cast<uint8>(*begin);
        const size_t bytes = ((first_code_unit < 0xC0u /* 1100 0000 */) ? 0u
                           : ((first_code_unit < 0xE0u /* 1110 0000 */) ? 1u
                           : ((first_code_unit < 0xF0u /* 1111 0000 */) ? 2u
                           : ((first_code_unit < 0xF8u /* 1111 1000 */) ? 3u
                           : ((first_code_unit < 0xFCu /* 1111 1100 */) ? 4u
                           : 5u)))));

        if(begin + bytes >= end)
            throw std::range_error("The number of code units is out of range.");

        for (auto i = static_cast<int64>(bytes); i >= 0; --i)
        {
            if(i > 3)
                res = replacement_char;
            else
                res += std::bit_cast<uint8>(*begin++);

            if(i != 0)
                res <<= 6;
        }

        res -= utf8_offsets[bytes];

        return res;
    }

    std::u32string utf8_to_utf32(const std::u8string_view sv)
    {
        std::u32string res;

        auto itr = sv.begin();
        const auto end = sv.end();

        while (itr != end)
        {
            res.push_back(utf8_to_utf32(itr, end));
        }

        return res;
    }
}