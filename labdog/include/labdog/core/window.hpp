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

#include <atomic>
#include <variant>
#include <GLFW/glfw3.h>
#include "common.hpp"
#include "string.hpp"
#include "strong_type.hpp"
#include "size.hpp"
#include "point.hpp"

namespace ld
{
    namespace detail
    {
        struct title_tag{};
        struct size_tag{};
        struct position_tag{};
    }

    namespace args
    {
        using title = strong_type<string_view, detail::title_tag>;
        using position = strong_type<point, detail::position_tag>;
        using size = strong_type<size, detail::size_tag>;
    }

    /// @brief ウィンドウを管理する
    class window final
    {
    public:
        /// @brief ウィンドウハンドル型
        using handle_type = GLFWwindow*;

        /// @brief オプション引数を基にウィンドウを構築する
        /// @tparam OptionalArgs オプションの可変長引数型
        /// @param options オプションの可変長引数
        template <class... OptionalArgs>
        [[nodiscard]] explicit window(OptionalArgs&&... options)
            : handle_()
            , title_(u8"labdog")
            , position_(100, 100)
            , size_(600, 400)
        {
            if constexpr(sizeof...(OptionalArgs) > 0)
                std::apply(
                    [this](auto&&... opt) { (apply_optional_arg(opt), ...); },
                    std::make_tuple(std::forward<OptionalArgs>(options)...));

            create();
        }

        void apply_optional_arg(const args::title title) noexcept
        {
            title_ = *title;
        }

        void apply_optional_arg(const args::position position) noexcept
        {
            position_ = *position;
        }

        void apply_optional_arg(const args::size size) noexcept
        {
            size_ = *size;
        }

        /// @brief ウィンドウを破棄する
        ~window();

        window(const window&) = delete;
        window& operator=(const window&) = delete;

        window(window&&) noexcept = default;
        window& operator=(window&&) noexcept = default;

        /// @brief ウィンドウを閉じる
        void close() noexcept;

        /// @brief ウィンドウタイトルを変更する
        /// @param title ウィンドウタイトル
        void set_title(string_view title) noexcept;

        /// @brief ウィンドウ座標を変更する
        /// @param position 座標
        void set_position(point position) noexcept;

        /// @brief ウィンドウサイズを変更する
        /// @param size ウィンドウ幅
        void set_size(size size) noexcept;

        /// @brief ウィンドウが閉じられているかを返す
        /// @return ウィンドウが閉じられているか
        [[nodiscard]] bool is_closed() const noexcept;

        /// @brief ウィンドウが閉じるべき状態かを返す
        /// @return ウィンドウを閉じるべきか
        [[nodiscard]] bool should_close() const noexcept;

        /// @brief 全てのウィンドウを更新する
        static void update_all() noexcept;

    private:
        /// @brief ウィンドウを作成する
        void create();

        static void on_position_changed(handle_type handle, int32 x_pos, int32 y_pos);
        static void on_size_changed(handle_type handle, int32 width, int32 height);

        static std::atomic_size_t instance_count; //!< ウィンドウの総数

        handle_type handle_;    //!< ウィンドウハンドル

        string title_;      //!< ウィンドウタイトル
        point position_;    //!< ウィンドウ座標
        size size_;         //!< ウィンドウ幅
    };
} // namespace ld

#endif // LABDOG_WINDOW_HPP