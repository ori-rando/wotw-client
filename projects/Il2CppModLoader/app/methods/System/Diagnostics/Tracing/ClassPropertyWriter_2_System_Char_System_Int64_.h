#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Diagnostics::Tracing::ClassPropertyWriter_2_System_Char_System_Int64_ {
    IL2CPP_REGISTER_METHOD(0x02B36B60, void, ctor, (app::ClassPropertyWriter_2_System_Char_System_Int64_ * this_ptr, app::PropertyAnalysis * property))
    IL2CPP_REGISTER_METHOD(0x02B36D50, void, Write, (app::ClassPropertyWriter_2_System_Char_System_Int64_ * this_ptr, app::TraceLoggingDataCollector * collector, uint16_t * container))
    IL2CPP_REGISTER_METHOD(0x02B360C0, app::Object *, GetData, (app::ClassPropertyWriter_2_System_Char_System_Int64_ * this_ptr, uint16_t container))
}
