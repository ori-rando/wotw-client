#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace DynamicMetaObject {
        extern IL2CPP_MODLOADER_DLLEXPORT app::DynamicMetaObject__Class** type_info;
        inline app::DynamicMetaObject__Class* get_class() {
            return il2cpp::get_class<app::DynamicMetaObject__Class>(type_info, "System.Dynamic", "DynamicMetaObject");
        }
        inline app::DynamicMetaObject* create() {
            return il2cpp::create_object<app::DynamicMetaObject>(get_class());
        }
        inline app::DynamicMetaObject__Array* create_array(int size) {
            return il2cpp::array_new<app::DynamicMetaObject__Array>(get_class(), size);
        }
        inline app::DynamicMetaObject__Array* create_array(const std::vector<app::DynamicMetaObject*>& items) {
            return il2cpp::array_new<app::DynamicMetaObject__Array>(get_class(), items);
        }
    } // namespace DynamicMetaObject
} // namespace app::classes::types
