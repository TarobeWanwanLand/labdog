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
    static constexpr uint32 max_unicode{ 0x10FFFFu }; // 0000 0000 0001 0000 1111 1111 1111 1111

    [[nodiscard]] constexpr size_t utf8_bytes(const uint8 first_code_unit)
    {
        if (first_code_unit < 0xC0u /* 1100 0000 */)
            return 0u;
        if (first_code_unit < 0xE0u /* 1110 0000 */)
            return 1u;
        if (first_code_unit < 0xF0u /* 1111 0000 */)
            return 2u;
        if (first_code_unit < 0xF8u /* 1111 1000 */)
            return 3u;
        if (first_code_unit < 0xFCu /* 1111 1100 */)
            return 4u;
        return 5u;
    }

    size_t utf32_length(std::u8string_view u8sv)
    {
        size_t res = 0;
        auto itr = u8sv.begin();
        const auto end = u8sv.end();

        while(itr != end)
        {
            size_t bytes = utf8_bytes(std::bit_cast<uint8>(*itr));

            for (size_t i = 1; i < bytes + 1; ++i)
            {
                if ((*(itr + i) & 0xC0) != 0x80)
                {
                    bytes = 0;
                    break;
                }
            }

            itr += bytes + 1;

            ++res;
        }

        return res;
    }

    template <std::input_iterator Iterator>
    requires std::convertible_to<std::iter_value_t<Iterator>, char8>
    char32 code_units_from_utf8_to_utf32(Iterator& begin, Iterator end)
    {
        char32 res = 0;

        if(begin == end)
            return res;

        const size_t bytes = utf8_bytes(std::bit_cast<uint8>(*begin));

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
        auto itr = sv.begin();
        const auto end = sv.end();

        const size_t length = utf32_length(sv);
        std::u32string res(length, U'\0');

        for (size_t i = 0; i < length; ++i)
        {
            res[i] = code_units_from_utf8_to_utf32(itr, end);
        }

        return res;
    }
}