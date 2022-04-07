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
	/// @brief �A���C�����g���w�肵�ă������̈���m�ۂ���
	///	@param size �m�ۂ��郁�����̈�̃T�C�Y(bytes)
	/// @param alignment �A���C�����g�l
	/// @return �m�ۂ���������
	[[nodiscard]] LABDOG_EXPORT inline void* aligned_malloc(size_t size, size_t alignment) noexcept;

	/// @brief �A���C�����g���w�肳�ꂽ�������̈���������
	///	@param ptr ������郁�����̈�̃|�C���^
	inline void alined_free(void* ptr) noexcept;

	/// @brief �������̈悪�w�肵���T�C�Y�ŃA���C�����g����Ă��邩��Ԃ�
	///	@param ptr �������̈�̃|�C���^
	///	@param alignment �A���C�����g�l
	///	@return �������̈悪�w�肵���T�C�Y�ŃA���C�����g����Ă��邩
	[[nodiscard]] LABDOG_EXPORT inline bool is_aligned(const void* ptr, size_t alignment) noexcept;

	/// @brief �A���C�����g���w�肵�ă������̈���m�ۂ��A�I�u�W�F�N�g���\�z����
	///	@param size �m�ۂ��郁�����̈�̃T�C�Y(bytes)
	/// @param alignment �A���C�����g�l
	/// @return �m�ۂ���������
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