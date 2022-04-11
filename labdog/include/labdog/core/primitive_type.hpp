//=========================================================
//
//	primitive_type.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include <cstddef>

namespace labdog
{
	//=========================================================
	//	tซฎ^
	//=========================================================
	/// @brief tซ8bitฎ^
	using int8  = char;
	static_assert(sizeof(int8) == 1);

	/// @brief tซ16bitฎ^
	using int16 = short;
	static_assert(sizeof(int16) == 2);

	/// @brief tซ32bitฎ^
	using int32 = int;
	static_assert(sizeof(int32) == 4);

	/// @brief tซ64bitฎ^
	using int64 = long long;
	static_assert(sizeof(int64) == 8);

	//=========================================================
	//	ศตฎ^
	//=========================================================
	/// @brief ณต8bitฎ^
	using uint8  = unsigned char;
	static_assert(sizeof(uint8) == 1);

	/// @brief ณต16bitฎ^
	using uint16 = unsigned short;
	static_assert(sizeof(uint16) == 2);

	/// @brief ณต32bitฎ^
	using uint32 = unsigned int;
	static_assert(sizeof(uint32) == 4);

	/// @brief ณต64bitฎ^
	using uint64 = unsigned long long;
	static_assert(sizeof(uint64) == 8);

	//=========================================================
	//	ถ^
	//=========================================================
	/// @brief UTF-8ถ^
	using char8 = char;
	static_assert(sizeof(char8) == 1);

	/// @brief UTF-16ถ^
	using char16 = char16_t;
	static_assert(sizeof(char16) == 2);

	/// @brief UTF-32ถ^
	using char32 = char32_t;
	static_assert(sizeof(char32) == 4);
}