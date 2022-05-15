//=========================================================
//
//  string_view.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_STRING_VIEW_HPP
#define LABDOG_STRING_VIEW_HPP

#include <string_view>
#include <fmt/format.h>
#include "common.hpp"

namespace ld
{
    class string_view final
    {
    public:
        using string_view_type = std::basic_string_view<char8>;
        using traits_type = string_view_type::traits_type;
        using value_type = string_view_type::value_type;
        using pointer = string_view_type::pointer;
        using const_pointer = string_view_type::const_pointer;
        using reference = string_view_type::reference;
        using const_reference = string_view_type::const_reference;
        using iterator = string_view_type::iterator;
        using const_iterator = string_view_type::const_iterator;
        using reverse_iterator = string_view_type::reverse_iterator;
        using const_reverse_iterator = string_view_type::const_reverse_iterator;
        using size_type = string_view_type::size_type;
        using difference_type = string_view_type::difference_type;

        static constexpr auto npos{ string_view_type::npos };

        [[nodiscard]] constexpr string_view() noexcept
            : view_() {}

        [[nodiscard]] constexpr string_view(const string_view& sv) noexcept
            : view_(sv) {}

        [[nodiscard]] constexpr /* implicit */ string_view(const string_view_type& sv) noexcept
            : view_(sv) {}

        [[nodiscard]] constexpr /* implicit */ string_view(const value_type* const ptr) noexcept
            : view_(ptr) {}

        [[nodiscard]] constexpr string_view(const value_type* const ptr, const size_type n) noexcept
            : view_(ptr, n) {}

        template <std::contiguous_iterator Iterator, std::sized_sentinel_for<Iterator> Sentinel>
        requires std::is_same_v<std::iter_value_t<Iterator>, value_type>
              && std::negation_v<std::is_convertible<Sentinel, size_type>>
        [[nodiscard]] constexpr string_view(Iterator first, Sentinel last)
        noexcept(noexcept(string_view_type(first, last)))
            : view_(first, last) {}

        template <class Range>
        requires (!std::same_as<std::remove_cvref_t<Range>, string_view>
              && !std::same_as<std::remove_cvref_t<Range>, string_view_type>
              && std::ranges::contiguous_range<Range>
              && std::ranges::sized_range<Range>
              && std::same_as<std::ranges::range_value_t<Range>, value_type>
              && (!std::is_convertible_v<Range, const value_type*>)
              && (!requires(std::remove_cvref_t<Range>& range) {
                     range.operator std::basic_string_view<value_type, traits_type>(); })
              && (!requires { typename std::remove_reference_t<Range>::traits_type; }
                     || std::same_as<typename std::remove_reference_t<Range>::traits_type, traits_type>))
        [[nodiscard]] constexpr explicit string_view(Range&& range) noexcept(noexcept(string_view_type(range)))
            : view_(std::forward<Range>(range)) {}

        ~string_view() noexcept = default;

        [[nodiscard]] constexpr /* implicit */ operator string_view_type() const noexcept
        {
            return view_;
        }

        constexpr string_view& operator=(const string_view& sv) noexcept
        {
            view_ = sv.view_;
            return *this;
        }

        constexpr string_view& operator=(const value_type* const ptr) noexcept
        {
            view_ = ptr;
            return *this;
        }

        [[nodiscard]] constexpr const_iterator begin() const noexcept
        {
            return view_.begin();
        }

        [[nodiscard]] constexpr const_iterator end() const noexcept
        {
            return view_.end();
        }

        [[nodiscard]] constexpr const_iterator cbegin() const noexcept
        {
            return view_.cbegin();
        }

        [[nodiscard]] constexpr const_iterator cend() const noexcept
        {
            return view_.cend();
        }

        [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept
        {
            return view_.rbegin();
        }

        [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept
        {
            return view_.rend();
        }

        [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept
        {
            return view_.crbegin();
        }

        [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept
        {
            return view_.crend();
        }

        [[nodiscard]] constexpr size_type size() const noexcept
        {
            return view_.size();
        }

        [[nodiscard]] constexpr size_type length() const noexcept
        {
            return view_.length();
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return view_.empty();
        }

        [[nodiscard]] constexpr const value_type* data() const noexcept
        {
            return view_.data();
        }

        [[nodiscard]] constexpr size_type max_size() const noexcept
        {
            return view_.max_size();
        }

        [[nodiscard]] constexpr const value_type& operator[](const size_type pos) const noexcept
        {
            return view_[pos];
        }

        [[nodiscard]] constexpr const value_type& at(const size_type pos) const
        {
            return view_.at(pos);
        }

        [[nodiscard]] constexpr const value_type& front() const noexcept
        {
            return view_.front();
        }

        [[nodiscard]] constexpr const value_type& back() const noexcept
        {
            return view_.back();
        }

        constexpr void remove_prefix(const size_type n) noexcept
        {
            view_.remove_prefix(n);
        }

        constexpr void remove_suffix(const size_type n) noexcept
        {
            view_.remove_suffix(n);
        }

        constexpr void swap(string_view& str) noexcept
        {
            view_.swap(str.view_);
        }

        constexpr size_type copy(value_type* const ptr, const size_type n, const size_type pos = 0) noexcept
        {
            return view_.copy(ptr, n, pos);
        }

        [[nodiscard]] constexpr string_view substr(const size_type pos = 0, const size_type n = npos) const
        {
            return view_.substr(pos, n);
        }

        [[nodiscard]] constexpr int32 compare(const string_view sv) const
        {
            return view_.compare(sv.view_);
        }

        [[nodiscard]] constexpr int32 compare(
            const size_type pos,
            const size_type n,
            const string_view sv) const
        {
            return view_.compare(pos, n, sv.view_);
        }

        [[nodiscard]] constexpr int32 compare(
            const size_type pos1,
            const size_type n1,
            const string_view sv,
            const size_type pos2,
            const size_type n2) const
        {
            return view_.compare(pos1, n1, sv.view_, pos2, n2);
        }

        [[nodiscard]] constexpr int32 compare(const value_type* const ptr) const
        {
            return view_.compare(ptr);
        }

        [[nodiscard]] constexpr int32 compare(
            const size_type pos,
            const size_type n,
            const value_type* const ptr) const
        {
            return view_.compare(pos, n, ptr);
        }

        [[nodiscard]] constexpr int32 compare(
            const size_type pos,
            const size_type n,
            const value_type* const ptr,
            const size_type n2) const
        {
            return view_.compare(pos, n, ptr, n2);
        }

        [[nodiscard]] constexpr std::strong_ordering operator<=>(const string_view sv) const noexcept
        {
            return view_ <=> sv.view_;
        }

        [[nodiscard]] constexpr std::strong_ordering operator<=>(const value_type* const ptr) const noexcept
        {
            return view_ <=> ptr;
        }

        [[nodiscard]] constexpr bool starts_with(const string_view sv) const noexcept
        {
            return view_.starts_with(sv.view_);
        }

        [[nodiscard]] constexpr bool starts_with(const value_type c) const noexcept
        {
            return view_.starts_with(c);
        }

        [[nodiscard]] constexpr bool starts_with(const value_type* const ptr) const noexcept
        {
            return view_.starts_with(ptr);
        }

        [[nodiscard]] constexpr bool ends_with(const string_view sv) const noexcept
        {
            return view_.ends_with(sv.view_);
        }

        [[nodiscard]] constexpr bool ends_with(const value_type c) const noexcept
        {
            return view_.ends_with(c);
        }

        [[nodiscard]] constexpr bool ends_with(const value_type* const ptr) const noexcept
        {
            return view_.ends_with(ptr);
        }

        [[nodiscard]] constexpr bool contains(const string_view sv) const noexcept
        {
            return (find(sv) != npos);
        }

        [[nodiscard]] constexpr bool contains(const value_type c) const noexcept
        {
            return (find(c) != npos);
        }

        [[nodiscard]] constexpr bool contains(const value_type* const ptr) const noexcept {
            return (find(ptr) != npos);
        }

        [[nodiscard]] constexpr size_type find(const string_view sv, const size_type pos = 0) const noexcept
        {
            return view_.find(sv.view_, pos);
        }

        [[nodiscard]] constexpr size_type find(const value_type c, const size_type pos = 0) const noexcept
        {
            return view_.find(c, pos);
        }

        [[nodiscard]] constexpr size_type find(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return view_.find(ptr, pos);
        }

        [[nodiscard]] constexpr size_type find(
            const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return view_.find(ptr, pos, n);
        }

        [[nodiscard]] constexpr size_type rfind(const string_view sv, const size_type pos = 0) const noexcept
        {
            return view_.rfind(sv.view_, pos);
        }

        [[nodiscard]] constexpr size_type rfind(const value_type c, const size_type pos = 0) const noexcept
        {
            return view_.rfind(c, pos);
        }

        [[nodiscard]] constexpr size_type rfind(const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return view_.rfind(ptr, pos);
        }

        [[nodiscard]] constexpr size_type rfind(
            const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return view_.rfind(ptr, pos, n);
        }

        [[nodiscard]] constexpr size_type find_first_of(const string_view sv, const size_type pos = 0) const noexcept
        {
            return view_.find_first_of(sv.view_, pos);
        }

        [[nodiscard]] constexpr size_type find_first_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return view_.find_first_of(c, pos);
        }

        [[nodiscard]] constexpr size_type find_first_of(
            const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return view_.find_first_of(ptr, pos);
        }

        [[nodiscard]] constexpr size_type find_first_of(
            const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return view_.find_first_of(ptr, pos, n);
        }

        [[nodiscard]] constexpr size_type find_last_of(const string_view sv, const size_type pos = 0) const noexcept
        {
            return view_.find_last_of(sv.view_, pos);
        }

        [[nodiscard]] constexpr size_type find_last_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return view_.find_last_of(c, pos);
        }

        [[nodiscard]] constexpr size_type find_last_of(
            const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return view_.find_last_of(ptr, pos);
        }

        [[nodiscard]] constexpr size_type find_last_of(
                const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return view_.find_last_of(ptr, pos, n);
        }

        [[nodiscard]] constexpr size_type find_first_not_of(
            const string_view sv, const size_type pos = 0) const noexcept
        {
            return view_.find_first_not_of(sv.view_, pos);
        }

        [[nodiscard]] constexpr size_type find_first_not_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return view_.find_first_not_of(c, pos);
        }

        [[nodiscard]] constexpr size_type find_first_not_of(
            const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return view_.find_first_not_of(ptr, pos);
        }

        [[nodiscard]] constexpr size_type find_first_not_of(
            const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return view_.find_first_not_of(ptr, pos, n);
        }

        [[nodiscard]] constexpr size_type find_last_not_of(const string_view sv, const size_type pos = 0) const noexcept
        {
            return view_.find_last_not_of(sv.view_, pos);
        }

        [[nodiscard]] constexpr size_type find_last_not_of(const value_type c, const size_type pos = 0) const noexcept
        {
            return view_.find_last_not_of(c, pos);
        }

        [[nodiscard]] constexpr size_type find_last_not_of(
            const value_type* const ptr, const size_type pos = 0) const noexcept
        {
            return view_.find_last_not_of(ptr, pos);
        }

        [[nodiscard]] constexpr size_type find_last_not_of(
            const value_type* const ptr, const size_type pos, const size_type n) const noexcept
        {
            return view_.find_last_not_of(ptr, pos, n);
        }
    private:
        string_view_type view_;
    };

    inline namespace literals
    {
        inline namespace string_view_literals
        {
            [[nodiscard]] inline constexpr string_view operator""_sv(const char8* const ptr, const size_t length)
            {
                return { ptr, length };
            }
        }
    }
} // namespace ld

template <>
inline void std::swap(ld::string_view& sv1, ld::string_view& sv2) noexcept
{
    sv1.swap(sv2);
}

template <>
struct std::hash<ld::string_view>
{
    [[nodiscard]] size_t operator()(const ld::string_view& sv) const noexcept
    {
        return std::hash<std::u8string_view>{}({ sv.begin(), sv.end() });
    }
};

template <>
struct fmt::formatter<ld::string_view> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    constexpr auto parse(const ld::string_view& sv, FormatContext& ctx)
    {
        return formatter<std::string_view>(reinterpret_cast<const char*>(sv.data()), ctx);
    }
};

#endif // LABDOG_STRING_VIEW_HPP