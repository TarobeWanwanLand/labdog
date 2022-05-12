#include <labdog/graphics/window.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <labdog/core/signal.hpp>

struct event
{
    int a = 0;
};

void listenter(const event& event)
{
    std::cout << event.a << '\n';
}

void listenter2(const event& event)
{
    std::cout << event.a * event.a << '\n';
}

void listenter3(const event& event)
{
    std::cout << event.a * event.a << '\n';
}

int main()
{
    using namespace ld;

    signal<void(event)> sig;
    signal<int(event)> sig2;

//    signal.connect(listenter);
//    signal.connect(listenter2);
//    signal.connect(listenter2);
//
//    signal.dispatch(event{3 });
//
//    signal.disconnect(listenter2);
//
//    signal.dispatch(event{2 });

    std::vector<std::unique_ptr<window>> windows;
    auto& main = windows.emplace_back(
        std::make_unique<window>(u8"🐕LabDog🦴", 600, 400));

    while(!windows.empty())
    {
        window::update_all();

        std::erase_if(windows, [](const auto& x){ return x->should_close(); });
    }

    return 0;
}