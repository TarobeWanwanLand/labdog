//=========================================================
//
//	scalar.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "../core/common.hpp"
#include <concepts>

namespace labdog
{
	template <std::integral Type>
	LABDOG_EXPORT [[nodiscard]] inline bool is_power_of_two(Type value)
	{
		return ((value & (value - 1)) == 0)
	}
}