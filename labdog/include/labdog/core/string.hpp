//=========================================================
//
//  string.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_STRING_HPP
#define LABDOG_STRING_HPP

#include <string>
#include <fmt/format.h>
#include "common.hpp"
#include "string_view.hpp"
#include "charset_convert.hpp"

namespace ld
{
    class string;

    namespace detail
    {
        template <class Type>
        concept is_string_view = requires
        {
            std::is_convertible_v<const Type&, string_view>;
            std::negation_v<std::is_convertible<const Type*, const string*>>;
            std::negation_v<std::is_convertible<const Type&, const char8*>>;
        };
    }

    /// @brief Unicode文字列
    class string final
    {
    public:
        //=========================================================
        //  エイリアス
        //=========================================================
        /// @brief 文字列型
        using string_type = std::basic_string<char8>;
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
        /// @brief 空の文字列を構築する
        [[nodiscard]] string() noexcept
            : string_() {}

        /// @brief 文字列をコピー構築する
        /// @param str コピー元の文字列
        [[nodiscard]] string(const string& str)
            : string_(str.string_) {}

        /// @brief 範囲を指定して文字列をコピー構築する
        /// @param str コピー元の文字列
        /// @param pos コピー範囲の開始位置
        /// @param n コピー範囲の要素数
        [[nodiscard]] string(const string& str, const size_type pos, const size_type n = npos)
            : string_(str.string_, pos, n) {}

        /// @brief 文字列をムーブ構築する
        /// @param str ムーブ元の文字列型
        [[nodiscard]] string(string&& str) noexcept
            : string_(std::move(str.string_)) {}

        /// @brief STLの文字列から文字列をコピー構築する
        /// @param str コピー元のSTLの文字列
        [[nodiscard]] /* implicit */ string(const string_type& str)
            : string_(str) {}

        /// @brief STLの文字列から文字列をムーブ構築する
        /// @param str ムーブ元のSTLの文字列
        [[nodiscard]] /* implicit */ string(string_type&& str) noexcept
            : string_(std::move(str)) {}

        /// @brief 文字配列から文字列を構築する
        /// @param ptr 文字配列の先頭ポインタ
        [[nodiscard]] /* implicit */ string(const value_type* const ptr)
            : string_(ptr) {}

        /// @brief 範囲を指定して文字配列から文字列を構築する
        /// @param ptr 文字配列の先頭ポインタ
        /// @param n 範囲の要素数
        [[nodiscard]] string(const value_type* const ptr, const size_type n)
            : string_(ptr, n) {}

        /// @brief 指定した値からなる要素数Nの文字列を構築する
        /// @param n 要素数
        /// @param c 要素の値
        [[nodiscard]] string(const size_type n, const value_type c)
            : string_(n, c) {}

        /// @brief 初期化リストから文字列を構築する
        /// @param il 初期化リスト
        [[nodiscard]] string(std::initializer_list<value_type> il)
            : string_(il) {}

        /// @brief イテレータの範囲から文字列を構築する
        /// @param first 範囲の開始位置を指すイテレータ
        /// @param last 範囲の末尾位置の次を指すイテレータ
        template <class Iterator>
        [[nodiscard]] string(Iterator first, Iterator last)
            : string_(first, last) {}

        /// @brief 文字列ビューから文字列を構築する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 文字列ビュー
        template <detail::is_string_view StringView>
        [[nodiscard]] /* implicit */ string(const StringView& sv)
            : string_(sv) {}

        /// @brief 範囲を指定して文字列ビューから文字列を構築する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 文字列ビュー
        /// @param pos コピー範囲の開始位置
        /// @param n コピー範囲の要素数
        template <detail::is_string_view StringView>
        [[nodiscard]] string(const StringView& sv, const size_type pos, const size_type n = npos)
            : string_(sv, pos, n) {}

        //=========================================================
        //  デストラクタ
        //=========================================================
        /// @brief 文字列を破棄する
        ~string() noexcept = default;

        /// @brief string_viewへの暗黙型キャスト
        /// @return 文字列を参照したstring_view
        [[nodiscard]] /* implicit */ operator string_view() const noexcept
        {
            return { string_.data(), string_.size() };
        }

        /// @brief STLの文字列への暗黙型キャスト
        /// @return 文字列をコピーしたSTLの文字列
        [[nodiscard]] /* implicit */ operator string_type() const noexcept
        {
            return string_;
        }

        /// @brief 文字列を代入する
        /// @param str 代入元の文字列
        /// @return *this
        string& assign(const string& str)
        {
            string_.assign(str.string_);
            return *this;
        }

        /// @brief 文字列をムーブ代入する
        /// @param str ムーブ代入元の文字列
        /// @return *this
        string& assign(string&& str) noexcept(noexcept(string_.assign(std::move(str.string_))))
        {
            string_.assign(std::move(str.string_));
            return *this;
        }

        /// @brief 範囲を指定して文字列を代入する
        /// @param str 代入元の文字列
        /// @param pos 代入する範囲の開始位置
        /// @param n 代入する範囲の要素数
        /// @return *this
        string& assign(const string& str, const size_type pos, const size_type n = npos)
        {
            string_.assign(str.string_, pos, n);
            return *this;
        }

        /// @brief 文字配列を代入する
        /// @param ptr 代入元の文字配列
        /// @return *this
        string& assign(const value_type* const ptr)
        {
            string_.assign(ptr);
            return *this;
        }

        /// @brief 文字配列を代入する
        /// @param ptr 代入元の文字配列
        /// @param n 代入する範囲の要素数
        /// @return *this
        string& assign(const value_type* const ptr, const size_type n)
        {
            string_.assign(ptr, n);
            return *this;
        }

        /// @brief 文字を代入する
        /// @param c 代入元の文字
        /// @return *this
        string& assign(const value_type c)
        {
            string_.assign(1, c);
            return *this;
        }

        /// @brief 指定した値からなる要素数Nの文字列を代入する
        /// @param n 代入する要素数
        /// @param c 代入する要素の値
        /// @return *this
        string& assign(const size_type n, const value_type c)
        {
            string_.assign(n, c);
            return *this;
        }

        /// @brief 初期化リストを代入する
        /// @param il 代入元の初期化リスト
        /// @return *this
        string& assign(std::initializer_list<value_type> il)
        {
            string_.assign(il);
            return *this;
        }

        /// @brief イテレータの範囲を代入する
        /// @param first 範囲の開始位置を指すイテレータ
        /// @param last 範囲の末尾位置の次を指すイテレータ
        /// @return *this
        template <class Iterator>
        string& assign(const Iterator first, const Iterator last)
        {
            string_.assign(first, last);
            return *this;
        }

        /// @brief 文字列ビューを代入する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 代入元の文字列ビュー
        /// @return *this
        template <detail::is_string_view StringView>
        string& assign(const StringView& sv)
        {
            string_.assign(sv);
            return *this;
        }

        /// @brief 範囲を指定して文字列ビューを代入する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 代入元の文字列ビュー
        /// @param pos 代入する範囲の開始位置
        /// @param n 代入する範囲の要素数
        /// @return *this
        template <detail::is_string_view StringView>
        string& assign(const StringView& sv, const size_type pos, const size_type n = npos)
        {
            string_.assign(sv, pos, n);
            return *this;
        }

        /// @brief 文字列を代入する
        /// @param str 代入元の文字列
        /// @return *this
        string& operator=(const string& str)
        {
            return assign(str);
        }

        /// @brief 文字列をムーブ代入する
        /// @param str ムーブ代入元の文字列
        /// @return *this
        string& operator=(string&& str) noexcept
        {
            return assign(std::move(str));
        }

        /// @brief 文字配列を代入する
        /// @param ptr 代入元の文字配列
        /// @return *this
        string& operator=(const value_type* const ptr)
        {
            return assign(ptr);
        }

        /// @brief 文字を代入する
        /// @param c 代入元の文字
        /// @return *this
        string& operator=(const value_type c)
        {
            return assign(c);
        }

        /// @brief 初期化リストを代入する
        /// @param il 代入元の初期化リスト
        /// @return *this
        string& operator=(std::initializer_list<value_type> il)
        {
            return assign(il);
        }

        /// @brief 文字列ビューを代入する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 代入元の文字列ビュー
        /// @return *this
        template <detail::is_string_view StringView>
        string& operator=(const StringView& sv)
        {
            return assign(sv);
        }

        /// @brief 文字列を末尾に結合する
        /// @param str 結合する文字列
        /// @return *this
        string& append(const string& str)
        {
            string_.append(str.string_);
            return *this;
        }

        /// @brief 範囲を指定して文字列を末尾に結合する
        /// @param str 結合する文字列
        /// @param pos 結合する範囲の開始位置
        /// @param n 結合する範囲の要素数
        /// @return *this
        string& append(const string& str, const size_type pos, const size_type n = npos)
        {
            string_.append(str.string_, pos, n);
            return *this;
        }

        /// @brief 文字配列を末尾に結合する
        /// @param ptr 結合する文字配列
        /// @return *this
        string& append(const value_type* const ptr)
        {
            string_.append(ptr);
            return *this;
        }

        /// @brief 範囲を指定して文字配列を末尾に結合する
        /// @param ptr 結合する文字配列
        /// @param n 結合する範囲の要素数
        /// @return *this
        string& append(const value_type* const ptr, const size_type n)
        {
            string_.append(ptr, n);
            return *this;
        }

        /// @brief 文字を末尾に結合する
        /// @param c 結合する文字
        /// @return *this
        string& append(const value_type c)
        {
            push_back(c);
            return *this;
        }

        /// @brief 指定した値からなる要素数Nの文字列を末尾に結合する
        /// @param n 結合する要素数
        /// @param c 結合する要素の値
        /// @return *this
        string& append(const size_type n, const value_type c)
        {
            string_.append(n, c);
            return *this;
        }

        /// @brief 初期化リストを末尾に結合する
        /// @param il 初期化リスト
        /// @return *this
        string& append(std::initializer_list<value_type> il)
        {
            string_.append(il);
            return *this;
        }

        /// @brief イテレータの範囲を末尾に結合する
        /// @param first 範囲の開始位置を指すイテレータ
        /// @param last 範囲の末尾位置の次を指すイテレータ
        /// @return *this
        template <class Iterator>
        string& append(const Iterator first, const Iterator last)
        {
            string_.append(first, last);
            return *this;
        }

        /// @brief 文字列ビューを末尾に結合する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 結合する文字列ビュー
        /// @return *this
        template <detail::is_string_view StringView>
        string& append(const StringView& sv)
        {
            string_.append(sv);
            return *this;
        }

        /// @brief 文字列ビューを末尾に結合する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 結合する文字列ビュー
        /// @param pos 結合する範囲の開始位置
        /// @param n 結合する範囲の要素数
        /// @return *this
        template <detail::is_string_view StringView>
        string& append(const StringView& sv, const size_type pos, const size_type n = npos)
        {
            string_.append(sv, pos, n);
            return *this;
        }

        /// @brief 文字列を末尾に結合する
        /// @param str 結合する文字列
        /// @return *this
        string& operator+=(const string& str)
        {
            string_ += str.string_;
            return *this;
        }

        /// @brief 文字配列を末尾に結合する
        /// @param ptr 結合する文字配列
        /// @return *this
        string& operator+=(const value_type* str)
        {
            string_ += str;
            return *this;
        }

        /// @brief 文字を末尾に結合する
        /// @param c 結合する文字
        /// @return *this
        string& operator+=(value_type c)
        {
            string_ += c;
            return *this;
        }

        /// @brief 初期化リストを末尾に結合する
        /// @param il 初期化リスト
        /// @return *this
        string& operator+=(std::initializer_list<value_type> il)
        {
            string_ += il;
            return *this;
        }

        /// @brief 文字列ビューを末尾に結合する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 結合する文字列ビュー
        /// @return *this
        template <detail::is_string_view StringView>
        string& operator+=(const StringView& sv)
        {
            string_ += sv;
            return *this;
        }

        /// @brief 文字列を末尾に結合した文字列を構築する
        /// @param str 結合する文字列
        /// @return 結合した文字列
        [[nodiscard]] string operator+(const string& str)
        {
            string res(*this);
            res.append(str);
            return res;
        }

        /// @brief 文字配列を末尾に結合した文字列を構築する
        /// @param str 結合する文字配列
        /// @return 結合した文字列
        [[nodiscard]] string operator+(const value_type* str)
        {
            string res(*this);
            res.append(str);
            return res;
        }

        /// @brief 文字を末尾に結合した文字列を構築する
        /// @param c 結合する文字
        /// @return 結合した文字列
        [[nodiscard]] string operator+(value_type c)
        {
            string res(*this);
            res.append(c);
            return res;
        }

        /// @brief 文字列ビューを末尾に結合した文字列を構築する
        /// @tparam StringView 文字列ビューに変換可能な型
        /// @param sv 結合する文字列ビュー
        /// @return 結合した文字列
        template <detail::is_string_view StringView>
        [[nodiscard]] string operator+(const StringView& sv)
        {
            string res(*this);
            res.append(sv);
            return res;
        }

        string& insert(const size_type pos, const string& str)
        {
            string_.insert(pos, str.string_);
            return *this;
        }

        string& insert(
            const size_type pos1, const string& str, const size_type pos2, const size_type n = npos)
        {
            string_.insert(pos1, str.string_, pos2, n);
            return *this;
        }

        string& insert(const size_type pos, const value_type* const ptr)
        {
            string_.insert(pos, ptr);
            return *this;
        }

        string& insert(
                const size_type pos,
                const value_type* const ptr,
                const size_type n)
        {
            string_.insert(pos, ptr, n);
            return *this;
        }

        string& insert(const size_type pos, const value_type c)
        {
            insert(pos, 1, c);
            return *this;
        }

        string& insert(const size_type pos, const size_type n, const value_type c)
        {
            string_.insert(pos, n, c);
            return *this;
        }

        template <detail::is_string_view StringView>
        string& insert(const size_type pos, StringView& sv)
        {
            string_.insert(pos, sv);
            return *this;
        }

        template <detail::is_string_view StringView>
        string& insert(const size_type pos1, StringView& sv, const size_type pos2, const size_type n = npos)
        {
            string_.insert(pos1, sv, pos2, n);
            return *this;
        }

        iterator insert(const_iterator where, const value_type c)
        {
            return string_.insert(where, c);
        }

        iterator insert(const_iterator where, const size_type n, const value_type c)
        {
            return string_.insert(where, n, c);
        }

        iterator insert(const_iterator where, std::initializer_list<value_type> il)
        {
            return string_.insert(where, il);
        }

        template <class Iterator>
        iterator insert(const_iterator where, Iterator first, Iterator last)
        {
            return string_.insert(where, first, last);
        }

        string& erase(const size_type pos = 0)
        {
            string_.erase(pos);
            return *this;
        }

        string& erase(const size_type pos, const size_type n = npos)
        {
            string_.erase(pos, n);
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

        string& replace(const size_type pos, const size_type n, const string& str)
        {
            string_.replace(pos, n, str.string_);
            return *this;
        }

        string& replace(
                const size_type pos1,
                const size_type n1,
                const string& str,
                const size_type pos2,
                const size_type n2 = npos)
        {
            string_.replace(pos1, n1, str.string_, pos2, n2);
            return *this;
        }

        string& replace(const size_type pos, const size_type n, const value_type* const ptr)
        {
            string_.replace(pos, n, ptr);
            return *this;
        }

        string& replace(
                const size_type pos,
                const size_type n1,
                const value_type* const ptr,
                const size_type n2)
        {
            string_.replace(pos, n1, ptr, n2);
            return *this;
        }

        string& replace(const size_type pos, const size_type n1, const size_type n2, const value_type c)
        {
            string_.replace(pos, n1, n2, c);
            return *this;
        }

        template <detail::is_string_view StringView>
        string& replace(const size_type pos, const size_type n, const StringView& sv)
        {
            return string_.replace(pos, n, sv);
        }

        template <detail::is_string_view StringView>
        string& replace(
            const size_type pos1,
            const size_type n1,
            const StringView& sv,
            const size_type pos2,
            const size_type n2 = npos)
        {
            return string_.replace(pos1, n1, sv, pos2, n2);
        }

        string& replace(const const_iterator first, const const_iterator last, const string& str)
        {
            string_.replace(first, last, str.string_);
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
                const size_type n)
        {
            string_.replace(first, last, ptr, n);
            return *this;
        }

        string& replace(
                const const_iterator first,
                const const_iterator last,
                const size_type n,
                const value_type c)
        {
            string_.replace(first, last, n, c);
            return *this;
        }

        template <class Iterator>
        string& replace(
                const const_iterator first1,
                const const_iterator last1,
                const Iterator first2,
                const Iterator last2)
        {
            string_.replace(first1, last1, first2, last2);
            return *this;
        }

        template <detail::is_string_view StringView>
        string& replace(const const_iterator first, const const_iterator last, const StringView& sv)
        {
            return string_.replace(first, last, sv);
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

        [[nodiscard]] value_type& at(const size_type pos)
        {
            return string_.at(pos);
        }

        [[nodiscard]] const value_type& at(const size_type pos) const
        {
            return string_.at(pos);
        }

        [[nodiscard]] value_type& operator[](const size_type pos) &
        {
            return string_[pos];
        }

        [[nodiscard]] const value_type& operator[](const size_type pos) const &
        {
            return string_[pos];
        }

        [[nodiscard]] value_type operator[](const size_type pos) &&
        {
            return std::move(string_[pos]);
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

        void pop_front(const size_type n) noexcept
        {
            string_.erase(begin(), begin() + std::min<size_t>(n, size()));
        }

        void pop_back() noexcept
        {
            string_.pop_back();
        }

        void pop_back(const size_type n) noexcept
        {
            string_.erase(end() - std::min<size_t>(n, size()), end());
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

        [[nodiscard]] string_type& str() noexcept
        {
            return string_;
        }

        [[nodiscard]] const string_type& str() const noexcept
        {
            return string_;
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

        size_type copy(value_type* const ptr, const size_type n, const size_type pos = 0) const
        {
            return string_.copy(ptr, n, pos);
        }

        void swap(string& str) noexcept
        {
            string_.swap(str.string_);
        }

        [[nodiscard]] size_type find(const string& str, const size_type pos = 0) const noexcept
        {
            return string_.find(str.string_, pos);
        }

        [[nodiscard]] size_type find(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return string_.find(ptr, pos);
        }

        [[nodiscard]] size_type find(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return string_.find(ptr, pos, n);
        }

        [[nodiscard]] size_type find(const value_type c, const size_type pos = 0) const noexcept
        {
            return string_.find(c, pos);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] size_type find(const StringView& sv, const size_type pos = 0) const noexcept
        {
            return string_.find(sv, pos);
        }

        [[nodiscard]] size_type rfind(const string& str, const size_type pos = 0) const noexcept
        {
            return string_.rfind(str.string_, pos);
        }

        [[nodiscard]] size_type rfind(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return string_.rfind(ptr, pos);
        }

        [[nodiscard]] size_type rfind(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return string_.rfind(ptr, pos, n);
        }

        [[nodiscard]] size_type rfind(const value_type c, const size_type pos = 0) const noexcept
        {
            return string_.rfind(c, pos);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] size_type rfind(const StringView& sv, const size_type pos = 0) const noexcept
        {
            return string_.rfind(sv, pos);
        }

        [[nodiscard]] size_type find_first_of(const string& str, const size_type pos = 0) const noexcept
        {
            return string_.find_first_of(str.string_, pos);
        }

        [[nodiscard]] size_type find_first_of(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return string_.find_first_of(ptr, pos);
        }

        [[nodiscard]] size_type find_first_of(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return string_.find_first_of(ptr, pos, n);
        }

        [[nodiscard]] size_type find_first_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return string_.find_first_of(c, pos);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] size_type find_first_of(const StringView& sv, const size_type pos = 0) const noexcept
        {
            return string_.find_first_of(sv, pos);
        }

        [[nodiscard]] size_type find_last_of(const string& str, const size_type pos = 0) const noexcept
        {
            return string_.find_last_of(str.string_, pos);
        }

        [[nodiscard]] size_type find_last_of(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return string_.find_last_of(ptr, pos);
        }

        [[nodiscard]] size_type find_last_of(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return string_.find_last_of(ptr, pos, n);
        }

        [[nodiscard]] size_type find_last_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return string_.find_last_of(c, pos);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] size_type find_last_of(const StringView& sv, const size_type pos = 0) const noexcept
        {
            return string_.find_last_of(sv, pos);
        }

        [[nodiscard]] size_type find_first_not_of(const string& str, const size_type pos = 0) const noexcept
        {
            return string_.find_first_not_of(str.string_, pos);
        }

        [[nodiscard]] size_type find_first_not_of(
                const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return string_.find_first_not_of(ptr, pos);
        }

        [[nodiscard]] size_type find_first_not_of(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return string_.find_first_not_of(ptr, pos, n);
        }

        [[nodiscard]] size_type find_first_not_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return string_.find_first_not_of(c, pos);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] size_type find_first_not_of(const StringView& sv, const size_type pos = 0) const noexcept
        {
            return string_.find_first_not_of(sv, pos);
        }

        [[nodiscard]] size_type find_last_not_of(const string& str, const size_type pos = 0) const noexcept
        {
            return string_.find_last_not_of(str.string_, pos);
        }

        [[nodiscard]] size_type find_last_not_of(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return string_.find_last_not_of(ptr, pos);
        }

        [[nodiscard]] size_type find_last_not_of(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return string_.find_last_not_of(ptr, pos, n);
        }

        [[nodiscard]] size_type find_last_not_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return string_.find_last_not_of(c, pos);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] size_type find_last_not_of(const StringView& sv, const size_type pos = 0) const noexcept
        {
            return string_.find_last_not_of(sv, pos);
        }

        [[nodiscard]] string substr(const size_type pos, const size_type n = npos) const
        {
            return string_.substr(pos, npos);
        }

        [[nodiscard]] int32 compare(const string& str) const noexcept
        {
            return string_.compare(str.string_);
        }

        [[nodiscard]] int32 compare(const size_type pos, const size_type n, const string& str) const noexcept
        {
            return string_.compare(pos, n, str.string_);
        }

        [[nodiscard]] int32 compare(
                const size_type pos1,
                const size_type n1,
                const string& str,
                const size_type pos2,
                const size_type n2) const noexcept
        {
            return string_.compare(pos1, n1, str.string_, pos2, n2);
        }

        [[nodiscard]] int32 compare(const value_type* const ptr) const noexcept
        {
            return string_.compare(ptr);
        }

        [[nodiscard]] int32 compare(
                const size_type pos, const size_type n, const value_type* const ptr) const noexcept
        {
            return string_.compare(pos, n, ptr);
        }

        [[nodiscard]] int32 compare(
                const size_type pos,
                const size_type n1,
                const value_type* const ptr,
                const size_type n2) const noexcept
        {
            return string_.compare(pos, n1, ptr, n2);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] int32 compare(const StringView& sv) const noexcept
        {
            return string_.compare(sv);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] int32 compare(
            const size_type pos, const size_type n, const StringView& sv) const noexcept
        {
            return string_.compare(pos, n, sv);
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] int32 compare(
            const size_type pos1,
            const size_type n1,
            const StringView& sv,
            const size_type pos2,
            const size_type n2 = npos) const noexcept
        {
            return string_.compare(pos1, n1, sv, pos2, n2);
        }

        [[nodiscard]] bool operator==(const string& str) const noexcept
        {
            return string_ == str.string_;
        }

        [[nodiscard]] bool operator==(const value_type* const ptr) const noexcept
        {
            return string_ == ptr;
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] bool operator==(const StringView sv) const noexcept
        {
            return compare(sv) == 0;
        }

        [[nodiscard]] std::strong_ordering operator<=>(const string& str) const noexcept
        {
            return string_ <=> str.string_;
        }

        [[nodiscard]] std::strong_ordering operator<=>(const value_type* const ptr) const noexcept
        {
            return string_ <=> ptr;
        }

        template <detail::is_string_view StringView>
        [[nodiscard]] std::strong_ordering operator<=>(const StringView sv) const noexcept
        {
            const int32 comp = compare(sv);
            return ((comp == 0) ? std::strong_ordering::equal
                 : ((comp <  0) ? std::strong_ordering::less
                 : std::strong_ordering::greater));
        }

        [[nodiscard]] bool starts_with(const string& str) const noexcept
        {
            return string_.starts_with(str.string_);
        }

        [[nodiscard]] bool starts_with(const value_type* const ptr) const noexcept
        {
            return string_.starts_with(ptr);
        }

        [[nodiscard]] bool starts_with(const value_type c) const noexcept
        {
            return string_.starts_with(c);
        }

        [[nodiscard]] bool starts_with(const string_view sv) const noexcept
        {
            return string_.starts_with(sv);
        }

        [[nodiscard]] bool ends_with(const string& str) const noexcept
        {
            return string_.ends_with(str.string_);
        }

        [[nodiscard]] bool ends_with(const value_type* const ptr) const noexcept
        {
            return string_.ends_with(ptr);
        }

        [[nodiscard]] bool ends_with(const value_type c) const noexcept
        {
            return string_.ends_with(c);
        }

        [[nodiscard]] bool ends_with(const string_view sv) const noexcept
        {
            return string_.ends_with(sv);
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
            [[nodiscard]] inline string operator""_s(const char8* const ptr, const size_t n)
            {
                return string(ptr, n);
            }
        }
    }
} // namespace ld

template <>
inline void std::swap(ld::string& str1, ld::string& str2) noexcept
{
    str1.swap(str2);
}

template <>
struct std::hash<ld::string>
{
    [[nodiscard]] size_t operator()(const ld::string& str) const noexcept
    {
        return std::hash<std::u8string>{}(str);
    }
};

template <>
struct fmt::formatter<ld::string> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    constexpr auto parse(const ld::string& str, FormatContext& ctx)
    {
        return formatter<std::string_view>(reinterpret_cast<const char*>(str.c_str()), ctx);
    }
};

#endif // LABDOG_STRING_HPP