//=========================================================
//
//  application.hpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_APPLICATION_HPP
#define LABDOG_APPLICATION_HPP

#include "common.hpp"
#include "dispatcher.hpp"
#include <boost/program_options.hpp>

namespace ld {
    class application final
    {
    public:
        application(int32 argc, char *argv[])
        {
            if(instance_)
                std::logic_error("The application is already instantiated.");

            instance_ = this;
        }

        ~application()
        {
            instance_ = nullptr;
        }

        [[nodiscard]] dispatcher& dispatcher() noexcept
        {
            return dispatcher_;
        }

        [[nodiscard]] static application& get()
        {
            if (!instance_)
                throw std::logic_error("The application instance does not exist.");

            return *instance_;
        }

    private:
        ld::dispatcher dispatcher_; //<! イベント発行

        static application* instance_; //<! アプリケーションのインスタンス
    };
}

#endif //LABDOG_APPLICATION_HPP