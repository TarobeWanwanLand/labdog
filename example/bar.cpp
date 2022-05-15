#include <labdog/core/window.hpp>
#include <vector>
#include <memory>

int main(ld::int32 argc, char* argv[])
{
    using namespace ld;

    std::vector<std::unique_ptr<window>> windows;

    windows.emplace_back(std::make_unique<window>());
    windows.emplace_back(std::make_unique<window>(args::size(300, 900), args::title(u8"🐕huga")));
    windows.emplace_back(std::make_unique<window>(args::size(600, 150), args::title(u8"🐶hoge"), args::position(500, 500)));
    windows.emplace_back(std::make_unique<window>(args::position(900, 300)));

    while(!windows.empty())
    {
        window::update_all();

        std::erase_if(windows, [](const auto& w){ return w->should_close(); });
    }

    return 0;
}