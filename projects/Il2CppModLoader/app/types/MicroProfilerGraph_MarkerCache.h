#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace MicroProfilerGraph_MarkerCache {
        extern IL2CPP_MODLOADER_DLLEXPORT app::MicroProfilerGraph_MarkerCache__Class** type_info;
        inline app::MicroProfilerGraph_MarkerCache__Class* get_class() {
            return il2cpp::get_nested_class<app::MicroProfilerGraph_MarkerCache__Class>(type_info, "", "MicroProfilerGraph", "MarkerCache");
        }
        inline app::MicroProfilerGraph_MarkerCache* create() {
            return il2cpp::create_object<app::MicroProfilerGraph_MarkerCache>(get_class());
        }
        inline app::MicroProfilerGraph_MarkerCache__Boxed* box(app::MicroProfilerGraph_MarkerCache value) {
            return il2cpp::box_value<app::MicroProfilerGraph_MarkerCache__Boxed>(get_class(), value);
        }
        inline app::MicroProfilerGraph_MarkerCache__Array* create_array(int size) {
            return il2cpp::array_new<app::MicroProfilerGraph_MarkerCache__Array>(get_class(), size);
        }
        inline app::MicroProfilerGraph_MarkerCache__Array* create_array(const std::vector<app::MicroProfilerGraph_MarkerCache__Boxed>& items) {
            return il2cpp::array_new<app::MicroProfilerGraph_MarkerCache__Array>(get_class(), items);
        }
    } // namespace MicroProfilerGraph_MarkerCache
} // namespace app::classes::types
