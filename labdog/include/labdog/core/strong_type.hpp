//=========================================================
//
//  strong_type.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_STRONG_TYPE_HPP
#define LABDOG_STRONG_TYPE_HPP

#include <type_traits>
#include <concepts>

namespace ld
{
    template<class Type, class Tag>
    struct strong_type final
    {
        static_assert(
            std::is_same_v<Type, std::remove_cvref_t<Type>>,
            "It must be a non-const, non-volatile type.");

    public:
        using value_type = Type;

        [[nodiscard]] constexpr strong_type() = default;

        template <class... Args>
        requires std::is_constructible_v<value_type, Args...>
        [[nodiscard]] constexpr explicit strong_type(Args&&... args)
        noexcept(std::is_nothrow_constructible_v<value_type, Args...>)
            : value_{ std::forward<Args>(args)... }
        { }

        [[nodiscard]] constexpr strong_type(const strong_type& other)
        noexcept(std::is_nothrow_copy_constructible_v<value_type>)
        requires std::is_copy_constructible_v<value_type>
            : value_{ other.value_ }
        { }

        [[nodiscard]] constexpr strong_type(strong_type&& other)
        noexcept(std::is_nothrow_move_constructible_v<value_type>)
        requires std::is_move_constructible_v<value_type>
                 && std::negation_v<std::is_reference<value_type>>
            : value_{ std::move(other.value_) }
        { }

        ~strong_type() = default;

        [[nodiscard]] constexpr value_type& value() noexcept
        {
            return value_;
        }

        constexpr strong_type& operator=(const strong_type& rhs)
        noexcept(std::is_nothrow_copy_assignable_v<value_type>)
        requires std::is_copy_assignable_v<value_type>
        {
            value_ = rhs.value_;
            return *this;
        }

        constexpr strong_type& operator=(strong_type&& rhs)
        noexcept(std::is_nothrow_move_assignable_v<value_type>)
        requires std::is_move_assignable_v<value_type>
                 && std::negation_v<std::is_reference<value_type>>
        {
            value_ = std::move(rhs.value_);
            return *this;
        }

        constexpr strong_type& operator=(const value_type& rhs)
        noexcept(std::is_nothrow_copy_assignable_v<value_type>)
        requires std::is_copy_assignable_v<value_type>
        {
            value_ = rhs;
            return *this;
        }

        constexpr strong_type& operator=(value_type&& rhs)
        noexcept(std::is_nothrow_move_assignable_v<value_type>)
        requires std::is_move_assignable_v<value_type>
                 && std::negation_v<std::is_reference<value_type>>
        {
            value_ = rhs;
            return *this;
        }

        [[nodiscard]] constexpr const value_type& operator*() const noexcept
        {
            return value_;
        }

        [[nodiscard]] constexpr const value_type* operator->() const noexcept
        {
            return std::addressof(value_);
        }

        [[nodiscard]] constexpr const value_type& value() const noexcept
        {
            return value_;
        }

    private:
        value_type value_;
    };
}

#endif // LABDOG_STRONG_TYPE_HPP
