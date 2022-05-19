//=========================================================
//
//  event.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_EVENT_HPP
#define LABDOG_EVENT_HPP

#include "key_code.hpp"
#include "axis_code.hpp"

namespace ld::event
{
    struct button_state_changed
    {
        window* window;
        key_code button;
        bool is_down;
    };

    struct axis_value_changed
    {
        window* window;
        axis_code axis;
        float value;
    };
}

#endif //LABDOG_EVENT_HPP