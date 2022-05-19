#include <labdog/core/window.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <cmath>
#include <numbers>
#include <labdog/core/mouse.hpp>
#include <labdog/core/application.hpp>
#include <optional>

using namespace ld;

class example final : public application
{
public:
    example()
        : main_window{ args::title(u8"🐕"), args::position(100, 100) }
    {
    }

    ~example() noexcept override = default;

private:
    void start() override
    {

    }

    void tick() override
    {
        if(main_window.should_close())
            terminate();
    }

    window main_window;
};

int main(ld::int32 argc, char* argv[])
{
    using namespace ld;

    example app;
    app.run();

    return 0;
}