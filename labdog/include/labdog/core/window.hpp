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
#include "string_view.hpp"
#include "strong_type.hpp"
#include "size.hpp"
#include "point.hpp"
#include "type_traits.hpp"
#include "dispatcher.hpp"
#include "locator.hpp"
#include "detail/glfw_init.hpp"

namespace ld
{
    namespace detail
    {
        struct title_tag{};
        struct size_tag{};
        struct position_tag{};
        struct opacity_tag{};
    }

    namespace args
    {
        /// @brief ウィンドウのタイトル名
        using title = strong_type<string_view, detail::title_tag>;
        /// @brief ウィンドウの座標
        using position = strong_type<point, detail::position_tag>;
        /// @brief ウィンドウのサイズ
        using size = strong_type<size, detail::size_tag>;
        /// @brief ウィンドウの透明度
        using opacity = strong_type<float, detail::opacity_tag>;
    }

    /// @brief ウィンドウを管理する
    class window final
    {
    public:
        /// @brief ウィンドウハンドル型
        using handle_type = GLFWwindow*;

        /// @brief ウィンドウをデフォルト構築する
        [[nodiscard]] window();

        /// @brief オプション引数を基にウィンドウを構築する
        /// @tparam OptionalArgs オプションの可変長引数型
        /// @param options オプションの可変長引数
        /// @arg args::title ウィンドウのタイトル名
        /// @arg args::position ウィンドウの座標
        /// @arg args::size ウィンドウのサイズ
        template <class... OptionalArgs>
        [[nodiscard]] explicit window(OptionalArgs&&... options)
            : handle_{}
            , title_{ default_title }
            , dispatcher_{ &locator<dispatcher>::service() }
        {
            // 同じオプション引数が複数渡された場合エラー
            static_assert(is_none_of_v<OptionalArgs...>, "Multiple identical option arguments are passed.");

            // ウィンドウを作成
            create();

            // 全てのオプション引数を適応する
            static_cast<void>(std::initializer_list<int>{
                (static_cast<void>(apply_optional_arg(options)), 0)... }
            );
        }

        /// @brief ウィンドウを破棄する
        ~window();

        /// @brief コピーコンストラクタを削除
        window(const window&) = delete;

        /// @brief コポー代入演算子を削除
        window& operator=(const window&) = delete;

        /// @brief デフォルトムーブコンストラクタ
        window(window&&) noexcept = default;

        /// @brief デフォルトムーブ代入演算子
        window& operator=(window&&) noexcept = default;

        /// @brief ウィンドウを閉じる
        void close() noexcept;

        /// @brief ウィンドウタイトルを変更する
        /// @param title ウィンドウタイトル
        void set_title(string_view title);

        /// @brief ウィンドウ座標を変更する
        /// @param position 座標
        void set_position(point position);

        /// @brief ウィンドウサイズを変更する
        /// @param size ウィンドウ幅
        void set_size(size size);

        /// @brief ウィンドウの透明度を変更する
        /// @param opacity ウィンドウの透明度
        void set_opacity(float opacity);

        /// @brief ウィンドウタイトルを取得する
        /// @return ウィンドウタイトル
        [[nodiscard]] string_view get_title() const;

        /// @brief ウィンドウ座標を取得する
        /// @return ウィンドウ座標
        [[nodiscard]] point get_position() const;

        /// @brief ウィンドウサイズを取得する
        /// @return ウィンドウサイズ
        [[nodiscard]] size get_size() const;

        /// @brief ウィンドウの透明度を取得する
        /// @return ウィンドウの透明度
        [[nodiscard]] float get_opacity() const;

        /// @brief ウィンドウが閉じられているかを返す
        /// @return ウィンドウが閉じられているか
        [[nodiscard]] bool is_closed() const noexcept;

        /// @brief ウィンドウが閉じるべき状態かを返す
        /// @return ウィンドウを閉じるべきか
        [[nodiscard]] bool should_close() const;

    private:
        /// @brief ウィンドウを作成する
        void create();

        /// @brief オプション引数からウィンドウのタイトルをセットする
        void apply_optional_arg(const args::title title) noexcept
        {
            set_title(*title);
        }

        /// @brief オプション引数からウィンドウの座標をセットする
        void apply_optional_arg(const args::position position) noexcept
        {
            set_position(*position);
        }

        /// @brief オプション引数からウィンドウのサイズをセットする
        void apply_optional_arg(const args::size size) noexcept
        {
            set_size(*size);
        }

        /// @brief オプション引数からウィンドウの透明度をセットする
        void apply_optional_arg(const args::opacity opacity) noexcept
        {
            set_opacity(*opacity);
        }

        /// @brief ウィンドウサイズ変更時のコールバック
        static void on_size_changed(handle_type handle, int32 width, int32 height);

        /// @brief ウィンドウ座標変更時のコールバック
        static void on_position_changed(handle_type handle, int32 x_pos, int32 y_pos);

        static constexpr string_view default_title{ u8"" };     //!< デフォルトのタイトル名
        static constexpr size default_size{ 600, 400 }; //!< デフォルトのサイズ

        detail::glfw_init glfw_initializer_;   //!< GLFWの初期化＆解放
        handle_type handle_;        //!< ハンドル
        string title_;              //<! タイトル
        dispatcher* dispatcher_;    //<! イベント発行
    };
}

#endif // LABDOG_WINDOW_HPP