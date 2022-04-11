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

	/// @brief UTF-32文字列ビュークラス
	class LABDOG_EXPORT string_view
	{
	public:
		//=========================================================
		//	エイリアス
		//=========================================================
		/// @brief 文字列型
		using string_view_type = std::u32string_view;

		/// @brief 文字列の特性型
		using traits_type = string_view_type::traits_type;

		/// @brief 要素型
		using value_type = string_view_type::value_type;

		/// @brief 要素のポインタ型
		using pointer = string_view_type::pointer;

		/// @brief 要素のconstポインタ型
		using const_pointer = string_view_type::const_pointer;

		/// @brief 要素の参照型
		using reference = string_view_type::reference;

		/// @brief 要素のconst参照型
		using const_reference = string_view_type::const_reference;

		/// @brief イテレータ型
		using iterator = string_view_type::iterator;

		/// @brief constイテレータ型
		using const_iterator = string_view_type::const_iterator;

		/// @brief リバースイテレータ型
		using reverse_iterator = string_view_type::reverse_iterator;

		/// @brief constリバースイテレータ型
		using const_reverse_iterator = string_view_type::const_reverse_iterator;

		/// @brief 要素の個数を表現する型
		using size_type = string_view_type::size_type;

		/// @brief 要素間の距離を表現する型
		using difference_type = string_view_type::difference_type;

		//=========================================================
		//	定数
		//=========================================================
		/// @brief 無効な位置
		static constexpr size_t npos = string_view_type::npos;

		//=========================================================
		//	コンストラクタ
		//=========================================================
		/// @brief デフォルトコンストラクタ
		constexpr string_view() noexcept = default;

		/// @brief コピーコンストラクタ
		constexpr string_view(const string_view&) noexcept = default;

		/// @brief ムーブコンストラクタ
		constexpr string_view(string_view&& other) noexcept;

		/// @brief 文字列を参照する
		///	@param str 参照する文字列
		explicit constexpr string_view(const string& str) noexcept;

		/// @brief 文字配列の先頭から指定文字数の範囲を参照する
		///	@param str 参照する文字配列
		///	@param count 参照する文字数
		explicit constexpr string_view(const string& str, size_t count) noexcept;

		/// @brief 文字配列を参照する
		///	@param str 参照する文字配列
		explicit constexpr string_view(const value_type* str) noexcept;

		/// @brief 文字配列の先頭から指定文字数の範囲を参照する
		///	@param str 参照する文字配列
		///	@param count 参照する文字数
		constexpr string_view(const value_type* str, size_t count) noexcept;

		/// @brief 文字列の範囲を参照する
		/// @tparam Iterator イテレータ型
		/// @param first 範囲の先頭要素へのイテレータ
		/// @param last 範囲の末尾要素へのイテレータ
		template <class Iterator>
		constexpr string_view(Iterator first, Iterator last);

		//=========================================================
		//	デストラクタ
		//=========================================================
		/// @brief デフォルトデストラクタ
		virtual ~string_view() noexcept = default;

		//=========================================================
		//	演算子
		//=========================================================
		/// @brief コピー代入演算子
		[[nodiscard]] constexpr string_view& operator=(const string_view& rhs) = default;

		/// @brief 文字列を参照する
		[[nodiscard]] constexpr string_view& operator=(const string& rhs) noexcept;

		/// @brief 文字配列を参照する
		[[nodiscard]] constexpr string_view& operator=(const value_type* rhs);

		/// @brief 文字列を等値比較する
		[[nodiscard]] constexpr bool operator==(const string_view& rhs) const;

		/// @brief 文字列を等値比較する
		[[nodiscard]] constexpr bool operator==(const string& rhs) const;

		/// @brief 文字列を等値比較する
		[[nodiscard]] constexpr bool operator==(const value_type* rhs) const;

		/// @brief 文字列を比較する
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const string_view& rhs) const noexcept;

		/// @brief 文字列を比較する
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const string& rhs) const noexcept;

		/// @brief 文字列を比較する
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const value_type* rhs) const noexcept;

		//=========================================================
		//	要素アクセス
		//=========================================================
		/// @brief 先頭要素へのポインタを返す
		///	@return 先頭要素へのポインタ
		[[nodiscard]] constexpr const value_type* data() const noexcept;

		/// @brief 先頭要素へのconst参照を返す
		///	@return 先頭要素へのconst参照
		[[nodiscard]] constexpr const value_type& front() const noexcept;

		/// @brief 末尾要素へのconst参照を返す
		///	@return 末尾要素へのconst参照
		[[nodiscard]] constexpr const value_type& back() const noexcept;

		//=========================================================
		//	情報
		//=========================================================
		/// @brief 文字列の長さを返す
		///	@return 文字列の長さ
		[[nodiscard]] constexpr size_t size() const noexcept;

		/// @brief 参照可能な最大文字数を返す
		///	@return 参照可能な最大文字数
		[[nodiscard]] constexpr size_t max_size() const noexcept;

		/// @brief 文字列が空かどうかを返す
		///	@return 文字列が空か
		[[nodiscard]] constexpr bool empty() const noexcept;

		//=========================================================
		//	イテレータ
		//=========================================================
		/// @brief 先頭要素を指すconstイテレータを返す
		[[nodiscard]] constexpr const_iterator begin() const noexcept;

		/// @brief 末尾要素を指すconstイテレータを返す
		[[nodiscard]] constexpr const_iterator end() const noexcept;

		/// @brief 先頭要素を指すconstイテレータを返す
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept;

		/// @brief 末尾要素を指すconstイテレータを返す
		[[nodiscard]] constexpr const_iterator cend() const noexcept;

		/// @brief 先頭要素を指すconstリバースイテレータを返す
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept;

		/// @brief 先頭要素を指すconstリバースイテレータを返す
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept;

		/// @brief 先頭要素を指すconstリバースイテレータを返す
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept;

		/// @brief 末尾要素を指すconstリバースイテレータを返す
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept;

	private:
		//=========================================================
		//	変数
		//=========================================================
		string_view_type view_;
	};
}

#include "detail/string_view.ipp"