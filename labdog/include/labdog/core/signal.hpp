//=========================================================
//
//  signal.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_SIGNAL_HPP
#define LABDOG_SIGNAL_HPP

#include <boost/signals2.hpp>
#include <span>

namespace ld
{
    template <class Function>
    class signal final
    {
    private:
        template <class>
        static constexpr bool always_false = false;

        template <class T>
        struct function_impl
        {
            static_assert(always_false<T>, "Do not accept non-functional types as template arguments.");
        };

        template <class Result, class... Args>
        struct function_impl<Result (Args...)>
        {
            using result_type = Result;
            using arg_types = std::tuple<Args...>;
        };

        template <class View>
        struct aggregate_values
        {
            using result_type = View;

            template <class InputIterator>
            [[nodiscard]] result_type operator()(InputIterator first, InputIterator last) const noexcept
            {
                return View{ first, last };
            }
        };

    public:
        using function_trait = function_impl<Function>;
        using result_type = typename function_trait::result_type;
        using arg_types = typename function_trait::arg_types;
        using sink_type = std::conditional<std::is_void_v<result_type>,
            boost::signals2::signal<Function>,
            boost::signals2::signal<Function, aggregate_values<std::span<result_type>>>>;

        signal() = default;
        ~signal() = default;

        signal(const signal& signal) = default;
        signal(signal&& signal) = default;
        signal& operator=(const signal& signal) = default;
        signal& operator=(signal&& signal) = default;

//        template <class Func>
//        void connect(Func&& subscriver)
//        {
//            sink_.connect(std::forward<Func>(subscriver));
//        }
//
//        template <class Func>
//        void disconnect(Func&& subscriver)
//        {
//            sink_.disconnect(std::forward<Func>(subscriver));
//        }
//
//        template <class... Args>
//        void dispatch(Args&&... args)
//        {
//            static_cast<void>(sink_(std::forward<Args>(args)...));
//        }
//
//        template <class... Args>
//        void dispatch(Args&&... args) const
//        {
//            static_cast<void>(sink_(std::forward<Args>(args)...));
//        }
//
//        template <class... Args, std::output_iterator<result_type> OutputIterator>
//        requires (!requires { std::is_void_v<result_type>; })
//        void collect(Args&&... args, OutputIterator dest)
//        {
//            const auto results = sink_(std::forward<Args>(args)...);
//            std::copy(results.begin(), results.end(), dest);
//        }
//
//        template <class... Args, std::output_iterator<result_type> OutputIterator>
//        requires (!requires { std::is_void_v<result_type>; })
//        void collect(Args&&... args, OutputIterator dest) const
//        {
//            const auto results = sink_(std::forward<Args>(args)...);
//            std::copy(results.begin(), results.end(), dest);
//        }
//
//        void clear()
//        {
//            sink_.disconnect_all_slots();
//        }

    private:
        sink_type sink_;
    };
}

#endif // LABDOG_SIGNAL_HPP