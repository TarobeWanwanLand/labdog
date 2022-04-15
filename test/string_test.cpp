#include "test.hpp"
#include <cstring>

namespace
{
    constexpr char32 C_STRING[] { U"labdod is the best!" };
    constexpr size_t C_STRING_SIZE{ sizeof(C_STRING) / sizeof(char32) - 1 };

    TEST(string, construct_empty)
	{
        string str;

        EXPECT_EQ(str, U"");
        EXPECT_EQ(str, U""_s);
        EXPECT_EQ(str.size(), 0);
        EXPECT_EQ(str.length(), 0);
        EXPECT_TRUE(str.empty());
    }

    TEST(string, construct_from_std_string)
    {
        const std::u32string std_str(C_STRING);

        string str(std_str);

        EXPECT_EQ(str.size(), C_STRING_SIZE);
        EXPECT_EQ(str.length(), C_STRING_SIZE);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING, C_STRING_SIZE), 0);
    }

    TEST(string, move_construct_from_std_string)
    {
        std::u32string std_str(C_STRING);

        string str(std::move(std_str));

        EXPECT_EQ(str.size(), C_STRING_SIZE);
        EXPECT_EQ(str.length(), C_STRING_SIZE);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING, C_STRING_SIZE), 0);
    }

    TEST(string, construct_from_string)
    {
        string original(C_STRING);

        string str(original);

        EXPECT_EQ(str.size(), C_STRING_SIZE);
        EXPECT_EQ(str.length(), C_STRING_SIZE);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING, C_STRING_SIZE), 0);
    }

    TEST(string, construct_from_string_with_range)
    {
        string original(C_STRING);

        string str(original, 7, 11);

        EXPECT_EQ(str.size(), 11);
        EXPECT_EQ(str.length(), 11);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING + 7, 11), 0);
    }

    TEST(string, move_construct_from_string)
    {
        string original(C_STRING);

        string str(std::move(original));

        EXPECT_EQ(str.size(), C_STRING_SIZE);
        EXPECT_EQ(str.length(), C_STRING_SIZE);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING, C_STRING_SIZE), 0);
    }

    TEST(string, construct_from_ptr_string)
    {
        string str(C_STRING);

        EXPECT_EQ(str.size(), C_STRING_SIZE);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING, C_STRING_SIZE), 0);
    }

    TEST(string, construct_from_ptr_string_with_range)
    {
        string str(C_STRING + 7, 11);

        EXPECT_EQ(str.size(), 11);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), C_STRING + 7, 11), 0);
    }

    TEST(string, construct_from_char)
    {
        string str(5, U'🦴');

        EXPECT_EQ(str.size(), 5);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), U"🦴🦴🦴🦴🦴", 5), 0);
    }

    TEST(string, construct_from_initializer_list)
    {
        string str({ U'🥰', U'🐶', U'🦴' });

        EXPECT_EQ(str.size(), 3);
        EXPECT_EQ(std::char_traits<char32>::compare(str.c_str(), U"🥰🐶🦴", 3), 0);
    }
}
#pragma clang diagnostic pop