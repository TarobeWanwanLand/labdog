//=========================================================
//
//	alignment.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "../core/common.hpp"

namespace labdog
{
	/// @brief アライメントを指定してメモリ領域を確保する
	///	@param size 確保するメモリ領域のサイズ(bytes)
	/// @param alignment アライメント値
	/// @return 確保したメモリ
	[[nodiscard]] LABDOG_EXPORT inline void* aligned_malloc(size_t size, size_t alignment) noexcept;

	/// @brief アライメントを指定されたメモリ領域を解放する
	///	@param ptr 解放するメモリ領域のポインタ
	inline void alined_free(void* ptr) noexcept;

	/// @brief メモリ領域が指定したサイズでアライメントされているかを返す
	///	@param ptr メモリ領域のポインタ
	///	@param alignment アライメント値
	///	@return メモリ領域が指定したサイズでアライメントされているか
	[[nodiscard]] LABDOG_EXPORT inline bool is_aligned(const void* ptr, size_t alignment) noexcept;

	/// @brief アライメントを指定してメモリ領域を確保し、オブジェクトを構築する
	///	@param size 確保するメモリ領域のサイズ(bytes)
	/// @param alignment アライメント値
	/// @return 確保したメモリ
	template <class Type, class... Args>
	[[nodiscard]] LABDOG_EXPORT inline Type* aligned_new(Args&&... args);

	template <class Type>
	LABDOG_EXPORT inline void aligned_delete(Type* ptr);

	template <class Type>
	struct LABDOG_EXPORT aligned_deleter
	{
		void operator()(Type* ptr) noexcept;
	};
}

#include "detail/alignment.ipp"