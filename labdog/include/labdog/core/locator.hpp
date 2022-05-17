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
#include "dispatcher.hpp"

namespace ld
{
    class dispatcher;

    /// @brief サービスロケータ
    class locator final
    {
    public:
        static void provide_dispatcher(dispatcher* dispatcher)
        {
            if(!dispatcher)
                throw std::invalid_argument("The pointer to the dispatcher is nullptr.");

            dispatcher_ = dispatcher;
        }

        [[nodiscard]] static dispatcher* dispatcher_service()
        {
            return dispatcher_;
        }

    private:
        static inline dispatcher* dispatcher_{};
    };
}

#endif //LABDOG_LOCATOR_HPP