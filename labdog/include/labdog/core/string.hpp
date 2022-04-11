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

	/// @brief UTF-32文字列クラス
	class LABDOG_API string
	{
	public:
		//=========================================================
		//	エイリアス
		//=========================================================
		/// @brief 文字列型
		using string_type = std::u32string;

		/// @brief 文字列の特性型
		using traits_type = string_type::traits_type;

		/// @brief アロケータ型
		using allocator_type = string_type::allocator_type;

		/// @brief 要素型
		using value_type = string_type::value_type;

		/// @brief 要素のポインタ型
		using pointer = string_type::pointer;

		/// @brief 要素のconstポインタ型
		using const_pointer = string_type::const_pointer;

		/// @brief 要素の参照型
		using reference = string_type::reference;

		/// @brief 要素のconst参照型
		using const_reference = string_type::const_reference;

		/// @brief イテレータ型
		using iterator = string_type::iterator;

		/// @brief constイテレータ型
		using const_iterator = string_type::const_iterator;

		/// @brief リバースイテレータ型
		using reverse_iterator = string_type::reverse_iterator;

		/// @brief constリバースイテレータ型
		using const_reverse_iterator = string_type::const_reverse_iterator;

		/// @brief 要素の個数を表現する型
		using size_type = string_type::size_type;

		/// @brief 要素間の距離を表現する型
		using difference_type = string_type::difference_type;

        //=========================================================
        //	定数
        //=========================================================
        /// @brief 無効な要素のインデックス値
        static constexpr size_type npos{ string_type::npos };

		//=========================================================
		//	コンストラクタ
		//=========================================================
		/// @brief デフォルトコンストラクタ
        LABDOG_NODISCARD_CXX20
        string() noexcept;

		/// @brief コピーコンストラクタ
        LABDOG_NODISCARD_CXX20
        string(const string& other) noexcept;

		/// @brief ムーブコンストラクタ
        LABDOG_NODISCARD_CXX20
        string(string&& other) noexcept;

		/// @brief 文字列の指定範囲をコピーして構築する
		/// @param str コピーする文字列
		///	@param pos 範囲の先頭位置
		///	@param length 範囲の長さ
        LABDOG_NODISCARD_CXX20
        string(const string& str, size_type pos, size_type length = npos);

		/// @brief 文字列からコピーして構築する
		///	@param str コピーする文字列
        LABDOG_NODISCARD_CXX20
        explicit string(const string_type& str);

		/// @brief 文字列の指定範囲をコピーして構築する
		/// @param str コピーする文字列
		///	@param pos 範囲の先頭位置
		///	@param length 範囲の長さ
        LABDOG_NODISCARD_CXX20
        string(const string_type& str, size_type pos, size_type length = npos);

		/// @brief 文字配列をコピーして構築する
		/// @param str コピーする文字配列
        LABDOG_NODISCARD_CXX20
        explicit string(const value_type* str);

		/// @brief 文字配列の指定範囲をコピーして構築する
		/// @param str コピーする文字配列
		///	@param pos 範囲の先頭位置
		///	@param length 範囲の長さ
        LABDOG_NODISCARD_CXX20
        string(const value_type* str, size_type pos, size_type length = npos);

		/// @brief 文字を指定個数並べた文字列を構築する
		///	@param c 繰り返す文字
		///	@param count 個数
        LABDOG_NODISCARD_CXX20
        string(value_type c, size_type count);

		/// @brief 文字列の範囲から構築する
		/// @tparam Iterator イテレータ型
		/// @param first 範囲の先頭要素へのイテレータ
		/// @param last 範囲の末尾要素へのイテレータ
		template <class Iterator>
        LABDOG_NODISCARD_CXX20
        string(Iterator first, Iterator last);

		/// @brief 文字の初期化子リストから構築する
		///	@param list 文字の初期化子リスト
        LABDOG_NODISCARD_CXX20
        string(std::initializer_list<value_type> list);

		//=========================================================
		//	デストラクタ
		//=========================================================
		/// @brief デフォルトデストラクタ
		virtual ~string() noexcept = default;

		//=========================================================
		//	演算子
		//=========================================================
		/// @brief コピー代入演算子
		[[nodiscard]] string& operator=(const string& rhs) = default;

		/// @brief ムーブ代入演算子
		[[nodiscard]] string& operator=(string&& rhs) noexcept;

		/// @brief 文字配列をコピー代入する
		[[nodiscard]] string& operator=(const value_type* rhs);

		/// @brief 文字をコピー代入する
		[[nodiscard]] string& operator=(value_type rhs);

		/// @brief 文字の初期化子リストをコピー代入する
		[[nodiscard]] string& operator=(std::initializer_list<value_type> rhs);

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
		[[nodiscard]] bool operator!=(const string & rhs) const;

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
		//	イテレータ
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
		//friend string_view;

		//=========================================================
		//	変数
		//=========================================================
		/// @brief 文字列コンテナ
		string_type string_;
	};
}

#include "detail/string.ipp"

#endif // LABDOG_STRING_HPP