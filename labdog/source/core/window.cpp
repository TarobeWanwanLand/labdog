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

namespace ld {
    window::window()
        : handle_{}
        , title_{ default_title }
    {
        // ウィンドウを作成
        create();
    }

    window::~window()
    {
        // ウィンドウを閉じる
        close();
    }

    void window::set_title(const string_view title) noexcept
    {
        // ウィンドウタイトルを変更する
        title_ = title;
        glfwSetWindowTitle(handle_, reinterpret_cast<const char *>(title_.c_str()));
    }

    void window::set_position(const point position) noexcept
    {
        // ウィンドウ座標を変更する
        glfwSetWindowPos(handle_, position.x, position.y);
    }

    void window::set_size(const size size)
    {
        // ウィンドウサイズの幅に0以下の値を設定した場合エラー
        if (size.width <= 0 && size.height <= 0)
            throw std::out_of_range("Window size cannot be less than zero.");

        // ウィンドウサイズを変更する
        glfwSetWindowSize(handle_, size.width, size.height);
    }

    void window::set_opacity(float opacity) noexcept
    {
        // ウィンドウの透明度を変更する
        glfwSetWindowOpacity(handle_, opacity);
    }

    string_view window::get_title() const noexcept
    {
        // ウィンドウタイトルを返す
        return title_;
    }

    point window::get_position() const noexcept
    {
        // ウィンドウ座標を返す
        point result;
        glfwGetWindowPos(handle_, &result.x, &result.y);
        return result;
    }

    size window::get_size() const noexcept
    {
        // ウィンドウサイズを返す
        size result;
        glfwGetWindowSize(handle_, &result.width, &result.height);
        return result;
    }

    float window::get_opacity() const noexcept
    {
        // ウィンドウの透明度を返す
        return glfwGetWindowOpacity(handle_);
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

    void window::close() noexcept
    {
        // ウィンドウが開いている場合、ウィンドウを閉じる
        if (handle_) {
            // ウィンドウを破棄
            glfwDestroyWindow(handle_);
            handle_ = nullptr;
        }
    }

    void window::create()
    {
        // ウィンドウが既に作成されていた場合エラー
        if (handle_)
            throw std::logic_error("The window has already been created.");

        // ウィンドウの設定
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

        // ウィンドウを作成する
        handle_ = glfwCreateWindow(
            default_size.width,
            default_size.height,
            reinterpret_cast<const char*>(title_.c_str()),
            nullptr,
            nullptr);
        if (!handle_)
            throw std::runtime_error("Failed to create window.");

        // ウィンドウコールバックに使用するユーザーデータをセット
        glfwSetWindowUserPointer(handle_, this);

        // ウィンドウ座標変更時のコールバックをセット
        glfwSetWindowPosCallback(handle_, on_position_changed);

        // ウィンドウサイズ変更時のコールバックをセット
        glfwSetWindowSizeCallback(handle_, on_size_changed);
    }

    void window::on_position_changed(handle_type handle, int32 x_pos, int32 y_pos)
    {
        // TODO: イベント発行
    }

    void window::on_size_changed(handle_type handle, int32 width, int32 height)
    {
        // TODO: イベント発行
    }
}