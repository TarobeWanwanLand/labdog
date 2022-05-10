//=========================================================
//
//  window.cpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/graphics/window.hpp"
#include "labdog/core/assertion.hpp"

namespace ld
{
    std::atomic_size_t window::window_count{ 0 };

    window::window(const string_view title, const int32 width, const int32 height)
        : handle_(nullptr)
        , title_(title)
        , x_pos_(0)
        , y_pos_(0)
        , width_(width)
        , height_(height)
    {
        // ウィンドウサイズに0以下の値を設定した場合エラー
        if(width_ <= 0 || height_ <= 0)
            throw std::out_of_range("Window size cannot be less than zero.");

        // 総ウィンドウ数が0の場合、GLFWの初期化を行う
        if(window_count == 0)
        {
            // GLFWの初期化
            if(glfwInit() == GLFW_FALSE)
                throw std::runtime_error("Failed to initialize GLFW.");

            // ウィンドウの設定
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        }

        // ウィンドウを作成する
        handle_ = glfwCreateWindow(
            static_cast<int32>(width_),
            static_cast<int32>(height_),
            reinterpret_cast<const char*>(title_.c_str()),
            nullptr,
            nullptr);
        if(!handle_)
            throw std::runtime_error("Failed to create window.");

        ++window_count;

        // ウィンドウ座標を取得
        glfwGetWindowPos(handle_, &x_pos_, &y_pos_);

        // ウィンドウコールバックに使用するユーザーデータをセット
        glfwSetWindowUserPointer(handle_, this);

        // ウィンドウ座標変更時のコールバックをセット
        glfwSetWindowPosCallback(handle_, on_position_changed);

        // ウィンドウサイズ変更時のコールバックをセット
        glfwSetWindowSizeCallback(handle_, on_size_changed);
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
        glfwSetWindowTitle(handle_, reinterpret_cast<const char*>(title_.data()));
    }

    void window::set_position(const int32 x_pos, const int32 y_pos) noexcept
    {
        // ウィンドウ座標を変更する
        // コールバックでメンバにも変更が反映される
        glfwSetWindowPos(handle_, x_pos, y_pos);
    }

    void window::set_size(const int32 width, const int32 height) noexcept
    {
        // ウィンドウサイズを変更する
        // コールバックでメンバにも変更が反映される
        glfwSetWindowSize(handle_, width, height);
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
            --window_count;
        }

        // 総ウィンドウ数が0の場合、GLFWの終了処理を行う
        if(window_count == 0)
            glfwTerminate();
    }

    void window::on_size_changed(handle_type handle, int32 width, int32 height)
    {
        auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

        data.width_ = width;
        data.height_ = height;
    }

    void window::on_position_changed(handle_type handle, int32 x_pos, int32 y_pos)
    {
        auto& data = *static_cast<window*>(glfwGetWindowUserPointer(handle));

        data.x_pos_ = x_pos;
        data.y_pos_ = y_pos;
    }
} // namespace ld