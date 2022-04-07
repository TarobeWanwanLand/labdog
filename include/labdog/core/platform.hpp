//=========================================================
//
//	platform.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once

//=========================================================
//	プラットフォーム
//=========================================================
/// @brief プラットフォームがサポート対象か
#ifndef _WIN32 // Windows以外は非サポート
	#error Unsupported platform.
#elif !defined(_WIN64) // x86は非サポート
	#error Windows x86 is not supported.
#endif

//=========================================================
//	ビルド設定
//=========================================================
/// @brief ビルドタイプがデバッグか
#if defined(_DEBUG) || defined(DEBUG) // デバッグビルド
	#define LABDOG_BUILD_TYPE_DEBUG true
#else
	#define LABDOG_BUILD_TYPE_DEBUG false
#endif

//=========================================================
//	コンパイラ拡張(MSVC)
//=========================================================
/// @brief pragma warning(push), pragma warning(pop)
#ifdef _MSC_VER
	#define LABDOG_DISABLE_WARNINGS_PUSH(warnings)		\
			 __pragma(warning(push))					\
			 __pragma(warning(disable: warnings))
	#define LABDOG_DISABLE_WARNINGS_POP()				\
			 __pragma(warning(pop))
#else
	#define LABDOG_DISABLE_WARNINGS_PUSH(warnings)
	#define LABDOG_DISABLE_WARNINGS_POP()
#endif