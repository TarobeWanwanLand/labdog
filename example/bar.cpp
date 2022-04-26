#include <exception>
#include <iostream>
#include <labdog/graphics/window.hpp>
#include <labdog/graphics/graphics.hpp>

int main(int argc, char *argv[])
{
    try
    {
        ld::window window(600u, 400u);

        while (!window.should_close())
        {
            window.update();
        }
    }
    catch(std::exception exception)
    {
        std::cerr << exception.what();
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
