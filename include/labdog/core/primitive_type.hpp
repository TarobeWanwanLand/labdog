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

namespace wx2
{
	//=========================================================
	//	�����t�������^
	//=========================================================
	/// @brief �����t��8bit�����^
	using int8  = char;
	static_assert(sizeof(int8) == 1);

	/// @brief �����t��16bit�����^
	using int16 = short;
	static_assert(sizeof(int16) == 2);

	/// @brief �����t��32bit�����^
	using int32 = int;
	static_assert(sizeof(int32) == 4);

	/// @brief �����t��64bit�����^
	using int64 = long long;
	static_assert(sizeof(int64) == 8);

	//=========================================================
	//	�����Ȃ������^
	//=========================================================
	/// @brief ��������8bit�����^
	using uint8  = unsigned char;
	static_assert(sizeof(uint8) == 1);

	/// @brief ��������16bit�����^
	using uint16 = unsigned short;
	static_assert(sizeof(uint16) == 2);

	/// @brief ��������32bit�����^
	using uint32 = unsigned int;
	static_assert(sizeof(uint32) == 4);

	/// @brief ��������64bit�����^
	using uint64 = unsigned long long;
	static_assert(sizeof(uint64) == 8);

	//=========================================================
	//	�����^
	//=========================================================
	/// @brief UTF-8�����^
	using char8 = char;
	static_assert(sizeof(char8) == 1);

	/// @brief UTF-16�����^
	using char16 = char16_t;
	static_assert(sizeof(char16) == 2);

	/// @brief UTF-32�����^
	using char32 = char32_t;
	static_assert(sizeof(char32) == 4);
}