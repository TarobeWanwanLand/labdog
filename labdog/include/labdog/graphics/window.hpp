//=========================================================
//
//  window.hpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_WINDOW_HPP
#define LABDOG_WINDOW_HPP

#include "../core/common.hpp"
#include <GLFW/glfw3.h>

namespace ld
{
    class window final
    {
    public:
        /// @brief ウィンドウハンドル型
        using handle_type = GLFWwindow*;

        window(int32 handle, int32 height);
        ~window();

        window(const window&) = delete;
        window& operator=(const window&) = delete;
        window(window&&) = delete;
        window& operator=(window&&) = delete;

        void update() noexcept;

        [[nodiscard]] bool should_close() noexcept;

    private:
        static size_t window_count_;    //!< 総ウィンドウ数

        handle_type window_;    //!< ウィンドウハンドル

        // TODO: タイトルメンバ変数を追加
        //string title_;
        int32 x_pos_;   //!< ウィンドウX座標
        int32 y_pos_;   //!< ウィンドウY座標
        int32 width_;   //!< ウィンドウ横幅
        int32 height_;  //!< ウィンドウ縦幅
    };
} // namespace ld

#endif //LABDOG_WINDOW_HPP
