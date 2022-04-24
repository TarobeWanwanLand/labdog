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
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ld
{
    class window final
    {
    public:
        window(uint32 width, uint32 height);
        ~window();

    private:
        /// @brief ウィンドウ情報構造体
        struct window_data
        {
            //string title;
            uint32 width;
            uint32 height;
            bool vsync;
        };

        static uint32 window_count_;    //!< 総ウィンドウ数

        GLFWwindow* window_;    //!< GLFWのウィンドウ
        window_data data_;      //!< ウィンドウ情報
    };
} // namespace ld

#endif //LABDOG_WINDOW_HPP
