//=========================================================
//
//  window_manager.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_WINDOW_MANAGER_HPP
#define LABDOG_WINDOW_MANAGER_HPP

#include <vector>
#include <memory>
#include "window.hpp"

namespace ld
{
    /// @brief 複数のウィンドウを一括管理する
    class window_manager final
    {
    public:
        /// @brief ウィンドウを作成する
        /// @param width ウィンドウの横幅
        /// @param width ウィンドウの縦幅
        static window* create(int32 width, int32 height);

        /// @brief 全てのウィンドウを更新する
        static void update() noexcept;

        /// @brief ウィンドウが存在しているかを返す
        /// @return ウィンドウが存在しているか
        [[nodiscard]] static bool exists() noexcept;

    private:
        static std::vector<std::unique_ptr<window>> windows_;   //!< 有効なウィンドウのリスト
    };
} // namespace ld

#endif // LABDOG_WINDOW_MANAGER_HPP