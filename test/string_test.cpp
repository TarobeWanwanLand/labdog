#include "test.hpp"
#include <ranges>
#include "labdog/core/string.hpp"
#include "labdog/core/string_view.hpp"

namespace
{
    static constexpr const char32* const STRING{ U"labdog is the best!" };

    TEST(string, construct)
    {
        string str1{ string_view(STRING) };
        EXPECT_EQ(str1.compare(STRING), 0);

#if LD_COMPILER_MSVC
        string str2{ string_view(STRING) | std::views::drop(7) };
        EXPECT_EQ(str2.compare(STRING + 7), 0);
#endif
    }

    TEST(string, to_string_view)
    {
        string str{ STRING };
        string_view strv = str;
        EXPECT_EQ(str.compare(strv), 0);
    }

    TEST(string, assign_string_view)
    {
        string str(U"be overwritten");
        str.assign(string_view(STRING));
        EXPECT_EQ(str.compare(STRING), 0);
    }

#if LD_COMPILER_MSVC
    TEST(string, assign_range)
    {
        string str(U"be overwritten");
        str.assign(string_view(STRING) | std::views::drop(7));
        EXPECT_EQ(str.compare(STRING + 7), 0);
    }
#endif

    TEST(string, compare_with_string_view)
    {
        string str(U"b");
        EXPECT_EQ(str, string_view(U"b"));
        EXPECT_NE(str, string_view(U"z"));
        EXPECT_LT(str, string_view(U"ca"));
        EXPECT_GT(str, string_view(U"az"));
    }
}