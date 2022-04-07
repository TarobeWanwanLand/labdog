//=========================================================
//
//	string.hpp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "common.hpp"
#include <string>

namespace labdog
{
	class string_view;

	/// @brief UTF-32������N���X
	class LABDOG_EXPORT string
	{
	public:
		//=========================================================
		//	�G�C���A�X
		//=========================================================
		/// @brief ������^
		using string_type = std::u32string;

		/// @brief ������̓����^
		using traits_type = string_type::traits_type;

		/// @brief �A���P�[�^�^
		using allocator_type = string_type::allocator_type;

		/// @brief �v�f�^
		using value_type = string_type::value_type;

		/// @brief �v�f�̃|�C���^�^
		using pointer = string_type::pointer;

		/// @brief �v�f��const�|�C���^�^
		using const_pointer = string_type::const_pointer;

		/// @brief �v�f�̎Q�ƌ^
		using reference = string_type::reference;

		/// @brief �v�f��const�Q�ƌ^
		using const_reference = string_type::const_reference;

		/// @brief �C�e���[�^�^
		using iterator = string_type::iterator;

		/// @brief const�C�e���[�^�^
		using const_iterator = string_type::const_iterator;

		/// @brief ���o�[�X�C�e���[�^�^
		using reverse_iterator = string_type::reverse_iterator;

		/// @brief const���o�[�X�C�e���[�^�^
		using const_reverse_iterator = string_type::const_reverse_iterator;

		/// @brief �v�f�̌���\������^
		using size_type = string_type::size_type;

		/// @brief �v�f�Ԃ̋�����\������^
		using difference_type = string_type::difference_type;

		//=========================================================
		//	�R���X�g���N�^
		//=========================================================
		/// @brief �f�t�H���g�R���X�g���N�^
		constexpr string() noexcept = default;

		/// @brief �R�s�[�R���X�g���N�^
		constexpr string(const string& other) noexcept = default;

		/// @brief ���[�u�R���X�g���N�^
		constexpr string(string&& other) noexcept;

		/// @brief ������̎w��͈͂��R�s�[���č\�z����
		/// @param str �R�s�[���镶����
		///	@param pos �͈͂̐擪�ʒu
		///	@param length �͈͂̒���
		constexpr string(const string& str, size_type pos, size_type length = string_type::npos);

		/// @brief �����񂩂�R�s�[���č\�z����
		///	@param str �R�s�[���镶����
		explicit constexpr string(const string_type& str);

		/// @brief ������̎w��͈͂��R�s�[���č\�z����
		/// @param str �R�s�[���镶����
		///	@param pos �͈͂̐擪�ʒu
		///	@param length �͈͂̒���
		constexpr string(const string_type& str, size_type pos, size_type length = string_type::npos);

		/// @brief �����z����R�s�[���č\�z����
		/// @param str �R�s�[���镶���z��
		explicit constexpr string(const value_type* str);

		/// @brief �����z��̎w��͈͂��R�s�[���č\�z����
		/// @param str �R�s�[���镶���z��
		///	@param pos �͈͂̐擪�ʒu
		///	@param length �͈͂̒���
		constexpr string(const value_type* str, size_type pos, size_type length = string_type::npos);

		/// @brief �������w������ׂ���������\�z����
		///	@param c �J��Ԃ�����
		///	@param count ��
		constexpr string(value_type c, size_type count);

		/// @brief ������͈̔͂���\�z����
		/// @tparam Iterator �C�e���[�^�^
		/// @param first �͈͂̐擪�v�f�ւ̃C�e���[�^
		/// @param last �͈̖͂����v�f�ւ̃C�e���[�^
		template <class Iterator>
		constexpr string(Iterator first, Iterator last);

		/// @brief �����̏������q���X�g����\�z����
		///	@param list �����̏������q���X�g
		constexpr string(std::initializer_list<value_type> list);

		//=========================================================
		//	�f�X�g���N�^
		//=========================================================
		/// @brief �f�t�H���g�f�X�g���N�^
		constexpr virtual ~string() noexcept = default;

		//=========================================================
		//	���Z�q
		//=========================================================
		/// @brief �R�s�[������Z�q
		[[nodiscard]] constexpr string& operator=(const string& rhs) = default;

		/// @brief ���[�u������Z�q
		[[nodiscard]] constexpr string& operator=(string&& rhs) noexcept;

		/// @brief �����z����R�s�[�������
		[[nodiscard]] constexpr string& operator=(const value_type* rhs);

		/// @brief �������R�s�[�������
		[[nodiscard]] constexpr string& operator=(value_type rhs);

		/// @brief �����̏������q���X�g���R�s�[�������
		[[nodiscard]] constexpr string& operator=(std::initializer_list<value_type> rhs);

		/// @brief ������𖖔��Ɍ�������
		[[nodiscard]] constexpr string operator+(const string& rhs) const;

		/// @brief ������𖖔��Ɍ�������
		[[nodiscard]] constexpr string operator+(const value_type* rhs) const;

		/// @brief �����𖖔��Ɍ�������
		[[nodiscard]] constexpr string operator+(value_type rhs) const;

		/// @brief ������𖖔��Ɍ������đ������
		[[nodiscard]] constexpr string& operator+=(const string& rhs);

		/// @brief �����z��𖖔��Ɍ������đ������
		[[nodiscard]] constexpr string& operator+=(const value_type* rhs);

		/// @brief �����𖖔��Ɍ������đ������
		[[nodiscard]] constexpr string& operator+=(value_type rhs);

		/// @brief ������𓙒l��r����
		[[nodiscard]] constexpr bool operator==(const string& rhs) const;

		/// @brief ������𓙒l��r����
		[[nodiscard]] constexpr bool operator==(const value_type* rhs) const;

		/// @brief �������񓙒l��r����
		[[nodiscard]] constexpr bool operator!=(const string & rhs) const;

		/// @brief �������񓙒l��r����
		[[nodiscard]] constexpr bool operator!=(const value_type* rhs) const;

		/// @brief ��������r����
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const string& rhs) const;

		/// @brief ��������r����
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const value_type* rhs) const;

		//=========================================================
		//	�v�f�A�N�Z�X
		//=========================================================
		/// @brief �擪�v�f�ւ̃|�C���^��Ԃ�
		///	@return �擪�v�f�ւ̃|�C���^
		[[nodiscard]] constexpr const value_type* data() const noexcept;

		/// @brief �擪�v�f�ւ̎Q�Ƃ�Ԃ�
		///	@return �擪�v�f�ւ̎Q��
		[[nodiscard]] constexpr value_type& front() noexcept;

		/// @brief �擪�v�f�ւ�const�Q�Ƃ�Ԃ�
		///	@return �擪�v�f�ւ�const�Q��
		[[nodiscard]] constexpr const value_type& front() const noexcept;

		/// @brief �����v�f�ւ̎Q�Ƃ�Ԃ�
		///	@return �����v�f�ւ̎Q��
		[[nodiscard]] constexpr value_type& back() noexcept;

		/// @brief �����v�f�ւ�const�Q�Ƃ�Ԃ�
		///	@return �����v�f�ւ�const�Q��
		[[nodiscard]] constexpr const value_type& back() const noexcept;

		//=========================================================
		//	���
		//=========================================================
		/// @brief ������̒�����Ԃ�
		///	@return ������̒���
		[[nodiscard]] constexpr size_t size() const noexcept;

		/// @brief �i�[�\�ȍő啶������Ԃ�
		///	@return �i�[�\�ȍő啶����
		[[nodiscard]] constexpr size_t max_size() const noexcept;

		/// @brief �R���e�i���󂩂ǂ�����Ԃ�
		///	@return �R���e�i����
		[[nodiscard]] constexpr bool empty() const noexcept;

		//=========================================================
		//	�C�e���[�^
		//=========================================================
		/// @brief �擪�v�f���w���C�e���[�^��Ԃ�
		[[nodiscard]] constexpr iterator begin() noexcept;

		/// @brief �擪�v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator begin() const noexcept;

		/// @brief �����v�f���w���C�e���[�^��Ԃ�
		[[nodiscard]] constexpr iterator end() noexcept;

		/// @brief �����v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator end() const noexcept;

		/// @brief �擪�v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept;

		/// @brief �����v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_iterator cend() const noexcept;

		/// @brief �擪�v�f���w�����o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept;

		/// @brief �����v�f���w�����o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr reverse_iterator rend() noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept;

		/// @brief �����v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept;

	private:
		friend string_view;

		//=========================================================
		//	�ϐ�
		//=========================================================
		/// @brief ������R���e�i
		string_type string_;
	};
}

#include "detail/string.ipp"