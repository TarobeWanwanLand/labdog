//=========================================================
//
//  graphics.hpp is part of the labdog project.
//  Copyright(c) 2022 Tomomi murakami.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#ifndef LABDOG_GRAPHICS_HPP
#define LABDOG_GRAPHICS_HPP

#include "../core/common.hpp"
#include <vulkan/vulkan_core.h>

namespace ld
{
    class graphics final
    {
    public:
        graphics();
        ~graphics() = default;

    private:
        VkInstance instance_;
    };
} // namespace ld

#endif // LABDOG_GRAPHICS_HPP
