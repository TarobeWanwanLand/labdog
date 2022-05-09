#include <labdog/graphics/window.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

int main()
{
    using namespace ld;

    std::vector<std::unique_ptr<window>> windows;
    auto& main = windows.emplace_back(std::make_unique<window>());

    std::u8string a(u8"🥰aaあ🦴菅");

    while(!windows.empty())
    {
        window::update_all();

        std::erase_if(windows, [](const auto& x){ return x->should_close(); });
    }

    return 0;
}