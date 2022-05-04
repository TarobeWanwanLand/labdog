#ifndef LABDOG_UTF8_TO_UTF32_IPP
#define LABDOG_UTF8_TO_UTF32_IPP

#include "labdog/core/charset_convert.hpp"

namespace ld
{
    namespace detail
    {
        static constexpr std::array<uint32, 6> utf8_offsets
            {
                0x00000000, // 0: 0000 0000 0000 0000 0000 0000 0000 0000
                0x00003080, // 1: 0000 0000 0000 0000 0011 0000 1000 0000
                0x000E2080, // 2: 0000 0000 0000 1110 0010 0000 1000 0000
                0x03C82080, // 3: 0000 0011 1100 1000 0010 0000 1000 0000
                0xFA082080, // 4: 1111 1010 0000 1000 0010 0000 1000 0000
                0x82082080  // 5: 1000 0010 0000 1000 0010 0000 1000 0000
            };

        template <class U8>
        [[nodiscard]] constexpr size_t utf8_bytes(const U8 cp) noexcept
        {
            if (cp < 0xC0)               // 1: 0000 0000 ~ 0111 1111
                return 1;
            if (cp >= 0xC0 && cp < 0xE0) // 2: 1100 0000 ~ 1101 1111
                return 2;
            if (cp >= 0xE0 && cp < 0xF0) // 3: 1110 0000 ~ 1110 1111
                return 3;
            if (cp >= 0xF0 && cp < 0xF8) // 4: 1111 0000 ~ 1111 0111
                return 4;
            return 0;
        }

        template<std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
        requires
               std::same_as<std::iter_value_t<InputIterator>, char8_t>
            || std::same_as<std::iter_value_t<InputIterator>, char>
        InputIterator utf32_encode(InputIterator first, InputIterator last, OutputIterator dest)
        {
            const size_t bytes = utf8_bytes(static_cast<uint8>(*first));

            char32_t result = 0;

            switch (bytes)
            {
                default:
                    throw std::runtime_error("Invalid code point.");
                case 4:
                    result += *(first++);
                    result <<= 6;
                    [[fallthrough]];
                case 3:
                    result += *(first++);
                    result <<= 6;
                    [[fallthrough]];
                case 2:
                    result += *(first++);
                    result <<= 6;
                    [[fallthrough]];
                case 1:
                    result += *(first++);
                    result -= utf8_offsets[bytes - 1];
            }

            *dest = result;

            return first;
        }
    }

    template<std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
    requires
           std::same_as<std::iter_value_t<InputIterator>, char8_t>
        || std::same_as<std::iter_value_t<InputIterator>, char>
    inline OutputIterator utf8_to_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        while (first < last)
            first = detail::utf32_encode(first, last, dest++);

        return dest;
    }
}

#endif // LABDOG_UTF8_TO_UTF32_IPP