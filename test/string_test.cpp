#include "test.hpp"

namespace
{
	TEST(labdog_test, string_comparison)
	{
		constexpr const char32* c1 = U"labdog game🐶";
        constexpr const char32* c2 = U"aaaaa";

		EXPECT_EQ(string(c1), c1);
        EXPECT_EQ(string(U'a', 5), c2);
	}
}