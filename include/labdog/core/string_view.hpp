//=========================================================
//
//	string_view.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "common.hpp"
#include <string_view>
#include "string.hpp"

namespace labdog
{
	class string;

	/// @brief UTF-32������r���[�N���X
	class LABDOG_EXPORT string_view
	{
	public:
		//=========================================================
		//	�G�C���A�X
		//=========================================================
		/// @brief ������^
		using string_view_type = std::u32string_view;

		/// @brief ������̓����^
		using traits_type = string_view_type::traits_type;

		/// @brief �v�f�^
		using value_type = string_view_type::value_type;

		/// @brief �v�f�̃|�C���^�^
		using pointer = string_view_type::pointer;

		/// @brief �v�f��const�|�C���^�^
		using const_pointer = string_view_type::const_pointer;

		/// @brief �v�f�̎Q�ƌ^
		using reference = string_view_type::reference;

		/// @brief �v�f��const�Q�ƌ^
		using const_reference = string_view_type::const_reference;

		/// @brief �C�e���[�^�^
		using iterator = string_view_type::iterator;

		/// @brief const�C�e���[�^�^
		using const_iterator = string_view_type::const_iterator;

		/// @brief ���o�[�X�C�e���[�^�^
		using reverse_iterator = string_view_type::reverse_iterator;

		/// @brief const���o�[�X�C�e���[�^�^
		using const_reverse_iterator = string_view_type::const_reverse_iterator;

		/// @brief �v�f�̌���\������^
		using size_type = string_view_type::size_type;

		/// @brief �v�f�Ԃ̋�����\������^
		using difference_type = string_view_type::difference_type;

		//=========================================================
		//	�萔
		//=========================================================
		/// @brief �����Ȉʒu
		static constexpr size_t npos = string_view_type::npos;

		//=========================================================
		//	�R���X�g���N�^
		//=========================================================
		/// @brief �f�t�H���g�R���X�g���N�^
		constexpr string_view() noexcept = default;

		/// @brief �R�s�[�R���X�g���N�^
		constexpr string_view(const string_view&) noexcept = default;

		/// @brief ���[�u�R���X�g���N�^
		constexpr string_view(string_view&& other) noexcept;

		/// @brief ��������Q�Ƃ���
		///	@param str �Q�Ƃ��镶����
		explicit constexpr string_view(const string& str) noexcept;

		/// @brief �����z��̐擪����w�蕶�����͈̔͂��Q�Ƃ���
		///	@param str �Q�Ƃ��镶���z��
		///	@param count �Q�Ƃ��镶����
		explicit constexpr string_view(const string& str, size_t count) noexcept;

		/// @brief �����z����Q�Ƃ���
		///	@param str �Q�Ƃ��镶���z��
		explicit constexpr string_view(const value_type* str) noexcept;

		/// @brief �����z��̐擪����w�蕶�����͈̔͂��Q�Ƃ���
		///	@param str �Q�Ƃ��镶���z��
		///	@param count �Q�Ƃ��镶����
		constexpr string_view(const value_type* str, size_t count) noexcept;

		/// @brief ������͈̔͂��Q�Ƃ���
		/// @tparam Iterator �C�e���[�^�^
		/// @param first �͈͂̐擪�v�f�ւ̃C�e���[�^
		/// @param last �͈̖͂����v�f�ւ̃C�e���[�^
		template <class Iterator>
		constexpr string_view(Iterator first, Iterator last);

		//=========================================================
		//	�f�X�g���N�^
		//=========================================================
		/// @brief �f�t�H���g�f�X�g���N�^
		virtual ~string_view() noexcept = default;

		//=========================================================
		//	���Z�q
		//=========================================================
		/// @brief �R�s�[������Z�q
		[[nodiscard]] constexpr string_view& operator=(const string_view& rhs) = default;

		/// @brief ��������Q�Ƃ���
		[[nodiscard]] constexpr string_view& operator=(const string& rhs) noexcept;

		/// @brief �����z����Q�Ƃ���
		[[nodiscard]] constexpr string_view& operator=(const value_type* rhs);

		/// @brief ������𓙒l��r����
		[[nodiscard]] constexpr bool operator==(const string_view& rhs) const;

		/// @brief ������𓙒l��r����
		[[nodiscard]] constexpr bool operator==(const string& rhs) const;

		/// @brief ������𓙒l��r����
		[[nodiscard]] constexpr bool operator==(const value_type* rhs) const;

		/// @brief ��������r����
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const string_view& rhs) const noexcept;

		/// @brief ��������r����
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const string& rhs) const noexcept;

		/// @brief ��������r����
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const value_type* rhs) const noexcept;

		//=========================================================
		//	�v�f�A�N�Z�X
		//=========================================================
		/// @brief �擪�v�f�ւ̃|�C���^��Ԃ�
		///	@return �擪�v�f�ւ̃|�C���^
		[[nodiscard]] constexpr const value_type* data() const noexcept;

		/// @brief �擪�v�f�ւ�const�Q�Ƃ�Ԃ�
		///	@return �擪�v�f�ւ�const�Q��
		[[nodiscard]] constexpr const value_type& front() const noexcept;

		/// @brief �����v�f�ւ�const�Q�Ƃ�Ԃ�
		///	@return �����v�f�ւ�const�Q��
		[[nodiscard]] constexpr const value_type& back() const noexcept;

		//=========================================================
		//	���
		//=========================================================
		/// @brief ������̒�����Ԃ�
		///	@return ������̒���
		[[nodiscard]] constexpr size_t size() const noexcept;

		/// @brief �Q�Ɖ\�ȍő啶������Ԃ�
		///	@return �Q�Ɖ\�ȍő啶����
		[[nodiscard]] constexpr size_t max_size() const noexcept;

		/// @brief �����񂪋󂩂ǂ�����Ԃ�
		///	@return �����񂪋�
		[[nodiscard]] constexpr bool empty() const noexcept;

		//=========================================================
		//	�C�e���[�^
		//=========================================================
		/// @brief �擪�v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator begin() const noexcept;

		/// @brief �����v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator end() const noexcept;

		/// @brief �擪�v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept;

		/// @brief �����v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator cend() const noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept;

		/// @brief �����v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept;

	private:
		//=========================================================
		//	�ϐ�
		//=========================================================
		string_view_type view_;
	};
}

#include "detail/string_view.ipp"