#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace IEntityBehaviour {
        extern IL2CPP_MODLOADER_DLLEXPORT app::IEntityBehaviour__Class** type_info;
        inline app::IEntityBehaviour__Class* get_class() {
            return il2cpp::get_class<app::IEntityBehaviour__Class>(type_info, "Moon", "IEntityBehaviour");
        }
        inline app::IEntityBehaviour__Array* create_array(int size) {
            return il2cpp::array_new<app::IEntityBehaviour__Array>(get_class(), size);
        }
        inline app::IEntityBehaviour__Array* create_array(const std::vector<app::IEntityBehaviour*>& items) {
            return il2cpp::array_new<app::IEntityBehaviour__Array>(get_class(), items);
        }
    } // namespace IEntityBehaviour
} // namespace app::classes::types
