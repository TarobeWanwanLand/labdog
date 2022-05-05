﻿#include <exception>
#include <iostream>
#include <random>
#include <labdog/graphics/window_manager.hpp>
#include <labdog/graphics/graphics.hpp>
#include <labdog/core/string.hpp>
#include <labdog/core/charset_convert.hpp>
#include <labdog/core/logger.hpp>

int main(int argc, char *argv[])
{
    try
    {
        ld::string str(U"aあbc🥰def🦴");

        ld::logger::trace(str);

        for (ld::int32 i = 0; i < 3; ++i)
        {
            ld::window_manager::create(600, 400);
        }

        while (ld::window_manager::exists())
        {
            ld::window_manager::update();
        }
    }
    catch(std::exception exception)
    {
        std::cerr << exception.what();
        std::getchar();
        return EXIT_FAILURE;
    }

    std::getchar();
    return EXIT_SUCCESS;
}