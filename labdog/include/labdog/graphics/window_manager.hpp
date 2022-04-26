
#ifndef LABDOG_WINDOW_MANAGER_HPP
#define LABDOG_WINDOW_MANAGER_HPP

#include <vector>
#include <memory>
#include "window.hpp"

namespace ld
{
    class window_manager final
    {
    public:
        ~window_manager() = delete;

        window_manager(const window_manager&) = delete;
        window_manager& operator=(const window_manager&) = delete;
        window_manager(window_manager&&) = delete;
        window_manager& operator=(window_manager&&) = delete;

        static window* create(int32 width, int32 height);

        static void update() noexcept;

        [[nodiscard]] static bool empty() noexcept;

    private:
        static std::vector<std::unique_ptr<window>> windows_;
    };
} // namespace ld

#endif // LABDOG_WINDOW_MANAGER_HPP