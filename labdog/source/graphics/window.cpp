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
#include "labdog/core/assertion.hpp"

namespace ld
{
    window::window(int32 width, int32 height)
        : handle_(nullptr)
        , x_pos_(0)
        , y_pos_(0)
        , width_(width)
        , height_(height)
    {
        // ウィンドウサイズに0以下の値を設定した場合エラー
        if(width_ <= 0 || height_ <= 0)
            throw std::out_of_range("Window size cannot be less than zero.");

        // TODO: アプリケーション名の変更が出来るようにする
        // ウィンドウを作成する
        handle_ = glfwCreateWindow(
            static_cast<int32>(width),
            static_cast<int32>(height),
            "App",
            nullptr,
            nullptr);
        if(!handle_)
            throw std::runtime_error("Failed to create window.");

        // ウィンドウ座標を取得
        glfwGetWindowPos(handle_, &x_pos_, &y_pos_);

        // ウィンドウコールバックに使用するユーザーデータをセット
        glfwSetWindowUserPointer(handle_, this);

        // TODO: ウィンドウ座標変更時のイベントを発行する
        glfwSetWindowPosCallback(handle_, [](handle_type handle, int32 x_pos, int32 y_pos)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            data.x_pos_ = x_pos;
            data.y_pos_ = y_pos;
        });

        // TODO: ウィンドウサイズ変更時のイベントを発行する
        glfwSetWindowSizeCallback(handle_, [](handle_type handle, int32 width, int32 height)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            data.width_ = width;
            data.height_ = height;
        });

        // TODO: キー操作時のイベントを発行する
        glfwSetKeyCallback(handle_, [](handle_type handle, int32 key, int32 scancode, int32 action, int32 mods)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            switch (action)
            {
                case GLFW_RELEASE: break;
                case GLFW_PRESS: break;
                case GLFW_REPEAT: break;
            }
        });

        // TODO: 文字入力時のイベントを発行する
        glfwSetCharCallback(handle_, [](handle_type handle, uint32 keycode)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));
        });

        // TODO: マウスボタン操作時のイベントを発行する
        glfwSetMouseButtonCallback(handle_, [](handle_type handle, int32 button, int32 action, int32 mods)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            switch (action)
            {
                case GLFW_RELEASE: break;
                case GLFW_PRESS: break;
            }
        });

        // TODO: スクロール時のイベントを発行する
        glfwSetScrollCallback(handle_, [](handle_type handle, double x_pos, double y_pos)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));
        });

        // TODO: カーソル操作時のイベントを発行する
        glfwSetCursorPosCallback(handle_, [](handle_type handle, double x_pos, double y_pos)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));
        });

        // TODO: コントローラー接続/切断時のイベントを発行する
        glfwSetJoystickCallback([](int32 jid, int32 event)
        {
            switch (event)
            {
                case GLFW_CONNECTED: break;
                case GLFW_DISCONNECTED: break;
            }
        });
    }

    window::~window()
    {
        // ウィンドウ作成に成功していた場合、ウィンドウを破棄する
        if(handle_)
        {
            // ウィンドウを破棄
            glfwDestroyWindow(handle_);
            handle_ = nullptr;
        }
    }

    void window::set_position(int32 x_pos, int32 y_pos) noexcept
    {
        // ウィンドウ座標を変更する
        glfwSetWindowPos(handle_, x_pos, y_pos);
    }

    void window::set_size(int32 width, int32 height) noexcept
    {
        // ウィンドウサイズを変更する
        glfwSetWindowSize(handle_, width, height);
    }

    bool window::should_close() noexcept
    {
        // ウィンドウを閉じるべきか調べる
        return glfwWindowShouldClose(handle_) == GLFW_TRUE;
    }
} // namespace ld