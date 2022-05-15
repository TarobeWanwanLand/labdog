#include <labdog/core/window.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <boost/ptr_container/ptr_vector.hpp>
#include <labdog/core/dispatcher.hpp>
#include <labdog/core/point.hpp>
#include <labdog/core/strong_type.hpp>
#include <labdog/core/size.hpp>

struct Event
{
    int val;
};

struct Test
{
    void OnEvent(const Event& ev)
    {
        std::cout << ev.val << '\n';
    }
};

int main(ld::int32 argc, char* argv[])
{
    using namespace ld;

    std::vector<std::unique_ptr<window>> windows;

    windows.emplace_back(std::make_unique<window>());
    windows.emplace_back(std::make_unique<window>(args::size(200, 900), args::title(u8"🐕huga")));
    windows.emplace_back(std::make_unique<window>(args::title(u8"🐶hoge"), args::position(500, 800)));
    windows.emplace_back(std::make_unique<window>(args::position(900, 300)));

    while(!windows.empty())
    {
        window::update_all();

        std::erase_if(windows, [](const auto& w){ return w->should_close(); });
    }

    return 0;
}