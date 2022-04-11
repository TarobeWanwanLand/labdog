//=========================================================
//
//	assert.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "../core/common.hpp"
#include <format>
#include <source_location>

#ifdef NDEBUG
	#define LABDOG_ASSERT(expr) ((void)0)
	#define LABDOG_ASSERT_MSG(expr, msg) ((void)0)
#else
	/// @brief デバッグビルド時にログを出力してブレークポイントを発生させる
	/// @param expr 判定式
	#define LABDOG_ASSERT(expr) do { [[likely]] (!!(expr)) ? (void(0)) : (labdog::detail::AssertionFailed(#expr), __debugbreak()); } while(false)

	/// @brief デバッグビルド時にメッセージ付きでログを出力してブレークポイントを発生させる
	/// @param expr 判定式
	/// @param msg 書式文字列
	/// @param __VA_ARGS__ 書式引数
	#define LABDOG_ASSERT_MSG(expr, msg, ...) \
		do { [[likely]] (!!(expr)) ? (void(0)) : (labdog::detail::AssertionFailedMsg(#expr, std::format(msg, ##__VA_ARGS__)), __debugbreak()); } while(false)

namespace labdog::detail
{
	LABDOG_EXPORT inline void AssertionFailed(
		const std::string_view expr,
		const std::source_location location = std::source_location::current()) noexcept
	{
		// 出力用メッセージ
		const auto out = std::format(
			"\n"
			"==============< Assertion failed ! >==============\n"
			"Expression: {}\n"
			"File: {}\n"
			"Function: {}\n"
			"Line: {}\n"
			"==================================================\n",
			expr,
			location.file_name(),
			location.function_name(),
			location.line());

#ifdef _MSC_VER
		// VisualStudio上に出力
		OutputDebugString(out.c_str());
#endif	
	}

	LABDOG_EXPORT inline void AssertionFailedMsg(
		const std::string_view expr,
		const std::string_view msg,
		const std::source_location location = std::source_location::current()) noexcept
	{
		// 出力用メッセージ
		const auto out = std::format(
			"\n"
			"==============< Assertion failed ! >==============\n"
			"Expression: {}\n"
			"Message: {}\n"
			"File: {}\n"
			"Function: {}\n"
			"Line: {}\n"
			"==================================================\n",
			expr,
			msg,
			location.file_name(),
			location.function_name(),
			location.line());

#ifdef _MSC_VER
		// VisualStudio上に出力
		OutputDebugString(out.c_str());
#endif
	}
}
#endif