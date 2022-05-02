#ifndef LABDOG_UTF8_TO_UTF32_IPP
#define LABDOG_UTF8_TO_UTF32_IPP

#include "labdog/core/unicode_convert.hpp"

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

        /// @brief 置換文字
        static constexpr uint16 replacement_char{ 0xFFFD }; // 1111 1111 1111 1101

        template <class U8>
        [[nodiscard]] constexpr size_t utf8_bytes(const U8 cp)
        {
            if (cp < 0xC0)               // 1: 0000 0000 ~ 0111 1111
                return 1;
            if (cp >= 0xC0 && cp < 0xE0) // 2: 1100 0000 ~ 1101 1111
                return 2;
            if (cp >= 0xE0 && cp < 0xF0) // 3: 1110 0000 ~ 1110 1111
                return 3;
            if (cp >= 0xF0 && cp < 0xF8) // 4: 1111 0000 ~ 1111 0111
                return 4;
            throw std::runtime_error("Invalid code point.");
        }

        template <std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
        requires std::same_as<std::iter_value_t<InputIterator>, char8_t>
        InputIterator utf32_encode(InputIterator begin, InputIterator end, OutputIterator dest)
        {
            const size_t bytes = utf8_bytes(static_cast<uint8>(*begin));

            char32_t result = 0;

            switch (bytes)
            {
                case 4:
                    result += *(begin++);
                    result <<= 6;
                    [[fallthrough]];
                case 3:
                    result += *(begin++);
                    result <<= 6;
                    [[fallthrough]];
                case 2:
                    result += *(begin++);
                    result <<= 6;
                    [[fallthrough]];
                case 1:
                    result += *(begin++);
            }

            *dest = result - utf8_offsets[bytes - 1];

            return begin;
        }
    }

    template <std::input_iterator Iterator>
    requires std::same_as<std::iter_value_t<Iterator>, char8_t>
    inline size_t utf8_to_utf32_length(Iterator begin, Iterator end)
    {
        size_t result = 0;

        while(begin != end)
        {
            size_t bytes = detail::utf8_bytes(*begin);

            for (auto itr = begin + 1; (itr != (begin + bytes)) && (itr != end); ++itr)
            {
                if ((*itr & 0xC0) != 0x80)
                {
                    bytes = 1;
                    break;
                }
            }

            begin += bytes;

            ++result;
        }

        return result;
    }

    template<std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char8_t>
    inline OutputIterator utf8_to_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        while (first != last)
            first = detail::utf32_encode(first, last, dest++);

        return dest;
    }
}

#endif // LABDOG_UTF8_TO_UTF32_IPP