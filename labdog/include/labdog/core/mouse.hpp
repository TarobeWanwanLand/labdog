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
#include "common.hpp"
#include "dispatcher.hpp"

namespace ld
{
    /// @brief マウスクラス
    class mouse
    {
    public:
        /// @brief マウスのボタンコード
        enum buttons
        {
            left = 0,
            right,
            middle,
            x1,
            x2
        };

        /// @brief マウスの軸コード
        enum axes
        {
            cursor_x = 0,
            cursor_y,
            wheel_scroll
        };

    private:
        class impl;
        static std::unique_ptr<impl> impl_;
    };
}

#endif //LABDOG_MOUSE_HPP