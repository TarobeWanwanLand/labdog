//=========================================================
//
//	string.ipp
//	Copyright(c) 2022 Tomomi murakami.
//
//	Released under the MIT license.
//	see http://opensource.org/licenses/MIT
//
//=========================================================

#pragma once
#include "../string.hpp" // •s—v

namespace labdog
{
	inline constexpr string::string(string&& other) noexcept
		: string_(std::move(other.string_))
	{}

	inline constexpr inline string::string(const string& str, const size_type pos, const size_type length)
		: string_(str.string_, pos, length)
	{}

	inline constexpr string::string(const string_type& str)
		: string_(str)
	{}

	inline constexpr string::string(const string_type& str, const size_type pos, const size_type length)
		: string_(str, pos, length)
	{}

	inline constexpr string::string(const value_type* str)
		: string_(str)
	{}

	inline constexpr string::string(const value_type* str, const size_type pos, const size_type length)
		: string_(str, pos, length)
	{}

	inline constexpr string::string(const value_type c, const size_type count)
		: string_(count, c)
	{}

	template <class Iterator>
	inline constexpr string::string(Iterator first, Iterator last)
		: string_(first, last)
	{}

	inline constexpr string::string(const std::initializer_list<value_type> list)
		: string_(list)
	{}

	inline constexpr string& string::operator=(string&& rhs) noexcept
	{
		string_ = std::move(rhs);
		return *this;
	}

	inline constexpr string& string::operator=(const value_type* const rhs)
	{
		string_ = rhs;
		return *this;
	}

	inline constexpr string& string::operator=(const value_type rhs)
	{
		string_ = rhs;
		return *this;
	}

	inline constexpr string& string::operator=(const std::initializer_list<value_type> rhs)
	{
		string_ = rhs;
		return *this;
	}

	inline constexpr string string::operator+(const string& rhs) const
	{
		return string(string_ + rhs.string_);
	}

	inline constexpr string string::operator+(const value_type* rhs) const
	{
		return string(string_ + rhs);
	}

	inline constexpr string string::operator+(const value_type rhs) const
	{
		return string(string_ + rhs);
	}

	inline constexpr string& string::operator+=(const string& rhs)
	{
		string_ += rhs;
		return *this;
	}

	inline constexpr string& string::operator+=(const value_type* rhs)
	{
		string_ += rhs;
		return *this;
	}

	inline constexpr string& string::operator+=(const value_type rhs)
	{
		string_ += rhs;
		return *this;
	}

	inline constexpr bool string::operator==(const string& rhs) const
	{
		return (string_ == rhs.string_);
	}

	inline constexpr bool string::operator==(const value_type* rhs) const
	{
		return (string_ == rhs);
	}

	inline constexpr bool string::operator!=(const string& rhs) const
	{
		return (string_ != rhs.string_);
	}

	inline constexpr bool string::operator!=(const value_type* rhs) const
	{
		return (string_ != rhs);
	}

	inline constexpr std::strong_ordering string::operator<=>(const string& rhs) const
	{
		return (string_ <=> rhs.string_);
	}

	inline constexpr std::strong_ordering string::operator<=>(const value_type* rhs) const
	{
		return (string_ <=> rhs);
	}

	inline constexpr const string::value_type* string::data() const noexcept
	{
		return string_.data();
	}

	inline constexpr string::value_type& string::front() noexcept
	{
		return string_.front();
	}

	inline constexpr const string::value_type& string::front() const noexcept
	{
		return string_.front();
	}

	inline constexpr string::value_type& string::back() noexcept
	{
		return string_.back();
	}

	inline constexpr const string::value_type& string::back() const noexcept
	{
		return string_.back();
	}

	inline constexpr size_t string::size() const noexcept
	{
		return string_.size();
	}

	inline constexpr size_t string::max_size() const noexcept
	{
		return string_.max_size();
	}

	inline constexpr bool string::empty() const noexcept
	{
		return string_.empty();
	}

	inline constexpr string::iterator string::begin() noexcept
	{
		return string_.begin();
	}

	inline constexpr string::const_iterator string::begin() const noexcept
	{
		return string_.begin();
	}

	inline constexpr string::iterator string::end() noexcept
	{
		return string_.end();
	}

	inline constexpr string::const_iterator string::end() const noexcept
	{
		return string_.end();
	}

	inline constexpr string::const_iterator string::cbegin() const noexcept
	{
		return string_.cbegin();
	}

	inline constexpr string::const_iterator string::cend() const noexcept
	{
		return string_.cend();
	}

	inline constexpr string::reverse_iterator string::rbegin() noexcept
	{
		return string_.rbegin();
	}

	inline constexpr string::const_reverse_iterator string::rbegin() const noexcept
	{
		return string_.rbegin();
	}

	inline constexpr string::reverse_iterator string::rend() noexcept
	{
		return string_.rend();
	}

	inline constexpr string::const_reverse_iterator string::rend() const noexcept
	{
		return string_.rend();
	}

	inline constexpr string::const_reverse_iterator string::crbegin() const noexcept
	{
		return string_.crbegin();
	}

	inline constexpr string::const_reverse_iterator string::crend() const noexcept
	{
		return string_.crend();
	}
}
