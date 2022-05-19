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
#include "locator.hpp"
#include "event.hpp"
#include "logger.hpp"

namespace ld
{
    /// @brief マウスクラス
    class mouse
    {
    public:
        mouse()
            : current_button_states_{}
            , previous_button_states_{}
            , current_axes_states_{}
            , previous_axes_states_{}
            , dispatcher_{ &locator<dispatcher>::service() }
        {
            dispatcher_->subscribe<event::button_state_changed, &mouse::on_button_state_changed>(*this);
            dispatcher_->subscribe<event::axis_value_changed, &mouse::on_axis_value_changed>(*this);
        }

        ~mouse() noexcept
        {
            dispatcher_->unsubscribe<event::button_state_changed>(*this);
            dispatcher_->unsubscribe<event::axis_value_changed>(*this);
        }

    private:
        static constexpr size_t num_button{ 5 };    //!< ボタン数
        static constexpr size_t num_axes{ 3 };      //!< 軸数

        void on_button_state_changed(const event::button_state_changed& event)
        {
            current_button_states_[static_cast<size_t>(event.button)] = event.is_down;
        }

        void on_axis_value_changed(const event::axis_value_changed& event) noexcept
        {
            current_axes_states_[static_cast<size_t>(event.axis)] = event.value;

            std::cout << magic_enum::enum_flags_name(event.axis) << ": " << event.value << '\n';
        }

        std::bitset<mouse::num_button> current_button_states_;
        std::bitset<mouse::num_button> previous_button_states_;

        std::array<float, mouse::num_axes> current_axes_states_;
        std::array<float, mouse::num_axes> previous_axes_states_;

        dispatcher* dispatcher_;
    };
}

#endif //LABDOG_MOUSE_HPP