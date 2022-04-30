//=========================================================
//
//  graphics.cpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/graphics/graphics.hpp"
#include <vector>
#include <stdexcept>

namespace ld
{
    graphics::graphics()
    {
        const char* appName = "Hello,Vulkan";
        std::vector<const char*> extensions;

        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = appName;
        app_info.pEngineName = appName;
        app_info.apiVersion = VK_API_VERSION_1_3;
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);  // TODO: labdogのバージョンをマクロ定義する

        // レイヤー名
        const char* layers[] = { "VK_LAYER_LUNARG_standard_validation" };

        // レイヤーと検証レイヤーを有効化
        VkInstanceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.enabledLayerCount = 1;
        create_info.ppEnabledLayerNames = layers;
        create_info.enabledExtensionCount = static_cast<uint32>(extensions.size());
        create_info.ppEnabledExtensionNames = extensions.data();
        create_info.pApplicationInfo = &app_info;

        // インスタンスの作成
        if(vkCreateInstance(&create_info, nullptr, &instance_) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan instance.");
    }
} // namespace ld