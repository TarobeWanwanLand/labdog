//=========================================================
//
//  mouse.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_MOUSE_HPP
#define LABDOG_MOUSE_HPP

#include <memory>
#include <bitset>
#include <magic_enum.hpp>
#include "common.hpp"
#include "application.hpp"
#include "window.hpp"
#include "dispatcher.hpp"
#include "point.hpp"
#include "key_code.hpp"
#include "axis_code.hpp"
#include "locator.hpp"

namespace ld
{
    namespace detail
    {
        struct button_state_changed_event
        {
            window* window;
            key_code button;
            bool is_pressed;
        };

        struct axis_value_changed_event
        {
            window* window;
            axis_code axis;
            float value;
        };
    }

    /// @brief マウスクラス
    class mouse
    {
    public:
        mouse()
            : current_button_states_{}
            , previous_button_states_{}
            , current_axes_states_{}
            , previous_axes_states_{}
            , dispatcher_{}
        {
            dispatcher_ = &locator::dispatcher_service();

            dispatcher_->subscribe<detail::button_state_changed_event, &mouse::on_button_state_changed>(*this);
            dispatcher_->subscribe<detail::axis_value_changed_event, &mouse::on_axis_value_changed>(*this);
        }

        ~mouse() noexcept
        {
            dispatcher_->unsubscribe<detail::button_state_changed_event>(*this);
            dispatcher_->unsubscribe<detail::axis_value_changed_event>(*this);
        }

    private:
        static constexpr size_t num_button{ 5 };    //!< ボタン数
        static constexpr size_t num_axes{ 3 };      //!< 軸数

        void on_button_state_changed(const detail::button_state_changed_event event)
        {
            current_button_states_[static_cast<size_t>(event.button)] = event.is_pressed;
        }

        void on_axis_value_changed(const detail::axis_value_changed_event event) noexcept
        {
            current_axes_states_[static_cast<size_t>(event.axis)] = event.value;
        }

        std::bitset<mouse::num_button> current_button_states_;
        std::bitset<mouse::num_button> previous_button_states_;

        std::array<float, mouse::num_axes> current_axes_states_;
        std::array<float, mouse::num_axes> previous_axes_states_;

        dispatcher* dispatcher_;
    };
}

#endif //LABDOG_MOUSE_HPP