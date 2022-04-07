#pragma once
#include "../string.hpp" // •s—v
#include "string_view.hpp"

namespace labdog
{
	constexpr string_view::string_view(string_view&& other) noexcept
		: view_(std::move(other.view_))
	{}

	inline constexpr string_view::string_view(const string& str) noexcept
		: view_(str.data())
	{}

	constexpr string_view::string_view(const string& str, const size_t count) noexcept
		: view_(str.data(), count)
	{}

	inline constexpr string_view::string_view(const value_type* str) noexcept
		: view_(str)
	{}

	inline constexpr string_view::string_view(const value_type* str, const size_t count) noexcept
		: view_(str, count)
	{}

	constexpr string_view& string_view::operator=(const string& rhs) noexcept
	{
		view_ = string_view_type(rhs.string_);
		return *this;
	}

	constexpr string_view& string_view::operator=(const value_type* rhs)
	{
		view_ = rhs;
		return *this;
	}

	constexpr bool string_view::operator==(const string_view& rhs) const
	{
		return (view_ == rhs.view_);
	}

	constexpr bool string_view::operator==(const string& rhs) const
	{
		return (view_ == string_view_type(rhs.string_));
	}

	constexpr bool string_view::operator==(const value_type* rhs) const
	{
		return (view_ == rhs);
	}

	constexpr std::strong_ordering string_view::operator<=>(const string_view& rhs) const noexcept
	{
		return (view_ <=> rhs.view_);
	}

	constexpr std::strong_ordering string_view::operator<=>(const string& rhs) const noexcept
	{
		return (view_ <=> string_view_type(rhs.string_));
	}

	constexpr std::strong_ordering string_view::operator<=>(const value_type* rhs) const noexcept
	{
		return (view_ <=> rhs);
	}

	constexpr const string_view::value_type* string_view::data() const noexcept
	{
		return view_.data();
	}

	constexpr const string_view::value_type& string_view::front() const noexcept
	{
		return view_.front();
	}

	constexpr const string_view::value_type& string_view::back() const noexcept
	{
		return view_.back();
	}

	constexpr size_t string_view::size() const noexcept
	{
		return view_.size();
	}

	constexpr size_t string_view::max_size() const noexcept
	{
		return view_.max_size();
	}

	constexpr bool string_view::empty() const noexcept
	{
		return view_.empty();
	}

	template <class Iterator>
	constexpr labdog::string_view::string_view(Iterator first, Iterator last)
		: view_(first, last)
	{}

	constexpr string_view::const_iterator string_view::begin() const noexcept
	{
		return view_.begin();
	}

	constexpr string_view::const_iterator string_view::end() const noexcept
	{
		return view_.end();
	}

	constexpr string_view::const_iterator string_view::cbegin() const noexcept
	{
		return view_.cbegin();
	}

	constexpr string_view::const_iterator string_view::cend() const noexcept
	{
		return view_.cend();
	}

	constexpr string_view::const_reverse_iterator string_view::rbegin() const noexcept
	{
		return view_.rbegin();
	}

	constexpr string_view::const_reverse_iterator string_view::rend() const noexcept
	{
		return view_.rend();
	}

	constexpr string_view::const_reverse_iterator string_view::crbegin() const noexcept
	{
		return view_.crbegin();
	}

	constexpr string_view::const_reverse_iterator string_view::crend() const noexcept
	{
		return view_.crend();
	}
}
