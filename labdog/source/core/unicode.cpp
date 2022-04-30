//=========================================================
//
//  unicode.cpp is part of the labdog project.
<<<<<<< Updated upstream
//  Copyright(c) 2022 Tomomi murakami.
=======
//  Copyright (C) 2022 TarobeWanwanLand.
>>>>>>> Stashed changes
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/unicode.hpp"
<<<<<<< Updated upstream
#include <unicode/ucnv.h>
=======
>>>>>>> Stashed changes
#include "labdog/core/assertion.hpp"

namespace ld
{
<<<<<<< Updated upstream
    std::u16string utf32To16(const string_view sv)
    {
        char buf2[10000];
        UErrorCode err = U_ZERO_ERROR;
        auto r = ucnv_convert_72(
            "UTF-16", // toConverterName
            "UTF-32",      // fromConverterName
            buf2,         // target
            sizeof(buf2), // targetCapacity
            reinterpret_cast<const char*>(sv.data()),          // source
            sv.size(),  // sourceLength
            &err);        // pErrorCode
        buf2[r] = '\0';

        LD_ASSERT(err == U_ZERO_ERROR);

        return std::u16string(reinterpret_cast<const char16*>(buf2));
=======
    std::u16string utf32_to_utf16(const std::u32string_view sv)
    {
        return {};
>>>>>>> Stashed changes
    }
} // namespace ld