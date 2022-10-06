#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace CommandBuffer {
        extern IL2CPP_MODLOADER_DLLEXPORT app::CommandBuffer__Class** type_info;
        inline app::CommandBuffer__Class* get_class() {
            return il2cpp::get_class<app::CommandBuffer__Class>(type_info, "UnityEngine.Rendering", "CommandBuffer");
        }
        inline app::CommandBuffer* create() {
            return il2cpp::create_object<app::CommandBuffer>(get_class());
        }
        inline app::CommandBuffer__Array* create_array(int size) {
            return il2cpp::array_new<app::CommandBuffer__Array>(get_class(), size);
        }
        inline app::CommandBuffer__Array* create_array(const std::vector<app::CommandBuffer*>& items) {
            return il2cpp::array_new<app::CommandBuffer__Array>(get_class(), items);
        }
    } // namespace CommandBuffer
} // namespace app::classes::types
