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
    size_t window::window_count_ = 0;

    window::window(int32 width, int32 height)
        : window_(nullptr)
        , x_pos_(0)
        , y_pos_(0)
        , width_(width)
        , height_(height)
    {
        // ウィンドウサイズに0以下の値を設定した場合エラー
        if(width_ <= 0 || height_ <= 0)
            throw std::out_of_range("Window size cannot be less than zero.");

        // 総ウィンドウ数が0の場合、GLFWの初期化を行う
        if(window_count_ == 0)
        {
            // GLFWの初期化
            if(glfwInit() == GLFW_FALSE)
                throw std::runtime_error("Failed to initialize GLFW.");

            // ウィンドウの設定
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, 0);
        }

        // TODO: アプリケーション名の変更が出来るようにする
        // ウィンドウを作成する
        window_ = glfwCreateWindow(static_cast<int32>(width), static_cast<int32>(height), "App", nullptr, nullptr);
        if(!window_)
            throw std::runtime_error("Failed to create window.");

        // 総ウィンドウ数をインクリメント
        ++window_count_;

        // ウィンドウ座標を取得
        glfwGetWindowPos(window_, &x_pos_, &y_pos_);

        // ウィンドウコールバックに使用するユーザーデータをセット
        glfwSetWindowUserPointer(window_, this);

        // TODO: ウィンドウ座標変更時のイベントを発行する
        glfwSetWindowPosCallback(window_, [](handle_type handle, int32 x_pos, int32 y_pos)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            data.x_pos_ = x_pos;
            data.y_pos_ = y_pos;
        });

        // TODO: ウィンドウサイズ変更時のイベントを発行する
        glfwSetWindowSizeCallback(window_, [](handle_type handle, int32 width, int32 height)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            data.width_ = width;
            data.height_ = height;
        });

        // TODO: キー操作時のイベントを発行する
        glfwSetKeyCallback(window_, [](handle_type handle, int32 key, int32 scancode, int32 action, int32 mods)
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
        glfwSetCharCallback(window_, [](handle_type handle, uint32 keycode)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));
        });

        // TODO: マウスボタン操作時のイベントを発行する
        glfwSetMouseButtonCallback(window_, [](handle_type handle, int32 button, int32 action, int32 mods)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

            switch (action)
            {
                case GLFW_RELEASE: break;
                case GLFW_PRESS: break;
            }
        });

        // TODO: スクロール時のイベントを発行する
        glfwSetScrollCallback(window_, [](handle_type handle, double x_pos, double y_pos)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));
        });

        // TODO: カーソル操作時のイベントを発行する
        glfwSetCursorPosCallback(window_, [](handle_type handle, double x_pos, double y_pos)
        {
            auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));
        });
    }

    window::~window()
    {
        // ウィンドウ作成に成功していた場合、ウィンドウを破棄する
        if(window_)
        {
            glfwDestroyWindow(window_);
            window_ = nullptr;

            // 総ウィンドウ数をデクリメント
            --window_count_;
        }

        // 総ウィンドウ数が0の場合、GLFWの終了処理を行う
        if(window_count_ == 0)
            glfwTerminate();
    }

    void window::update() noexcept
    {
        // ウィンドウイベントをポーリングする
        glfwPollEvents();
    }

    bool window::should_close() noexcept
    {
        // ウィンドウを閉じるべきか調べる
        return glfwWindowShouldClose(window_) == GLFW_TRUE;
    }
} // namespace ld