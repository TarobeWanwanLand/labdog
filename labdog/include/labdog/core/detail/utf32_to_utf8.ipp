#ifndef LABDOG_UTF32_TO_UTF8_IPP
#define LABDOG_UTF32_TO_UTF8_IPP

#include "labdog/core/unicode_convert.hpp"

namespace ld
{
    namespace detail
    {
        template <std::input_iterator InputIterator, std::output_iterator<char8_t> OutputIterator>
        requires std::same_as<std::iter_value_t<InputIterator>, char32_t>
        OutputIterator utf8_encode(InputIterator first, InputIterator last, OutputIterator dest)
        {
            if (!is_code_point_valid(*first))
                throw std::runtime_error("Invalid code point.");

            if (*first < 0x80) // one octet
            {
                *(dest++) = static_cast<char8>(*first);
            }
            else if (*first < 0x800) // two octet
            {
                *(dest++) = static_cast<char8>((*first >> 6) | 0xc0);
                *(dest++) = static_cast<char8>((*first & 0x3F) | 0x80);
            }
            else if (*first < 0x10000) // three octets
            {
                *(dest++) = static_cast<char8>((*first >> 12) | 0xE0);
                *(dest++) = static_cast<char8>(((*first >> 6) & 0x3F) | 0x80);
                *(dest++) = static_cast<char8>((*first & 0x3F) | 0x80);
            }
            else // four octets
            {
                *(dest++) = static_cast<char8>((*first >> 18) | 0xF0);
                *(dest++) = static_cast<char8>(((*first >> 12) & 0x3F) | 0x80);
                *(dest++) = static_cast<char8>(((*first >> 6) & 0x3F) | 0x80);
                *(dest++) = static_cast<char8>((*first & 0x3F) | 0x80);
            }

            return dest;
        }
    }

    template <std::input_iterator InputIterator, std::output_iterator<char8_t> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char32_t>
    inline OutputIterator utf32_to_utf8(InputIterator first, InputIterator last, OutputIterator dest)
    {
        while (first < last)
            dest = detail::utf8_encode(first++, last, dest);

        return dest;
    }
}

#endif // LABDOG_UTF32_TO_UTF8_IPP