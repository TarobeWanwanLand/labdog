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
                throw std::logic_error("The application is already instantiated.");

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

            while (!should_terminate_)
            {
                glfwPollEvents();

                tick();
            }
        }

        static void terminate()
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