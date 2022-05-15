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
    struct strong_type
    {
    public:
        using value_type = Type;

        [[nodiscard]] constexpr strong_type()
        noexcept(noexcept(std::is_nothrow_default_constructible_v<value_type>))
        requires std::is_default_constructible_v<value_type>
        {
        }

        template <class... Args>
        requires std::is_constructible_v<value_type, Args...>
              && std::negation_v<std::disjunction<std::is_same<Args, const value_type&>...>>
              && std::negation_v<std::disjunction<std::is_same<Args, value_type&&>...>>
        [[nodiscard]] constexpr explicit strong_type(Args&&... args)
        noexcept(noexcept(std::is_nothrow_constructible_v<value_type, Args...>))
            : value_{ std::forward<Args>(args)... }
        {
        }

        [[nodiscard]] constexpr explicit strong_type(const value_type& v)
        noexcept(noexcept(std::is_nothrow_copy_constructible_v<value_type>))
        requires std::is_copy_constructible_v<value_type>
            : value_{ v }
        {
        }

        [[nodiscard]] constexpr explicit strong_type(value_type&& v)
        noexcept(noexcept(std::is_nothrow_move_constructible_v<value_type>))
        requires std::is_move_constructible_v<value_type> && std::negation_v<std::is_reference<value_type>>
            : value_{ std::move(v) }
        {
        }

        constexpr strong_type& operator=(const value_type& v)
        noexcept(noexcept(std::is_nothrow_copy_assignable_v<Type>))
        requires std::is_copy_assignable_v<Type>
        {
            value_ = v;
            return *this;
        }

        constexpr strong_type& operator=(value_type&& v)
        noexcept(noexcept(std::is_nothrow_move_assignable_v<Type>))
        requires std::is_move_assignable_v<Type> && std::negation_v<std::is_reference<value_type>>
        {
            value_ = v;
            return *this;
        }

        [[nodiscard]] constexpr explicit operator value_type&()
        {
            return value_;
        }

        [[nodiscard]] constexpr explicit operator const value_type&() const
        {
            return value_;
        }

        [[nodiscard]] constexpr value_type& operator*() noexcept
        {
            return value_;
        }

        [[nodiscard]] constexpr const value_type& operator*() const noexcept
        {
            return value_;
        }

        [[nodiscard]] constexpr value_type* operator->() noexcept
        {
            return std::addressof(value_);
        }

        [[nodiscard]] constexpr const value_type* operator->() const noexcept
        {
            return std::addressof(value_);
        }

        [[nodiscard]] constexpr value_type& value() noexcept
        {
            return value_;
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
