#include <labdog/core/window.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

int main(ld::int32 argc, char* argv[])
{
    using namespace ld;

    std::thread t1([]
    {
        window w; while(!w.should_close()) { glfwPollEvents(); }
    });

    t1.join();

    return 0;
}