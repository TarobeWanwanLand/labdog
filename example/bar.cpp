#include <labdog/core/window.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <cmath>
#include <numbers>
#include <labdog/core/mouse.hpp>
#include <labdog/core/application.hpp>

class example : public ld::application
{
public:
    example()
    {

    }

private:
    void start() override
    {
        using namespace ld;

        std::thread t1([]
        {
            window w(args::title(u8"🐕"), args::size(800, 1000), args::position(100, 100));

            while(!w.should_close())
            {
                glfwPollEvents();
            }
        });

        t1.join();
    }

    void tick() override
    {

    }
};

int main(ld::int32 argc, char* argv[])
{
    using namespace ld;

    example app;
    app.run();

    return 0;
}