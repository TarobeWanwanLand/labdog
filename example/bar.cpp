#include <labdog/core/window.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <cmath>
#include <numbers>
#include <labdog/core/mouse.hpp>
#include <labdog/core/application.hpp>

int main(ld::int32 argc, char* argv[])
{
    using namespace ld;

    application app(argc, argv);
    mouse mouse;

    std::thread t1([]
    {
        window w(args::title(u8"🐕"), args::size(800, 1000), args::position(100, 100));

        const auto start_time = std::chrono::system_clock::now();
        auto current_time = start_time;

        while(!w.should_close())
        {
            current_time = std::chrono::system_clock::now();

            const auto elapced_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

            const float o = (std::sin(static_cast<float>(elapced_ms) * 0.001f) + 1.0f) * 0.5f;

            w.set_opacity(o);

            glfwPollEvents();
        }
    });

    t1.join();

    return 0;
}