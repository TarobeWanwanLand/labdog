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

int listenter3(const event& event)
{
    const int val = event.a;
    std::cout << val << '\n';
    return val;
}

int listenter4(const event& event)
{
    const int val = event.a * 2;
    std::cout << val << '\n';
    return val;
}

int main()
{
    using namespace ld;

//    ld::signal<int(event)> sig;
//
//    sig.connect(listenter3);
//    sig.connect(listenter4);
//    sig.connect(listenter3);
//
//    auto res = sig.dispatch(event{ 10 });

    detail::signal_impl_handler<listenter>;

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