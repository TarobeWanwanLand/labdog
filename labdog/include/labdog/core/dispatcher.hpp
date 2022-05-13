//=========================================================
//
//  dispatcher.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_DISPATCHER_HPP
#define LABDOG_DISPATCHER_HPP

#include <entt/signal/dispatcher.hpp>

namespace ld
{
    /// @brief イベント発行クラス
    class dispatcher final
    {
    public:
        /// @brief イベント発行クラス型
        using dispatcher_type = entt::dispatcher;
        /// @brief 要素数を表す符号なし整数型
        using size_type = dispatcher_type::size_type;

        dispatcher() = default;
        ~dispatcher() noexcept = default;

        dispatcher(const dispatcher&) = delete;
        dispatcher& operator=(const dispatcher&) = delete;

        dispatcher(dispatcher&&) noexcept = default;
        dispatcher& operator=(dispatcher&&) = default;

        /// @brief 中身を入れ替える
        /// @param dispr 他のイベント発行クラス
        void swap(dispatcher& dispr)
        {
            dispatcher_.swap(dispr.dispatcher_);
        }

        /// @brief イベントを購読する
        /// @tparam Event イベント型
        /// @tparam Candidate 購読するメソッドのポインタ型
        /// @tparam Receiver 購読するクラス型
        /// @param receiver 購読するクラス
        template <typename Event, auto Candidate, typename Receiver>
        void subscribe(Receiver&& receiver)
        {
            dispatcher_.sink<Event>().connect<Candidate>(&std::forward<Receiver>(receiver));
        }

        /// @brief イベントを購読解除する
        /// @tparam Event イベント型
        /// @tparam Receiver 購読解除するクラス型
        /// @param  receiver 購読解除するクラス
        template <typename Event, typename Receiver>
        void unsubscribe(Receiver&& receiver)
        {
            dispatcher_.sink<Event>().disconnect(&std::forward<Receiver>(receiver));
        }

        /// @brief イベントを発行する
        /// @tparam Event イベント型
        /// @tparam Args イベントを構築する引数型
        /// @param  args イベントを構築する引数
        template <typename Event, typename... Args>
        void dispatch(Args&&... args)
        {
            dispatcher_.trigger(Event{ std::forward<Args>(args)... });
        }

        /// @brief イベントをキューにプッシュする
        /// @tparam Event イベント型
        /// @tparam Args イベントを構築する引数型
        /// @param  args イベントを構築する引数
        template <typename Event, typename... Args>
        void enqueue(Args&&... args)
        {
            dispatcher_.enqueue<Event>(Event{ std::forward<Args>(args)... });
        }

        /// @brief　イベントキューのイベントを全て発行する
        void update() const
        {
            dispatcher_.update();
        }

        /// @brief リスナーを全て登録解除
        void clear()
        {
            dispatcher_.clear();
        }

        /// @brief 特定のイベントのリスナーを全て登録解除
        /// @tparam Event リスナーを解除するイベント型
        template <typename Event>
        void clear()
        {
            dispatcher_.clear<Event>();
        }

        /// @brief イベントキュー内のイベントの総数
        [[nodiscard]] size_type size() const noexcept
        {
            dispatcher_.size();
        }

        /// @brief イベントキュー内の特定のイベントの総数
        /// @tparam イベント型
        template <class Event>
        [[nodiscard]] size_type size() const noexcept
        {
            dispatcher_.size<Event>();
        }

    private:
        dispatcher_type dispatcher_;   //!< イベント発行クラス
    };
}

#endif // LABDOG_DISPATCHER_HPP