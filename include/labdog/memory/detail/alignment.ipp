//=========================================================
//
//	alignment.ipp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "../alignment.hpp"
#include <memory>
#include "../../math/scalar.hpp"

namespace labdog
	inline void* aligned_malloc(const size_t size, const size_t alignment) noexcept {
		return ::_aligned_malloc(size, alignment);
	}

	inline void alined_free(void* ptr) noexcept {
		return ::_aligned_free(ptr);
	}

	inline bool is_aligned(const void* ptr, const size_t alignment) noexcept {
		return ((reinterpret_cast<std::uintptr_t>(ptr) % alignment) == 0);
	}

	template <class Type, class ... Args>
	inline Type* aligned_new(Args&&... args) {
		constexpr size_t alignment = alignof(T);
		static_assert(alignment > 8, "");
		static_assert(is_power_of_two(alignment), "2ÇÃó›èÊêîÇ≈Ç†ÇÈïKóvÇ™Ç†ÇËÇ‹Ç∑ÅB");
		void* ptr = aligned_malloc(sizeof(Type), alignment);
		if (!ptr) LABDOG_UNLIKELY
			throw std::bad_alloc();
		return new(ptr) Type{ std::forward<Args>(args)... };
	}

	template <class Type>
	inline void aligned_delete(Type* ptr) {
		if (!ptr) LABDOG_UNLIKELY
			return;
		ptr->~Type();
		alined_free(ptr);
	}

	template <class Type>
	inline void aligned_deleter<Type>::operator()(Type* ptr) noexcept {
		aligned_delete(ptr);
	}
}
