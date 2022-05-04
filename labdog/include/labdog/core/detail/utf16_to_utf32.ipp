#ifndef LABDOG_UTF16_TO_UTF32_IPP
#define LABDOG_UTF16_TO_UTF32_IPP

namespace ld
{
    namespace detail
    {
        template<std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
        requires std::same_as<std::iter_value_t<InputIterator>, char16_t>
        InputIterator utf32_encode(InputIterator first, InputIterator last, OutputIterator dest)
        {
            char32_t result = 0;

            if(is_lead_surrogate(*first))
            {
                if(is_trail_surrogate(*(first + 1)))
                {
                    result = ((char32_t(*(first++)) - 0xD800) << 10);
                    result |= (char32_t(*(first++)) - 0xDC00);
                    result += 0x10000;
                }
                else if(*first == 0)
                    result = *(first++);
                else
                    throw std::runtime_error("Invalid code point.");
            }
            else if (is_trail_surrogate(*first))
            {
                if (*(first + 1) == 0)
                    result = *(first++);
                else
                    throw std::runtime_error("Invalid code point.");
            }
            else
                result = *(first++);

            *dest = result;

            return first;
        }
    }

    template<std::input_iterator InputIterator, std::output_iterator<char32_t> OutputIterator>
    requires std::same_as<std::iter_value_t<InputIterator>, char16_t>
    inline OutputIterator utf16_to_utf32(InputIterator first, InputIterator last, OutputIterator dest)
    {
        while (first < last)
            first = detail::utf32_encode(first, last, dest++);

        return dest;
    }
}

#endif // LABDOG_UTF16_TO_UTF32_IPP