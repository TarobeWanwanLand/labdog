//=========================================================
//
//  window.cpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/window.hpp"
#include "labdog/core/assertion.hpp"

namespace ld
{
    std::atomic_size_t window::instance_count{0 };

    window::~window()
    {
        // ウィンドウを閉じる
        close();
    }

    void window::set_title(const string_view title) noexcept
    {
        // ウィンドウタイトルを変更する
        title_ = title;
        glfwSetWindowTitle(handle_, reinterpret_cast<const char*>(title_.data()));
    }

    void window::set_position(const point position) noexcept
    {
        // ウィンドウ座標を変更する
        // コールバックでメンバにも変更が反映される
        glfwSetWindowPos(handle_, position.x, position.y);
    }

    void window::set_size(const size size) noexcept
    {
        // ウィンドウサイズを変更する
        // コールバックでメンバにも変更が反映される
        glfwSetWindowSize(handle_, size.width, size.height);
    }

    bool window::is_closed() const noexcept
    {
        // ウィンドウハンドルが有効か
        return !handle_;
    }

    bool window::should_close() const noexcept
    {
        // ウィンドウを閉じるべきか調べる
        return glfwWindowShouldClose(handle_) == GLFW_TRUE;
    }

    void window::update_all() noexcept
    {
        // ウィンドウのイベント処理を行う
        glfwPollEvents();
    }

    void window::close() noexcept
    {
        // ウィンドウ作成に成功していた場合、ウィンドウを破棄する
        if(handle_)
        {
            // ウィンドウを破棄
            glfwDestroyWindow(handle_);
            handle_ = nullptr;

            // ウィンドウの総数をデクリメント
            --instance_count;
        }

        // 総ウィンドウ数が0の場合、GLFWの終了処理を行う
        if(instance_count == 0)
            glfwTerminate();
    }

    void window::create()
    {
        // ウィンドウが既に作成されていた場合エラー
        if(handle_)
            throw std::logic_error("The window has already been created.");

        // ウィンドウサイズの幅に0以下の値を設定した場合エラー
        if(size_.width <= 0 && size_.height <= 0)
            throw std::out_of_range("Window size cannot be less than zero.");

        // 総ウィンドウ数が0の場合、GLFWの初期化を行う
        if(instance_count == 0)
        {
            // GLFWの初期化
            if(glfwInit() == GLFW_FALSE)
                throw std::runtime_error("Failed to initialize GLFW.");

            // ウィンドウの設定
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        }

        // ウィンドウを作成する
        handle_ = glfwCreateWindow(
            size_.width,
            size_.height,
            reinterpret_cast<const char*>(title_.c_str()),
            nullptr,
            nullptr);
        if(!handle_)
            throw std::runtime_error("Failed to create window.");

        // 総ウィンドウ数をインクリメント
        ++instance_count;

        // ウィンドウ座標をセット
        glfwSetWindowPos(handle_, position_.x, position_.y);

        // ウィンドウコールバックに使用するユーザーデータをセット
        glfwSetWindowUserPointer(handle_, this);

        // ウィンドウ座標変更時のコールバックをセット
        glfwSetWindowPosCallback(handle_, on_position_changed);

        // ウィンドウサイズ変更時のコールバックをセット
        glfwSetWindowSizeCallback(handle_, on_size_changed);
    }

    void window::on_size_changed(handle_type handle, int32 width, int32 height)
    {
        auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

        data.size_.width = width;
        data.size_.height = height;
    }

    void window::on_position_changed(handle_type handle, int32 x_pos, int32 y_pos)
    {
        auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

        data.position_.x = x_pos;
        data.position_.y = y_pos;
    }
} // namespace ld