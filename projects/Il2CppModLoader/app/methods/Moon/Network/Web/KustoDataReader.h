#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::Network::Web::KustoDataReader {
    IL2CPP_REGISTER_METHOD(0x002FA000, void, ctor_1, (app::KustoDataReader * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FBB10, void, ctor_2, (app::KustoDataReader * this_ptr, app::String * query))
    IL2CPP_REGISTER_METHOD(0x02E95C40, app::Byte__Array *, get_Data, (app::KustoDataReader * this_ptr))
}
