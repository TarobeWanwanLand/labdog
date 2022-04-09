#include <cstdio>
#include <gtest/gtest.h>
#include <labdog/core/string.hpp>

namespace
{
	TEST(labdog_test, string_comparison)
	{
		using namespace labdog;
		
		constexpr char32 arr[] = U"labdog🐶🦴";

		EXPECT_EQ(string(arr), arr);
		EXPECT_EQ(string(&*arr), arr);
	}
}