//=========================================================
//
//  string.cpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/string.hpp"

namespace ld
{
    string::string() noexcept
            : string_() {}

    string::string(const string& other) noexcept
            : string_(other.string_) {}

    string& string::operator=(const string& rhs) noexcept
    {
        string_ = rhs.string_;
        return *this;
    }

    string::string(string&& other) noexcept
            : string_(std::move(other.string_)) {}

    string& string::operator=(string&& rhs) noexcept
    {
        string_ = std::move(rhs.string_);
        return *this;
    }

    string::string(const string& str, const size_type pos, const size_type length)
            : string_(str.string_, pos, length) {}

    string::string(const string_type& str)
            : string_(str) {}

    string& string::operator=(const value_type rhs)
    {
        string_ = rhs;
        return *this;
    }

    string::string(const string_type& str, const size_type pos, const size_type length)
            : string_(str, pos, length) {}

    string::string(const value_type* str)
            : string_(str) {}

    string& string::operator=(const value_type* const rhs)
    {
        string_ = rhs;
        return *this;
    }

    string::string(const value_type* str, const size_type pos, const size_type length)
            : string_(str, pos, length) {}

    string::string(const value_type c, const size_type count)
            : string_(count, c) {}

    string::string(const std::initializer_list<value_type> list)
            : string_(list) {}

    string& string::operator=(const std::initializer_list<value_type> rhs)
    {
        string_ = rhs;
        return *this;
    }

    string string::operator+(const string& rhs) const
    {
        return string(string_ + rhs.string_);
    }

    string string::operator+(const value_type* rhs) const
    {
        return string(string_ + rhs);
    }

    string string::operator+(const value_type rhs) const
    {
        return string(string_ + rhs);
    }

    string& string::operator+=(const string& rhs)
    {
        string_ += rhs.string_;
        return *this;
    }

    string& string::operator+=(const value_type* rhs)
    {
        string_ += rhs;
        return *this;
    }

    string& string::operator+=(const value_type rhs)
    {
        string_ += rhs;
        return *this;
    }

    bool string::operator==(const string& rhs) const
    {
        return (string_ == rhs.string_);
    }

    bool string::operator==(const value_type* rhs) const
    {
        return (string_ == rhs);
    }

    bool string::operator!=(const string& rhs) const
    {
        return (string_ != rhs.string_);
    }

    bool string::operator!=(const value_type* rhs) const
    {
        return (string_ != rhs);
    }

    std::strong_ordering string::operator<=>(const string& rhs) const
    {
        return (string_ <=> rhs.string_);
    }

    std::strong_ordering string::operator<=>(const value_type* rhs) const
    {
        return (string_ <=> rhs);
    }

    const string::value_type* string::data() const noexcept
    {
        return string_.data();
    }

    string::value_type& string::front() noexcept
    {
        return string_.front();
    }

    const string::value_type& string::front() const noexcept
    {
        return string_.front();
    }

    string::value_type& string::back() noexcept
    {
        return string_.back();
    }

    const string::value_type& string::back() const noexcept
    {
        return string_.back();
    }

    size_t string::size() const noexcept
    {
        return string_.size();
    }

    size_t string::max_size() const noexcept
    {
        return string_.max_size();
    }

    bool string::empty() const noexcept
    {
        return string_.empty();
    }

    string::iterator string::begin() noexcept
    {
        return string_.begin();
    }

    string::const_iterator string::begin() const noexcept
    {
        return string_.begin();
    }

    string::iterator string::end() noexcept
    {
        return string_.end();
    }

    string::const_iterator string::end() const noexcept
    {
        return string_.end();
    }

    string::const_iterator string::cbegin() const noexcept
    {
        return string_.cbegin();
    }

    string::const_iterator string::cend() const noexcept
    {
        return string_.cend();
    }

    string::reverse_iterator string::rbegin() noexcept
    {
        return string_.rbegin();
    }

    string::const_reverse_iterator string::rbegin() const noexcept
    {
        return string_.rbegin();
    }

    string::reverse_iterator string::rend() noexcept
    {
        return string_.rend();
    }

    string::const_reverse_iterator string::rend() const noexcept
    {
        return string_.rend();
    }

    string::const_reverse_iterator string::crbegin() const noexcept
    {
        return string_.crbegin();
    }

    string::const_reverse_iterator string::crend() const noexcept
    {
        return string_.crend();
    }
}
