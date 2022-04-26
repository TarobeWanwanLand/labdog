#include <exception>
#include <iostream>
#include <random>
#include <labdog/graphics/window_manager.hpp>
#include <labdog/graphics/graphics.hpp>

int main(int argc, char *argv[])
{
    try
    {
        for (ld::int32 i = 0; i < 3; ++i)
        {
            ld::window_manager::create(600, 400);
        }

        while (!ld::window_manager::empty())
        {
            ld::window_manager::update();
        }
    }
    catch(std::exception exception)
    {
        std::cerr << exception.what();
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
