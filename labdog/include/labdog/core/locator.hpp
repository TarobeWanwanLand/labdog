//=========================================================
//
//  locator.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_LOCATOR_HPP
#define LABDOG_LOCATOR_HPP

#include <stdexcept>
#include <type_traits>
#include <entt/entt.hpp>
#include "dispatcher.hpp"

namespace ld
{
    /// @brief サービスロケータ
    template <class Service>
    class locator final
    {
        static_assert(
            std::is_same_v<Service, std::remove_cvref_t<Service>>,
            "Must be a non-const, non-volatile type.");

    public:
        using service_type = Service;
        using locator_type = entt::locator<Service>;

        locator() = delete;
        ~locator() = delete;

        template <class... Args>
        static void provide(Args&&... args)
        {
            locator_type::emplace(std::forward<Args>(args)...);
        }

        static service_type& service() noexcept
        {
            return locator_type::value();
        }

        template <class... Args>
        static service_type& service_or(Args&&... args)
        {
            return locator_type::value_or(std::forward<Args>(args)...);
        }
    };
}

#endif //LABDOG_LOCATOR_HPP