//=========================================================
//
//  application.cpp is part of the labdog project.
//  Copyright (C) 2022 TarobeWanwanLand.
//
//  Released under the MIT license.
//  see http://opensource.org/licenses/MIT
//
//=========================================================

#include "labdog/core/application.hpp"

namespace ld
{
    std::atomic<application*> application::instance_{ nullptr };
}