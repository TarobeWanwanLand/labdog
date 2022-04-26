#include "labdog/graphics/window_manager.hpp"
#include <algorithm>
#include <stdexcept>

namespace ld
{
    std::vector<std::unique_ptr<window>> window_manager::windows_;

    window* window_manager::create(int32 width, int32 height)
    {
        // 総ウィンドウ数が0の場合、GLFWの初期化を行う
        if(windows_.empty())
        {
            // GLFWの初期化
            if(glfwInit() == GLFW_FALSE)
                throw std::runtime_error("Failed to initialize GLFW.");

            // ウィンドウの設定
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            //glfwWindowHint(GLFW_RESIZABLE, 0);
        }

        auto& ret = windows_.emplace_back(std::make_unique<window>(width, height));
        return ret.get();
    }

    void window_manager::update() noexcept
    {
        // ウィンドウのイベント処理を行う
        glfwPollEvents();

        // 閉じられたウィンドウを破棄する
        std::erase_if(windows_, [](const std::unique_ptr<window>& window)
        {
           return window->should_close();
        });

        // 総ウィンドウ数が0の場合、GLFWの終了処理を行う
        if(windows_.empty())
            glfwTerminate();
    }

    bool window_manager::empty() noexcept
    {
        return windows_.empty();
    }
}