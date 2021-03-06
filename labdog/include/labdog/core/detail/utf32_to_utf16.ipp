#ifndef LABDOG_UTF32_TO_UTF16_IPP
#define LABDOG_UTF32_TO_UTF16_IPP

#include "labdog/core/charset_convert.hpp"

namespace ld
{
    namespace detail
    {
        template <std::input_iterator InputIterator, std::output_iterator<char16> OutputIterator>
        requires std::same_as<std::iter_value_t<InputIterator>, char32>
        OutputIterator utf16_encode(InputIterator first, InputIterator last, OutputIterator dest)
        {
            if (*first > code_point_max)
                throw std::runtime_error("Invalid code point.");

            if (*first < 0x10000)
            {
                auto res = static_cast<char16>(*first);
                *(dest++) = res;
            }
            else
            {
                *(dest++) = static_cast<char16>(((*first - 0x10000) >> 10) + lead_surrogate_min);
                *(dest++) = static_cast<char16>((*first & 0x3FF) + trail_surrogate_min);
            }

            return dest;
        }
    }

    template <std::input_iterator InputIterator, std::output_iterator<char16> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char32>
    inline OutputIterator utf32_to_utf16(InputIterator first, InputIterator last, OutputIterator dest)
    {
        while (first < last)
            dest = detail::utf16_encode(first++, last, dest);

        return dest;
    }
}

#endif // LABDOG_UTF32_TO_UTF16_IPP