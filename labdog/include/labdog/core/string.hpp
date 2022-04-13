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

#include "common.hpp"
#include <string>

namespace ld
{
    /// @brief UTF-32文字列クラス
    class LD_API string
    {
    public:
        using string_type = std::u32string;
        using traits_type = string_type::traits_type;
        using allocator_type = string_type::allocator_type;
        using value_type = string_type::value_type;
        using pointer = string_type::pointer;
        using const_pointer = string_type::const_pointer;
        using reference = string_type::reference;
        using const_reference = string_type::const_reference;
        using iterator = string_type::iterator;
        using const_iterator = string_type::const_iterator;
        using reverse_iterator = string_type::reverse_iterator;
        using const_reverse_iterator = string_type::const_reverse_iterator;
        using size_type = string_type::size_type;
        using difference_type = string_type::difference_type;

        static constexpr size_type npos{string_type::npos};

        LD_NODISCARD_CTOR string() noexcept;

        LD_NODISCARD_CTOR string(const string& other) noexcept;

        LD_NODISCARD_CTOR string(string&& other) noexcept;

        LD_NODISCARD_CTOR string(const string& str, size_type pos, size_type length = npos);

        LD_NODISCARD_CTOR explicit string(const string_type& str);

        LD_NODISCARD_CTOR string(const string_type& str, size_type pos, size_type length = npos);

        LD_NODISCARD_CTOR explicit string(const value_type* str);

        LD_NODISCARD_CTOR string(const value_type* str, size_type pos, size_type length = npos);

        LD_NODISCARD_CTOR string(value_type c, size_type count);

        LD_NODISCARD string& operator=(const string& rhs) noexcept;

        LD_NODISCARD string& operator=(string&& rhs) noexcept;

        LD_NODISCARD string& operator=(value_type rhs);

        LD_NODISCARD string& operator=(const value_type* rhs);

        /// @brief 文字列の範囲から構築する
        /// @tparam Iterator イテレータ型
        /// @param first 範囲の先頭要素へのイテレータ
        /// @param last 範囲の末尾要素へのイテレータ
        template <class Iterator>
        string(Iterator first, Iterator last)
                : string_(first, last) {}

        /// @brief 文字の初期化子リストから構築する
        ///	@param list 文字の初期化子リスト
        LD_NODISCARD_CTOR
        string(std::initializer_list<value_type> list);

        /// @brief 文字の初期化子リストをコピー代入する
        LD_NODISCARD
        string& operator=(std::initializer_list<value_type> rhs);

        //=========================================================
        //  デストラクタ
        //=========================================================
        /// @brief デフォルトデストラクタ
        virtual ~string() noexcept = default;

        //=========================================================
        //	演算子
        //=========================================================
        /// @brief 文字列を末尾に結合する
        [[nodiscard]] string operator+(const string& rhs) const;

        /// @brief 文字列を末尾に結合する
        [[nodiscard]] string operator+(const value_type* rhs) const;

        /// @brief 文字を末尾に結合する
        [[nodiscard]] string operator+(value_type rhs) const;

        /// @brief 文字列を末尾に結合して代入する
        [[nodiscard]] string& operator+=(const string& rhs);

        /// @brief 文字配列を末尾に結合して代入する
        [[nodiscard]] string& operator+=(const value_type* rhs);

        /// @brief 文字を末尾に結合して代入する
        [[nodiscard]] string& operator+=(value_type rhs);

        /// @brief 文字列を等値比較する
        [[nodiscard]] bool operator==(const string& rhs) const;

        /// @brief 文字列を等値比較する
        [[nodiscard]] bool operator==(const value_type* rhs) const;

        /// @brief 文字列を非等値比較する
        [[nodiscard]] bool operator!=(const string& rhs) const;

        /// @brief 文字列を非等値比較する
        [[nodiscard]] bool operator!=(const value_type* rhs) const;

        /// @brief 文字列を比較する
        [[nodiscard]] std::strong_ordering operator<=>(const string& rhs) const;

        /// @brief 文字列を比較する
        [[nodiscard]] std::strong_ordering operator<=>(const value_type* rhs) const;

        //=========================================================
        //	要素アクセス
        //=========================================================
        /// @brief 先頭要素へのポインタを返す
        ///	@return 先頭要素へのポインタ
        [[nodiscard]] const value_type* data() const noexcept;

        /// @brief 先頭要素への参照を返す
        ///	@return 先頭要素への参照
        [[nodiscard]] value_type& front() noexcept;

        /// @brief 先頭要素へのconst参照を返す
        ///	@return 先頭要素へのconst参照
        [[nodiscard]] const value_type& front() const noexcept;

        /// @brief 末尾要素への参照を返す
        ///	@return 末尾要素への参照
        [[nodiscard]] value_type& back() noexcept;

        /// @brief 末尾要素へのconst参照を返す
        ///	@return 末尾要素へのconst参照
        [[nodiscard]] const value_type& back() const noexcept;

        //=========================================================
        //	情報
        //=========================================================
        /// @brief 文字列の長さを返す
        ///	@return 文字列の長さ
        [[nodiscard]] size_t size() const noexcept;

        /// @brief 格納可能な最大文字数を返す
        ///	@return 格納可能な最大文字数
        [[nodiscard]] size_t max_size() const noexcept;

        /// @brief コンテナが空かどうかを返す
        ///	@return コンテナが空か
        [[nodiscard]] bool empty() const noexcept;

        //=========================================================
        //  イテレータ
        //=========================================================
        /// @brief 先頭要素を指すイテレータを返す
        [[nodiscard]] iterator begin() noexcept;

        /// @brief 先頭要素を指すconstイテレータを返す
        [[nodiscard]] const_iterator begin() const noexcept;

        /// @brief 末尾要素を指すイテレータを返す
        [[nodiscard]] iterator end() noexcept;

        /// @brief 末尾要素を指すconstイテレータを返す
        [[nodiscard]] const_iterator end() const noexcept;

        /// @brief 先頭要素を指すconstイテレータを返す
        [[nodiscard]] const_iterator cbegin() const noexcept;

        /// @brief 末尾要素を指すconstイテレータを返す
        [[nodiscard]] const_iterator cend() const noexcept;

        /// @brief 先頭要素を指すリバースイテレータを返す
        [[nodiscard]] reverse_iterator rbegin() noexcept;

        /// @brief 先頭要素を指すconstリバースイテレータを返す
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept;

        /// @brief 末尾要素を指すリバースイテレータを返す
        [[nodiscard]] reverse_iterator rend() noexcept;

        /// @brief 先頭要素を指すconstリバースイテレータを返す
        [[nodiscard]] const_reverse_iterator rend() const noexcept;

        /// @brief 先頭要素を指すconstリバースイテレータを返す
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept;

        /// @brief 末尾要素を指すconstリバースイテレータを返す
        [[nodiscard]] const_reverse_iterator crend() const noexcept;

    private:
        //=========================================================
        //	変数
        //=========================================================
        /// @brief 文字列
        string_type string_;
    };
}

#endif // LD_STRING_HPP