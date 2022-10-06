#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace Segment_1 {
        extern IL2CPP_MODLOADER_DLLEXPORT app::Segment_1__Class** type_info;
        inline app::Segment_1__Class* get_class() {
            return il2cpp::get_class<app::Segment_1__Class>(type_info, "", "Segment");
        }
        inline app::Segment_1* create() {
            return il2cpp::create_object<app::Segment_1>(get_class());
        }
        inline app::Segment_1__Array* create_array(int size) {
            return il2cpp::array_new<app::Segment_1__Array>(get_class(), size);
        }
        inline app::Segment_1__Array* create_array(const std::vector<app::Segment_1*>& items) {
            return il2cpp::array_new<app::Segment_1__Array>(get_class(), items);
        }
    } // namespace Segment_1
} // namespace app::classes::types
