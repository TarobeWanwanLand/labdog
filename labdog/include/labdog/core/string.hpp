//=========================================================
//
//  string.hpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LD_STRING_HPP
#define LD_STRING_HPP

#include <string>
#include "common.hpp"
#include "string_view.hpp"

namespace ld
{
    namespace detail
    {
        template <class StringViewIsh>
        concept is_string_view_ish = requires
        {
            std::is_convertible_v<const StringViewIsh&, string_view>;
            std::negation_v<std::is_convertible<const StringViewIsh&, const char32* const>>;
        };
    }

    class string_view;

    /// @brief UTF-32文字列クラス
    class string final
    {
    public:
        //=========================================================
        //  エイリアス
        //=========================================================
        /// @brief 文字列型
        using string_type = std::u32string;
        /// @brief 文字特性型
        using traits_type = string_type::traits_type;
        /// @brief アロケータ型
        using allocator_type = string_type::allocator_type;
        /// @brief 文字型
        using value_type = string_type::value_type;
        /// @brief 文字のポインタ型
        using pointer = string_type::pointer;
        /// @brief 文字のconstポインタ型
        using const_pointer = string_type::const_pointer;
        /// @brief 文字の参照型
        using reference = string_type::reference;
        /// @brief 文字のconst参照型
        using const_reference = string_type::const_reference;
        /// @brief イテレータ型
        using iterator = string_type::iterator;
        /// @brief constイテレータ型
        using const_iterator = string_type::const_iterator;
        /// @brief 逆順イテレータ型
        using reverse_iterator = string_type::reverse_iterator;
        /// @brief const逆順イテレータ型
        using const_reverse_iterator = string_type::const_reverse_iterator;
        /// @brief 要素数を表す符号なし整数型
        using size_type = string_type::size_type;
        /// @brief イテレータの差を表す符号なし整数型
        using difference_type = string_type::difference_type;

        //=========================================================
        //  定数
        //=========================================================
        /// @brief 無効な位置を表す値
        static constexpr size_type npos{ string_type::npos };

        //=========================================================
        //  コンストラクタ
        //=========================================================
        [[nodiscard]] string() noexcept
            : string_() {}

        [[nodiscard]] /* implicit */ string(const string_type& str)
            : string_(str) {}

        [[nodiscard]] /* implicit */ string(string_type&& str) noexcept
            : string_(std::move(str)) {}

        [[nodiscard]] string(const string& right)
            : string_(right.string_) {}

        [[nodiscard]] string(const string& right, const size_type offset, const size_type count = npos)
            : string_(right.string_, offset, count) {}

        [[nodiscard]] string(string&& right) noexcept
            : string_(std::move(right.string_)) {}

        [[nodiscard]] /* implicit */ string(const value_type* const ptr)
            : string_(ptr) {}

        [[nodiscard]] string(const value_type* const ptr, const size_type count)
            : string_(ptr, count) {}

        [[nodiscard]] string(const size_type count, const value_type c)
            : string_(count, c) {}

        [[nodiscard]] string(std::initializer_list<value_type> ilist)
            : string_(ilist) {}

        template <class Iterator>
        [[nodiscard]] string(Iterator first, Iterator last)
            : string_(first, last) {}

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] /* implicit */ string(const StringViewIsh& strv)
            : string_(strv.data(), strv.size()) {}

        template <class Type>
            requires std::convertible_to<Type, string_view>
        [[nodiscard]] string(const Type& strv, const size_type offset, const size_type count)
            : string(strv.substr(offset, count)) {}

        //=========================================================
        //  デストラクタ
        //=========================================================
        ~string() noexcept = default;

        [[nodiscard]] operator string_view() const noexcept
        {
            return { string_.data(), string_.size() };
        }

        string& assign(const string& right)
        {
            string_.assign(right.string_);
            return *this;
        }

        string& assign(string&& right) noexcept(noexcept(string_.assign(std::move(right.string_))))
        {
            string_.assign(std::move(right.string_));
            return *this;
        }

        string& assign(const string& right, const size_type offset, const size_type count = npos)
        {
            string_.assign(right.string_, offset, count);
            return *this;
        }

        string& assign(const value_type* const ptr)
        {
            string_.assign(ptr);
            return *this;
        }

        string& assign(const value_type* const ptr, const size_type count)
        {
            string_.assign(ptr, count);
            return *this;
        }

        string& assign(const value_type c)
        {
            assign(1, c);
            return *this;
        }

        string& assign(const size_type count, const value_type c)
        {
            string_.assign(count, c);
            return *this;
        }

        string& assign(std::initializer_list<value_type> ilist)
        {
            string_.assign(ilist);
            return *this;
        }

        template <class Iterator>
        string& assign(const Iterator first, const Iterator last)
        {
            string_.assign(first, last);
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& assign(const StringViewIsh& strv)
        {
            assign(strv.data(), strv.size());
            return *this;
        }

        [[nodiscard]] string& operator=(const string& right)
        {
            string_ = right.string_;
            return *this;
        }

        [[nodiscard]] string& operator=(string&& right) noexcept
        {
            string_ = std::move(right.string_);
            return *this;
        }

        [[nodiscard]] string& operator=(const value_type* const ptr)
        {
            string_ = ptr;
            return *this;
        }

        [[nodiscard]] string& operator=(const value_type c)
        {
            string_ = c;
            return *this;
        }

        [[nodiscard]] string& operator=(std::initializer_list<value_type> ilist)
        {
            string_ = ilist;
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] string& operator=(const StringViewIsh& strv)
        {
            string_ = strv;
            return *this;
        }

        string& append(const string& right)
        {
            string_.append(right.string_);
            return *this;
        }

        string& append(const string& right, const size_type offset, const size_type count = npos)
        {
            string_.append(right.string_, offset, count);
            return *this;
        }

        string& append(const value_type* const ptr)
        {
            string_.append(ptr);
            return *this;
        }

        string& append(const value_type* const ptr, const size_type count = npos)
        {
            string_.append(ptr, count);
            return *this;
        }

        string& append(const value_type c)
        {
            push_back(c);
            return *this;
        }

        string& append(const size_type count, const value_type c)
        {
            string_.append(count, c);
            return *this;
        }

        string& append(std::initializer_list<value_type> ilist)
        {
            string_.append(ilist);
            return *this;
        }

        template <class Iterator>
        string& append(const Iterator first, const Iterator last)
        {
            string_.append(first, last);
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& append(const StringViewIsh& strv)
        {
            append(strv.data(), strv.size());
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& append(const StringViewIsh& strv, const size_type offset, const size_type count = npos)
        {
            append(strv.substr(offset, count));
            return *this;
        }

        string& operator+=(const string& right)
        {
            string_ += right.string_;
            return *this;
        }

        string& operator+=(const value_type* ptr)
        {
            string_ += ptr;
            return *this;
        }

        string& operator+=(value_type c)
        {
            string_ += c;
            return *this;
        }

        string& operator+=(std::initializer_list<value_type> ilist)
        {
            string_ += ilist;
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& operator+=(const StringViewIsh& strv)
        {
            append(strv);
            return *this;
        }

        [[nodiscard]] string operator+(const string& right)
        {
            return { string_ + right.string_ };
        }

        [[nodiscard]] string operator+(const value_type* ptr)
        {
            return { string_ + ptr };
        }

        [[nodiscard]] string operator+(value_type c)
        {
            return { string_ + c };
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] string operator+(const StringViewIsh& strv)
        {
            return { string(string_).append(strv) };
        }

        string& insert(const size_type offset, const string& right)
        {
            string_.insert(offset, right.string_);
            return *this;
        }

        string& insert(
                const size_type offset, const string& right, const size_type roffset, const size_type count = npos)
        {
            string_.insert(offset, right.string_, roffset, count);
            return *this;
        }

        string& insert(const size_type offset, const value_type* const ptr)
        {
            string_.insert(offset, ptr);
            return *this;
        }

        string& insert(
                const size_type offset,
                const value_type* const ptr,
                const size_type rcount)
        {
            string_.insert(offset, ptr, rcount);
            return *this;
        }

        string& insert(const size_type offset, const size_type count, const value_type c)
        {
            string_.insert(offset, count, c);
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& insert(const size_type offset, StringViewIsh& strv)
        {
            insert(offset, strv.data(), strv.size());
            return *this;
        }

        iterator insert(
            const_iterator where,
            const value_type* const ptr,
            const size_type rcount)
        {
            return insert(where, ptr, ptr + rcount);
        }

        iterator insert(const_iterator where, const value_type c)
        {
            return string_.insert(where, c);
        }

        iterator insert(const_iterator where, const size_type count, const value_type c)
        {
            return string_.insert(where, count, c);
        }

        iterator insert(const_iterator where, std::initializer_list<value_type> ilist)
        {
            return string_.insert(where, ilist);
        }

        template <class Iterator>
        iterator insert(const_iterator where, Iterator first, Iterator last)
        {
            return string_.insert(where, first, last);
        }

        string& erase(const size_type offset = 0)
        {
            string_.erase(offset);
            return *this;
        }

        string& erase(const size_type offset, const size_type count = npos)
        {
            string_.erase(offset, count);
            return *this;
        }

        iterator erase(const const_iterator where) noexcept
        {
            return string_.erase(where);
        }

        iterator erase(const const_iterator first, const const_iterator last) noexcept
        {
            return string_.erase(first, last);
        }

        void clear() noexcept
        {
            string_.clear();
        }

        string& replace(const size_type offset, const size_type count, const string& right)
        {
            string_.replace(offset, count, right.string_);
            return *this;
        }

        string& replace(
                const size_type offset,
                const size_type count,
                const string& right,
                const size_type roffset,
                const size_type rcount)
        {
            string_.replace(offset, count, right.string_, roffset, rcount);
            return *this;
        }

        string& replace(const size_type offset, const size_type count, const value_type* const ptr)
        {
            string_.replace(offset, count, ptr);
            return *this;
        }

        string& replace(
                const size_type offset,
                const size_type count,
                const value_type* const ptr,
                const size_type rcount)
        {
            string_.replace(offset, count, ptr, rcount);
            return *this;
        }

        string& replace(const size_type offset, const size_type count, const size_type rcount, const value_type c)
        {
            string_.replace(offset, count, rcount, c);
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& replace(const size_type offset, const size_type count, const StringViewIsh& strv)
        {
            return string_.replace(offset, count, strv.view_);
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& replace(
            const size_type offset,
            const size_type count,
            const StringViewIsh& strv,
            const size_type roffset,
            const size_type rcount = npos)
        {
            return string_.replace(offset, count, strv.view_, roffset, rcount);
        }

        string& replace(const const_iterator first, const const_iterator last, const string& right)
        {
            string_.replace(first, last, right.string_);
            return *this;
        }

        string& replace(const const_iterator first, const const_iterator last, const value_type* const ptr)
        {
            string_.replace(first, last, ptr);
            return *this;
        }

        string& replace(
                const const_iterator first,
                const const_iterator last,
                const value_type* const ptr,
                const size_type count)
        {
            string_.replace(first, last, ptr, count);
            return *this;
        }

        string& replace(
                const const_iterator first,
                const const_iterator last,
                const size_type count,
                const value_type c)
        {
            string_.replace(first, last, count, c);
            return *this;
        }

        template <class Iterator>
        string& replace(
                const const_iterator first,
                const const_iterator last,
                const Iterator rfirst,
                const Iterator rlast)
        {
            string_.replace(first, last, rfirst, rlast);
            return *this;
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& replace(const const_iterator first, const const_iterator last, const StringViewIsh& strv)
        {
            return string_.replace(first, last, strv.view_);
        }

        template <detail::is_string_view_ish StringViewIsh>
        string& replace(
            const const_iterator first,
            const const_iterator last,
            const StringViewIsh& strv,
            const size_type roffset,
            const size_type rcount = npos)
        {
            return string_.replace(first, last, strv.view_, roffset, rcount);
        }

        [[nodiscard]] iterator begin() noexcept
        {
            return string_.begin();
        }

        [[nodiscard]] const_iterator begin() const noexcept
        {
            return string_.begin();
        }

        [[nodiscard]] iterator end() noexcept
        {
            return string_.end();
        }

        [[nodiscard]] const_iterator end() const noexcept
        {
            return string_.end();
        }

        [[nodiscard]] const_iterator cbegin() const noexcept
        {
            return string_.cbegin();
        }

        [[nodiscard]] const_iterator cend() const noexcept
        {
            return string_.cend();
        }

        [[nodiscard]] reverse_iterator rbegin() noexcept
        {
            return string_.rbegin();
        }

        [[nodiscard]] const_reverse_iterator rbegin() const noexcept
        {
            return string_.rbegin();
        }

        [[nodiscard]] reverse_iterator rend() noexcept
        {
            return string_.rend();
        }

        [[nodiscard]] const_reverse_iterator rend() const noexcept
        {
            return string_.rend();
        }

        [[nodiscard]] const_reverse_iterator crbegin() const noexcept
        {
            return string_.crbegin();
        }

        [[nodiscard]] const_reverse_iterator crend() const noexcept
        {
            return string_.crend();
        }

        void shrink_to_fit()
        {
            string_.shrink_to_fit();
        }

        [[nodiscard]] value_type& at(const size_type offset)
        {
            return string_.at(offset);
        }

        [[nodiscard]] const value_type& at(const size_type offset) const
        {
            return string_.at(offset);
        }

        [[nodiscard]] value_type& operator[](const size_type offset) &
        {
            return string_[offset];
        }

        [[nodiscard]] const value_type& operator[](const size_type offset) const &
        {
            return string_[offset];
        }

        [[nodiscard]] value_type operator[](const size_type offset) &&
        {
            return std::move(string_[offset]);
        }

        void push_front(const value_type c)
        {
            insert(begin(), c);
        }

        void push_back(const value_type c)
        {
            string_.push_back(c);
        }

        void pop_front() noexcept
        {
            string_.erase(begin());
        }

        void pop_front(const size_type count) noexcept
        {
            string_.erase(begin(), begin() + std::min<size_type>(count, size()));
        }

        void pop_back() noexcept
        {
            string_.pop_back();
        }

        void pop_back(const size_type count) noexcept
        {
            string_.erase(end() - std::min<size_type>(count, size()), end());
        }

        [[nodiscard]] value_type& front() noexcept
        {
            return string_.front();
        }

        [[nodiscard]] const value_type& front() const noexcept
        {
            return string_.front();
        }

        [[nodiscard]] value_type& back() noexcept
        {
            return string_.back();
        }

        [[nodiscard]] const value_type& back() const noexcept
        {
            return string_.back();
        }

        [[nodiscard]] string_type& str() noexcept
        {
            return string_;
        }

        [[nodiscard]] const string_type& str() const noexcept
        {
            return string_;
        }

        [[nodiscard]] const value_type* c_str() const noexcept
        {
            return string_.c_str();
        }

        [[nodiscard]] value_type* data() noexcept
        {
            return string_.data();
        }

        [[nodiscard]] const value_type* data() const noexcept
        {
            return string_.data();
        }

        [[nodiscard]] size_type length() const noexcept
        {
            return string_.length();
        }

        [[nodiscard]] size_type size() const noexcept
        {
            return string_.size();
        }

        [[nodiscard]] size_type max_size() const noexcept
        {
            return string_.max_size();
        }

        void resize(const size_type new_size, const value_type c = value_type{})
        {
            string_.resize(new_size, c);
        }

        [[nodiscard]] size_type capacity() const noexcept
        {
            return string_.capacity();
        }

        void reserve(const size_type new_capacity)
        {
            string_.reserve(new_capacity);
        }

        [[nodiscard]] bool empty() const noexcept
        {
            return string_.empty();
        }

        size_type copy(value_type* const ptr, const size_type count, const size_type offset = 0) const
        {
            return string_.copy(ptr, count, offset);
        }

        void swap(string& right) noexcept
        {
            string_.swap(right.string_);
        }

        [[nodiscard]] size_type find(const string& right, const size_type offset = 0) const noexcept
        {
            return string_.find(right.string_, offset);
        }

        [[nodiscard]] size_type find(const value_type* const ptr, const size_type offset = 0) const noexcept
        {
            return string_.find(ptr, offset);
        }

        [[nodiscard]] size_type find(
                const value_type* const ptr, const size_type offset, const size_type count) const noexcept
        {
            return string_.find(ptr, offset, count);
        }

        [[nodiscard]] size_type find(const value_type c, const size_type offset = 0) const noexcept
        {
            return string_.find(c, offset);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] size_type find(const StringViewIsh& strv, const size_type offset = 0) const noexcept
        {
            return string_.find(strv.view_, offset);
        }

        [[nodiscard]] size_type rfind(const string& right, const size_type offset = 0) const noexcept
        {
            return string_.rfind(right.string_, offset);
        }

        [[nodiscard]] size_type rfind(const value_type* const ptr, const size_type offset = 0) const noexcept
        {
            return string_.rfind(ptr, offset);
        }

        [[nodiscard]] size_type rfind(
                const value_type* const ptr, const size_type offset, const size_type count) const noexcept
        {
            return string_.rfind(ptr, offset, count);
        }

        [[nodiscard]] size_type rfind(const value_type c, const size_type offset = 0) const noexcept
        {
            return string_.rfind(c, offset);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] size_type rfind(const StringViewIsh& strv, const size_type offset = 0) const noexcept
        {
            return string_.rfind(strv.view_, offset);
        }

        [[nodiscard]] size_type find_first_of(const string& right, const size_type offset = 0) const noexcept
        {
            return string_.find_first_of(right.string_, offset);
        }

        [[nodiscard]] size_type find_first_of(const value_type* const ptr, const size_type offset = 0) const noexcept
        {
            return string_.find_first_of(ptr, offset);
        }

        [[nodiscard]] size_type find_first_of(
                const value_type* const ptr, const size_type offset, const size_type count) const noexcept
        {
            return string_.find_first_of(ptr, offset, count);
        }

        [[nodiscard]] size_type find_first_of(const value_type c, const size_type offset = 0) const noexcept
        {
            return string_.find_first_of(c, offset);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] size_type find_first_of(const StringViewIsh& strv, const size_type offset = 0) const noexcept
        {
            return string_.find_first_of(strv.view_, offset);
        }

        [[nodiscard]] size_type find_last_of(const string& right, const size_type offset = 0) const noexcept
        {
            return string_.find_last_of(right.string_, offset);
        }

        [[nodiscard]] size_type find_last_of(const value_type* const ptr, const size_type offset = 0) const noexcept
        {
            return string_.find_last_of(ptr, offset);
        }

        [[nodiscard]] size_type find_last_of(
                const value_type* const ptr, const size_type offset, const size_type count) const noexcept
        {
            return string_.find_last_of(ptr, offset, count);
        }

        [[nodiscard]] size_type find_last_of(const value_type c, const size_type offset = 0) const noexcept
        {
            return string_.find_last_of(c, offset);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] size_type find_last_of(const StringViewIsh& strv, const size_type offset = 0) const noexcept
        {
            return string_.find_last_of(strv.view_, offset);
        }

        [[nodiscard]] size_type find_first_not_of(const string& right, const size_type offset = 0) const noexcept
        {
            return string_.find_first_not_of(right.string_, offset);
        }

        [[nodiscard]] size_type find_first_not_of(
                const value_type* const ptr, const size_type offset = 0) const noexcept
        {
            return string_.find_first_not_of(ptr, offset);
        }

        [[nodiscard]] size_type find_first_not_of(
                const value_type* const ptr, const size_type offset, const size_type count) const noexcept
        {
            return string_.find_first_not_of(ptr, offset, count);
        }

        [[nodiscard]] size_type find_first_not_of(const value_type c, const size_type offset = 0) const noexcept
        {
            return string_.find_first_not_of(c, offset);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] size_type find_first_not_of(const StringViewIsh& strv, const size_type offset = 0) const noexcept
        {
            return string_.find_first_not_of(strv.view_, offset);
        }

        [[nodiscard]] size_type find_last_not_of(const string& right, const size_type offset = 0) const noexcept
        {
            return string_.find_last_not_of(right.string_, offset);
        }

        [[nodiscard]] size_type find_last_not_of(const value_type* const ptr, const size_type offset = 0) const noexcept
        {
            return string_.find_last_not_of(ptr, offset);
        }

        [[nodiscard]] size_type find_last_not_of(
                const value_type* const ptr, const size_type offset, const size_type count) const noexcept
        {
            return string_.find_last_not_of(ptr, offset, count);
        }

        [[nodiscard]] size_type find_last_not_of(const value_type c, const size_type offset = 0) const noexcept
        {
            return string_.find_last_not_of(c, offset);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] size_type find_last_not_of(const StringViewIsh& strv, const size_type offset = 0) const noexcept
        {
            return string_.find_last_not_of(strv.view_, offset);
        }

        [[nodiscard]] string substr(const size_type offset, const size_type count = npos) const
        {
            return { string_.substr(offset, count) };
        }

        [[nodiscard]] int32 compare(const string& right) const noexcept
        {
            return string_.compare(right.string_);
        }

        [[nodiscard]] int32 compare(const size_type offset, const size_type count, const string& right) const noexcept
        {
            return string_.compare(offset, count, right.string_);
        }

        [[nodiscard]] int32 compare(
                const size_type offset,
                const size_type count,
                const string& right,
                const size_type roffset,
                const size_type rcount) const noexcept
        {
            return string_.compare(offset, count, right.string_, roffset, rcount);
        }

        [[nodiscard]] int32 compare(const value_type* const ptr) const noexcept
        {
            return string_.compare(ptr);
        }

        [[nodiscard]] int32 compare(
                const size_type offset, const size_type count, const value_type* const ptr) const noexcept
        {
            return string_.compare(offset, count, ptr);
        }

        [[nodiscard]] int32 compare(
                const size_type offset,
                const size_type count,
                const value_type* const ptr,
                const size_type rcount) const noexcept
        {
            return string_.compare(offset, count, ptr, rcount);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] int32 compare(const StringViewIsh& strv) const noexcept
        {
            return string_.compare(0, npos, strv.data(), strv.size());
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] int32 compare(
            const size_type offset, const size_type count, const StringViewIsh& strv) const noexcept
        {
            return string_.compare(offset, count, strv.data(), strv.size());
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] int32 compare(
            const size_type offset,
            const size_type count,
            const StringViewIsh& strv,
            const size_type roffset,
            const size_type rcount = npos) const noexcept
        {
            const size_t size = strv.size();
            if (size)
                return compare(offset, count, strv.substr(roffset, count));
        }

        [[nodiscard]] bool operator==(const string& right) const noexcept
        {
            return string_ == right.string_;
        }

        [[nodiscard]] bool operator==(const value_type* const ptr) const noexcept
        {
            return string_ == ptr;
        }

        [[nodiscard]] std::strong_ordering operator<=>(const string& right) const noexcept
        {
            return string_ <=> right.string_;
        }

        [[nodiscard]] std::strong_ordering operator<=>(const value_type* const ptr) const noexcept
        {
            return string_ <=> ptr;
        }

        [[nodiscard]] bool starts_with(const string& right) const noexcept
        {
            return string_.starts_with(right.string_);
        }

        [[nodiscard]] bool starts_with(const value_type* const ptr) const noexcept
        {
            return string_.starts_with(ptr);
        }

        [[nodiscard]] bool starts_with(const value_type c) const noexcept
        {
            return (front() == c);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] bool starts_with(const StringViewIsh& strv) const noexcept
        {
            const size_type rsize = strv.size();
            if (size() < rsize)
                return false;
            return compare(0, rsize, strv.data(), rsize);
        }

        [[nodiscard]] bool ends_with(const string& right) const noexcept
        {
            return string_.ends_with(right.string_);
        }

        [[nodiscard]] bool ends_with(const value_type* const ptr) const noexcept
        {
            return string_.ends_with(ptr);
        }

        [[nodiscard]] bool ends_with(const value_type c) const noexcept
        {
            return (back() == c);
        }

        template <detail::is_string_view_ish StringViewIsh>
        [[nodiscard]] bool ends_with(const StringViewIsh& strv) const noexcept
        {
            const size_type mysize = size();
            const size_type rsize = strv.size();
            if (mysize < rsize)
                return false;
            return compare(mysize - rsize, mysize, strv.data(), rsize);
        }

        [[nodiscard]] allocator_type get_allocator() const noexcept
        {
            return string_.get_allocator();
        }

    private:
        string_type string_;
    };

    inline namespace literals
    {
        inline namespace string_literals
        {
            [[nodiscard]] inline string operator""_s(const char32* const ptr, const size_t length)
            {
                return { ptr, length };
            }
        }
    }
} // namespace ld

template <>
inline void std::swap(ld::string& a, ld::string& b) noexcept
{
    a.swap(b);
}

template <>
struct std::hash<ld::string>
{
    [[nodiscard]] size_t operator()(const ld::string& value) const noexcept
    {
        return std::hash<std::u32string>{}(value.str());
    }
};

#endif // LD_STRING_HPP