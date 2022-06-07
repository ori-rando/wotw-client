#pragma once

#include <Il2CppModLoader/common.h>

#include <memory>

namespace game {
    namespace pickups {
        bool should_collect_pickup();
        std::unique_ptr<modloader::ScopedSetter<bool>> scoped_not_collecting_pickup();
    } // namespace pickups
} // namespace game
