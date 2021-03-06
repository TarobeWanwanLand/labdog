//=========================================================
//
//  charset_converter.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_CHARSET_CONVERT_HPP
#define LABDOG_CHARSET_CONVERT_HPP

#include "common.hpp"
#include <string>
#include <string_view>
#include <array>
#include <stdexcept>
#include <iostream>

namespace ld
{
    namespace detail
    {
        const uint16 lead_surrogate_min { 0xD800 }; //!< 先頭サロゲートの最小値
        const uint16 lead_surrogate_max { 0xDBFF }; //!< 先頭サロゲートの最大値
        const uint16 trail_surrogate_min{ 0xDC00 }; //!< 後続サロゲートの最小値
        const uint16 trail_surrogate_max{ 0xDFFF }; //!< 後続サロゲートの最大値

        static constexpr uint32 code_point_max{ 0x10FFFF }; //!< コードポイントの最大値

        template <typename U16>
        [[nodiscard]] constexpr bool is_lead_surrogate(const U16 cp) noexcept
        {
            return (cp >= lead_surrogate_min && cp <= lead_surrogate_max);
        }

        template <typename U16>
        [[nodiscard]] constexpr bool is_trail_surrogate(const U16 cp) noexcept
        {
            return (cp >= trail_surrogate_min && cp <= trail_surrogate_max);
        }

        template <typename U16>
        [[nodiscard]] constexpr bool is_surrogate(const U16 cp) noexcept
        {
            return (is_lead_surrogate(cp) || is_trail_surrogate(cp));
        }

        template <typename U32>
        [[nodiscard]] constexpr bool is_code_point_valid(const U32 cp) noexcept
        {
            return (cp <= code_point_max && !is_surrogate(cp));
        }
    }

    template<std::input_iterator InputIterator, std::output_iterator<char32> OutputIterator>
    requires
           std::same_as<std::iter_value_t<InputIterator>, char8>
        || std::same_as<std::iter_value_t<InputIterator>, char>
    OutputIterator utf8_to_utf32(InputIterator first, InputIterator last, OutputIterator dest);

    template<std::input_iterator InputIterator, std::output_iterator<char32> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char16>
    OutputIterator utf16_to_utf32(InputIterator first, InputIterator last, OutputIterator dest);

    template <std::input_iterator InputIterator, class OutputIterator>
    requires
           std::same_as<std::iter_value_t<InputIterator>, char32>
        && (std::output_iterator<OutputIterator, char8> || std::output_iterator<OutputIterator, char>)
    OutputIterator utf32_to_utf8(InputIterator first, InputIterator last, OutputIterator dest);

    template <std::input_iterator InputIterator, std::output_iterator<char16> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char32>
    OutputIterator utf32_to_utf16(InputIterator first, InputIterator last, OutputIterator dest);

    template<std::input_iterator InputIterator, std::output_iterator<char8> OutputIterator>
    requires
           std::same_as<std::iter_value_t<InputIterator>, char16>
        && (std::output_iterator<OutputIterator, char8> || std::output_iterator<OutputIterator, char>)
    OutputIterator utf16_to_utf8(InputIterator first, InputIterator last, OutputIterator dest)
    {
        std::u32string temp;
        utf16_to_utf32(first, last, std::back_inserter(temp));
        return utf32_to_utf8(temp.begin(), temp.end(), dest);
    }

    template<std::input_iterator InputIterator, std::output_iterator<char16> OutputIterator>
    requires
           std::same_as<std::iter_value_t<InputIterator>, char8>
        || std::same_as<std::iter_value_t<InputIterator>, char>
    OutputIterator utf8_to_utf16(InputIterator first, InputIterator last, OutputIterator dest)
    {
        std::u32string temp;
        utf8_to_utf32(first, last, std::back_inserter(temp));
        return utf32_to_utf16(temp.begin(), temp.end(), dest);
    }
}

#include "detail/utf8_to_utf32.ipp"
#include "detail/utf16_to_utf32.ipp"
#include "detail/utf32_to_utf8.ipp"
#include "detail/utf32_to_utf16.ipp"

#endif // LABDOG_CHARSET_CONVERT_HPP