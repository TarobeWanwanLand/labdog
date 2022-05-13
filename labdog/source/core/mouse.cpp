//=========================================================
//
//  mouse.cpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/mouse.hpp"
#include "labdog/core/application.hpp"

namespace ld
{
    class mouse::impl final
    {
    public:
        impl()
            : x_pos_(0)
            , y_pos_(0)
            , x_move_(0)
            , y_move_(0)
        {
            auto& app = application::get();
            dispatcher_ = &app.dispatcher();
        }

        ~impl() noexcept = default;

        void on_cursor_moved(int32 x_pos, int32 y_pos)
        {
            x_move_ += x_pos - x_pos_;
            y_move_ += y_pos - y_pos_;
            x_pos_ = x_pos;
            y_pos_ = y_pos;
        }

        void on_button_pressed(int32 x_pos, int32 y_pos)
        {
            x_move_ += x_pos - x_pos_;
            y_move_ += y_pos - y_pos_;
            x_pos_ = x_pos;
            y_pos_ = y_pos;
        }

    private:
        int32 x_pos_;
        int32 y_pos_;
        int32 x_move_;
        int32 y_move_;

        dispatcher* dispatcher_{};
    };
}