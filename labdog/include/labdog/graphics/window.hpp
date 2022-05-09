//=========================================================
//
//  window.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_WINDOW_HPP
#define LABDOG_WINDOW_HPP

#include "../core/common.hpp"
#include <atomic>
#include <GLFW/glfw3.h>

namespace ld
{
    /// @brief ウィンドウを管理する
    class window final
    {
    public:
        /// @brief ウィンドウハンドル型
        using handle_type = GLFWwindow*;

        window()
            : window(600, 400) {};

        /// @brief ウィンドウを構築する
        /// @param width ウィンドウの横幅
        /// @param width ウィンドウの縦幅
        window(int32 width, int32 height);

        /// @brief ウィンドウを破棄する
        ~window();

        window(const window&) = delete;
        window& operator=(const window&) = delete;
        window(window&&) = delete;
        window& operator=(window&&) = delete;

        void close() noexcept;

        /// @brief ウィンドウ座標を変更する
        /// @param x_pos X軸座標
        /// @param y_pos Y軸座標
        void set_position(int32 x_pos, int32 y_pos) noexcept;

        /// @brief ウィンドウサイズを変更する
        /// @param width ウィンドウ横幅
        /// @param height ウィンドウ縦幅
        void set_size(int32 width, int32 height) noexcept;

        /// @brief ウィンドウが閉じられているかを返す
        /// @return ウィンドウが閉じられているか
        [[nodiscard]] bool is_closed() const noexcept;

        /// @brief ウィンドウが閉じるべき状態かを返す
        /// @return ウィンドウを閉じるべきか
        [[nodiscard]] bool should_close() const noexcept;

        /// @brief 全てのウィンドウを更新する
        static void update_all() noexcept;

    private:
        static std::atomic_size_t window_count; //!< ウィンドウの総数

        handle_type handle_;    //!< ウィンドウハンドル

        // TODO: タイトルメンバ変数を追加
        //string title_;
        int32 x_pos_;   //!< ウィンドウX座標
        int32 y_pos_;   //!< ウィンドウY座標
        int32 width_;   //!< ウィンドウ横幅
        int32 height_;  //!< ウィンドウ縦幅
    };
} // namespace ld

#endif // LABDOG_WINDOW_HPP