//=========================================================
//
//	string.hpp is part of the labdog framework.
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_STRING_HPP
#define LABDOG_STRING_HPP

#include "common.hpp"
#include <string>

namespace labdog
{
	//class string_view;

	/// @brief UTF-32������N���X
	class LABDOG_API string
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
        //	�萔
        //=========================================================
        /// @brief �����ȗv�f�̃C���f�b�N�X�l
        static constexpr size_type npos{ string_type::npos };

		//=========================================================
		//	�R���X�g���N�^
		//=========================================================
		/// @brief �f�t�H���g�R���X�g���N�^
        LABDOG_NODISCARD_CXX20
        string() noexcept;

		/// @brief �R�s�[�R���X�g���N�^
        LABDOG_NODISCARD_CXX20
        string(const string& other) noexcept;

		/// @brief ���[�u�R���X�g���N�^
        LABDOG_NODISCARD_CXX20
        string(string&& other) noexcept;

		/// @brief ������̎w��͈͂��R�s�[���č\�z����
		/// @param str �R�s�[���镶����
		///	@param pos �͈͂̐擪�ʒu
		///	@param length �͈͂̒���
        LABDOG_NODISCARD_CXX20
        string(const string& str, size_type pos, size_type length = npos);

		/// @brief �����񂩂�R�s�[���č\�z����
		///	@param str �R�s�[���镶����
        LABDOG_NODISCARD_CXX20
        explicit string(const string_type& str);

		/// @brief ������̎w��͈͂��R�s�[���č\�z����
		/// @param str �R�s�[���镶����
		///	@param pos �͈͂̐擪�ʒu
		///	@param length �͈͂̒���
        LABDOG_NODISCARD_CXX20
        string(const string_type& str, size_type pos, size_type length = npos);

		/// @brief �����z����R�s�[���č\�z����
		/// @param str �R�s�[���镶���z��
        LABDOG_NODISCARD_CXX20
        explicit string(const value_type* str);

		/// @brief �����z��̎w��͈͂��R�s�[���č\�z����
		/// @param str �R�s�[���镶���z��
		///	@param pos �͈͂̐擪�ʒu
		///	@param length �͈͂̒���
        LABDOG_NODISCARD_CXX20
        string(const value_type* str, size_type pos, size_type length = npos);

		/// @brief �������w������ׂ���������\�z����
		///	@param c �J��Ԃ�����
		///	@param count ��
        LABDOG_NODISCARD_CXX20
        string(value_type c, size_type count);

		/// @brief ������͈̔͂���\�z����
		/// @tparam Iterator �C�e���[�^�^
		/// @param first �͈͂̐擪�v�f�ւ̃C�e���[�^
		/// @param last �͈̖͂����v�f�ւ̃C�e���[�^
		template <class Iterator>
        LABDOG_NODISCARD_CXX20
        string(Iterator first, Iterator last);

		/// @brief �����̏������q���X�g����\�z����
		///	@param list �����̏������q���X�g
        LABDOG_NODISCARD_CXX20
        string(std::initializer_list<value_type> list);

		//=========================================================
		//	�f�X�g���N�^
		//=========================================================
		/// @brief �f�t�H���g�f�X�g���N�^
		virtual ~string() noexcept = default;

		//=========================================================
		//	���Z�q
		//=========================================================
		/// @brief �R�s�[������Z�q
		[[nodiscard]] string& operator=(const string& rhs) = default;

		/// @brief ���[�u������Z�q
		[[nodiscard]] string& operator=(string&& rhs) noexcept;

		/// @brief �����z����R�s�[�������
		[[nodiscard]] string& operator=(const value_type* rhs);

		/// @brief �������R�s�[�������
		[[nodiscard]] string& operator=(value_type rhs);

		/// @brief �����̏������q���X�g���R�s�[�������
		[[nodiscard]] string& operator=(std::initializer_list<value_type> rhs);

		/// @brief ������𖖔��Ɍ�������
		[[nodiscard]] string operator+(const string& rhs) const;

		/// @brief ������𖖔��Ɍ�������
		[[nodiscard]] string operator+(const value_type* rhs) const;

		/// @brief �����𖖔��Ɍ�������
		[[nodiscard]] string operator+(value_type rhs) const;

		/// @brief ������𖖔��Ɍ������đ������
		[[nodiscard]] string& operator+=(const string& rhs);

		/// @brief �����z��𖖔��Ɍ������đ������
		[[nodiscard]] string& operator+=(const value_type* rhs);

		/// @brief �����𖖔��Ɍ������đ������
		[[nodiscard]] string& operator+=(value_type rhs);

		/// @brief ������𓙒l��r����
		[[nodiscard]] bool operator==(const string& rhs) const;

		/// @brief ������𓙒l��r����
		[[nodiscard]] bool operator==(const value_type* rhs) const;

		/// @brief �������񓙒l��r����
		[[nodiscard]] bool operator!=(const string & rhs) const;

		/// @brief �������񓙒l��r����
		[[nodiscard]] bool operator!=(const value_type* rhs) const;

		/// @brief ��������r����
		[[nodiscard]] std::strong_ordering operator<=>(const string& rhs) const;

		/// @brief ��������r����
		[[nodiscard]] std::strong_ordering operator<=>(const value_type* rhs) const;

		//=========================================================
		//	�v�f�A�N�Z�X
		//=========================================================
		/// @brief �擪�v�f�ւ̃|�C���^��Ԃ�
		///	@return �擪�v�f�ւ̃|�C���^
		[[nodiscard]] const value_type* data() const noexcept;

		/// @brief �擪�v�f�ւ̎Q�Ƃ�Ԃ�
		///	@return �擪�v�f�ւ̎Q��
		[[nodiscard]] value_type& front() noexcept;

		/// @brief �擪�v�f�ւ�const�Q�Ƃ�Ԃ�
		///	@return �擪�v�f�ւ�const�Q��
		[[nodiscard]] const value_type& front() const noexcept;

		/// @brief �����v�f�ւ̎Q�Ƃ�Ԃ�
		///	@return �����v�f�ւ̎Q��
		[[nodiscard]] value_type& back() noexcept;

		/// @brief �����v�f�ւ�const�Q�Ƃ�Ԃ�
		///	@return �����v�f�ւ�const�Q��
		[[nodiscard]] const value_type& back() const noexcept;

		//=========================================================
		//	���
		//=========================================================
		/// @brief ������̒�����Ԃ�
		///	@return ������̒���
		[[nodiscard]] size_t size() const noexcept;

		/// @brief �i�[�\�ȍő啶������Ԃ�
		///	@return �i�[�\�ȍő啶����
		[[nodiscard]] size_t max_size() const noexcept;

		/// @brief �R���e�i���󂩂ǂ�����Ԃ�
		///	@return �R���e�i����
		[[nodiscard]] bool empty() const noexcept;

		//=========================================================
		//	�C�e���[�^
		//=========================================================
		/// @brief �擪�v�f���w���C�e���[�^��Ԃ�
		[[nodiscard]] iterator begin() noexcept;

		/// @brief �擪�v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] const_iterator begin() const noexcept;

		/// @brief �����v�f���w���C�e���[�^��Ԃ�
		[[nodiscard]] iterator end() noexcept;

		/// @brief �����v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] const_iterator end() const noexcept;

		/// @brief �擪�v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] const_iterator cbegin() const noexcept;

		/// @brief �����v�f���w��const�C�e���[�^��Ԃ�
		[[nodiscard]] const_iterator cend() const noexcept;

		/// @brief �擪�v�f���w�����o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] reverse_iterator rbegin() noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept;

		/// @brief �����v�f���w�����o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] reverse_iterator rend() noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] const_reverse_iterator rend() const noexcept;

		/// @brief �擪�v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept;

		/// @brief �����v�f���w��const���o�[�X�C�e���[�^��Ԃ�
		[[nodiscard]] const_reverse_iterator crend() const noexcept;

	private:
		//friend string_view;

		//=========================================================
		//	�ϐ�
		//=========================================================
		/// @brief ������R���e�i
		string_type string_;
	};
}

#include "detail/string.ipp"

#endif // LABDOG_STRING_HPP