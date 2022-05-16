//=========================================================
//
//  type_traits.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_TYPE_TRAITS_HPP
#define LABDOG_TYPE_TRAITS_HPP

#include <type_traits>
#include <concepts>

namespace ld
{
    template <class T, class... Types>
    struct is_all_same : std::false_type
    { };

    template <class T>
    struct is_all_same<T> : std::true_type
    { };

    template <class T, class U, class... Ts>
    struct is_all_same<T, U, Ts...> :
        std::conjunction<std::is_same<T, U>, is_all_same<T, Ts...>>
    { };

    template <class T, class... Ts>
    struct is_all_not_same : std::false_type
    { };

    template <class T>
    struct is_all_not_same<T> : std::true_type
    { };

    template <class T, class U, class... Ts>
    struct is_all_not_same<T, U, Ts...> :
        std::conditional_t<
            std::negation_v<std::disjunction<std::is_same<T, U>, std::is_same<T, Ts>...>>,
            is_all_not_same<U, Ts...>,
            std::false_type>
    { };

    template <class T, class... Ts>
    inline constexpr bool is_all_same_v = is_all_same<T, Ts...>::value;

    template <class T, class... Ts>
    inline constexpr bool is_all_not_same_v = is_all_not_same<T, Ts...>::value;
}

#endif // LABDOG_TYPE_TRAITS_HPP
