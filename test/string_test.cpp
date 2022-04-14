#include "test.hpp"

namespace
{
	TEST(labdog_test, string_comparison)
	{
        using namespace ld::string_literals;

        string empty_str;

        EXPECT_TRUE(empty_str.empty());
        EXPECT_EQ(empty_str, U"");
        EXPECT_EQ(empty_str, U""_s);
        EXPECT_EQ(empty_str.size(), 0);
    }
}