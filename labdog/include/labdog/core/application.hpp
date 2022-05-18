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

#include <chrono>
#include <atomic>
#include <GLFW/glfw3.h>
#include "common.hpp"
#include "locator.hpp"

namespace ld {
    class application
    {
    public:
        application()
        {
            if(instance_)
                std::logic_error("The application is already instantiated.");

            instance_ = this;
        }

        virtual ~application() noexcept
        {
            instance_ = nullptr;
        }

        void run()
        {
            locator<dispatcher>::provide();

            start();

            const auto start_time = std::chrono::system_clock::now();
            auto current_time = start_time;

            while (!should_terminate_)
            {
                glfwPollEvents();

                tick();
            }
        }

        void terminate()
        {
            should_terminate_ = true;
        }

    private:
        virtual void start() {};
        virtual void tick() {};

    private:
        static std::atomic<application*> instance_; //<! アプリケーションのインスタンス
        static std::atomic_bool should_terminate_;
    };
}

#endif //LABDOG_APPLICATION_HPP