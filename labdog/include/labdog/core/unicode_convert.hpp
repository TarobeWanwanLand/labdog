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
#include <stdexcept>
#include <iostream>

namespace ld
{
    namespace detail
    {
        const uint16_t lead_surrogate_min { 0xD800 }; //!< 先頭サロゲートの最小値
        const uint16_t lead_surrogate_max { 0xDBFF }; //!< 先頭サロゲートの最大値
        const uint16_t trail_surrogate_min{ 0xDC00 }; //!< 後続サロゲートの最小値
        const uint16_t trail_surrogate_max{ 0xDFFF }; //!< 後続サロゲートの最大値

        static constexpr uint32_t code_point_max{ 0x10FFFF }; //!< コードポイントの最大値

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

    //std::u32string utf8_to_utf32(const std::u8string_view sv);

    template<std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char8_t>
    OutputIterator utf8_to_utf32(InputIterator first, InputIterator last, OutputIterator dest);

    template <std::input_iterator InputIterator, std::output_iterator<char8_t> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char32_t>
    OutputIterator utf32_to_utf8(InputIterator first, InputIterator last, OutputIterator dest);

    template <std::input_iterator InputIterator, std::output_iterator<char16_t> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char32_t>
    OutputIterator utf32_to_utf16(InputIterator first, InputIterator last, OutputIterator dest);

    template <std::input_iterator Iterator>
    requires std::same_as<std::iter_value_t<Iterator>, char8_t>
    [[nodiscard]] size_t utf8_to_utf32_length(Iterator begin, Iterator end);
}

#include "detail/utf32_to_utf8.ipp"
#include "detail/utf32_to_utf16.ipp"
#include "detail/utf8_to_utf32.ipp"

#endif // LABDOG_UNICODE_CONVERT_HPP