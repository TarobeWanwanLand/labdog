#include <exception>
#include <iostream>
#include <random>
#include <labdog/graphics/window_manager.hpp>
#include <labdog/graphics/graphics.hpp>
<<<<<<< Updated upstream
#include <labdog/core/unicode.hpp>
=======
<<<<<<< Updated upstream
=======
#include <labdog/core/unicode_convert.hpp>
>>>>>>> Stashed changes
>>>>>>> Stashed changes

int main(int argc, char *argv[])
{
    try
    {
<<<<<<< Updated upstream
        auto str = ld::utf32To16(U"あ");

=======
<<<<<<< Updated upstream
=======
        // TODO: テスト書く
        std::u32string str = ld::utf8_to_utf32(u8"あvbsいaう");

>>>>>>> Stashed changes
>>>>>>> Stashed changes
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
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}