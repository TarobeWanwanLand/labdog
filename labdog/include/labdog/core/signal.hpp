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
#include <boost/functional.hpp>
#include <span>
#include "concepts.hpp"

namespace ld
{
    namespace detail
    {
        template <class Function> struct signal_impl;

        template <class Return, class... Types>
        requires std::is_same_v<Return, void>
        struct signal_impl<Return(*)(Types...)>
        {
            using function_type = Return(*)(Types...);
            using function_traits = boost::function_traits<function_type>;
            using result_type = typename function_traits::result_type;
            using sink_type = boost::signals2::signal<function_type>;
        };

        template <class Return, class... Types>
        requires std::negation_v<std::is_same<Return, void>>
        struct signal_impl<Return(*)(Types...)>
        {
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

            using function_type = Return(*)(Types...);
            using function_traits = boost::function_traits<function_type>;
            using result_type = typename function_traits::result_type;
            using sink_type = boost::signals2::signal<function_type, aggregate_values<std::span<result_type>>>;
        };

        template <class Function>
        struct signal_impl_handler : signal_impl<std::add_pointer_t<Function>> {};
    }

//    template <class Function>
//    class signal final : public detail::signal_impl<Function>
//    {
//        using impl_type = detail::signal_impl<Function>;
//
//    public:
//        signal() = default;
//        ~signal() = default;
//
//        signal(const signal& signal) = default;
//        signal(signal&& signal) noexcept = default;
//        signal& operator=(const signal& signal) = default;
//        signal& operator=(signal&& signal)  noexcept = default;
//
//        void connect(const impl_type::function_type& subscriber)
//        {
//            sink_.connect(subscriber);
//        }
//
//        template <class Func>
//        void disconnect(Func&& subscriber)
//        {
//            sink_.disconnect(std::forward<Func>(subscriber));
//        }
//
//        template <class... Args>
//        impl_type::result_type dispatch(Args&&... args)
//        {
//            return sink_(std::forward<Args>(args)...);
//        }
//
//        template <class... Args>
//        impl_type::result_type dispatch(Args&&... args) const
//        {
//            return sink_(std::forward<Args>(args)...);
//        }
//
//        void clear()
//        {
//            sink_.disconnect_all_slots();
//        }
//
//    private:
//        sink_type sink_;
//    };
}

#endif // LABDOG_SIGNAL_HPP