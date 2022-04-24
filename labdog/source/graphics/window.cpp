//=========================================================
//
//  window.cpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/graphics/window.hpp"
#include <cassert>

namespace ld
{
    uint32 window::window_count_ = 0;

    window::window(uint32 width, uint32 height)
        : window_(nullptr)
    {
        // 総ウィンドウ数が0の場合、GLFWの初期化を行う
        if(window_count_ == 0)
        {
            // glfwの初期化
            auto success = glfwInit();
            assert(success == GLFW_TRUE);

            // ウィンドウの設定
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, 0);
        }

        // TODO: アプリケーション名の変更が出来るようにする]
        // ウィンドウを作成する
        window_ = glfwCreateWindow(static_cast<int32>(width), static_cast<int32>(height), "App", nullptr, nullptr);
        if(window_)
            ++window_count_;
        else
            assert(false);

//        glfwSetWindowUserPointer(window_, &data_);
//
//        glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int32 width, int32 height)
//        {
//            window_data& data = *static_cast<window_data*>(glfwGetWindowUserPointer(window));
//            data.width = width;
//            data.height = height;
//        });
    }

    window::~window()
    {
        // ウィンドウ作成に成功していた場合、ウィンドウを破棄する
        if(window_)
        {
            glfwDestroyWindow(window_);
            --window_count_;
        }

        // 総ウィンドウ数が0の場合、GLFWの終了処理を行う
        if(window_count_ == 0)
            glfwTerminate();
    }
} // namespace ld