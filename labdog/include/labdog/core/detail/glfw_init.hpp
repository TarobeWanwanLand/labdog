#ifndef LABDOG_GLFW_INIT_HPP
#define LABDOG_GLFW_INIT_HPP

#include <atomic>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "../common.hpp"

namespace ld::detail
{
    /// @brief GLFWの初期化と終了処理を管理する
    class glfw_init final
    {
    public:
        glfw_init()
        {
            // 総インスタンス数が0の場合、GLFWの初期化を行う
            if(instance_count_ == 0)
                if(glfwInit() == GLFW_FALSE)
                    throw std::runtime_error("Failed to initialize GLFW.");

            // 総インスタンス数をインクリメント
            ++instance_count_;
        }

        ~glfw_init() noexcept(false)
        {
            // 総インスタンス数が0ならエラー
            if(instance_count_ == 0)
                throw std::logic_error("Invalid value for number of instances.");

            // 総インスタンス数が1の場合、GLFWの終了処理を行う
            if(instance_count_ == 1)
                glfwTerminate();

            // 総インスタンス数をデクリメント
            --instance_count_;
        }

    private:
        inline static std::atomic_size_t instance_count_{}; //!< 総インスタンス数
    };
}

#endif // LABDOG_GLFW_INIT_HPP
