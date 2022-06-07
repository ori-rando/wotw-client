#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Xml::Schema::FacetsChecker {
    IL2CPP_REGISTER_METHOD(0x02369B00, app::Exception *, CheckLexicalFacets, (app::FacetsChecker * this_ptr, app::String * * parse_string, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_1, (app::FacetsChecker * this_ptr, app::Object * value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_2, (app::FacetsChecker * this_ptr, app::Decimal value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_3, (app::FacetsChecker * this_ptr, int64_t value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_4, (app::FacetsChecker * this_ptr, int32_t value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_5, (app::FacetsChecker * this_ptr, int16_t value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_6, (app::FacetsChecker * this_ptr, app::DateTime value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_7, (app::FacetsChecker * this_ptr, double value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_8, (app::FacetsChecker * this_ptr, float value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_9, (app::FacetsChecker * this_ptr, app::String * value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_10, (app::FacetsChecker * this_ptr, app::Byte__Array * value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_11, (app::FacetsChecker * this_ptr, app::TimeSpan value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::Exception *, CheckValueFacets_12, (app::FacetsChecker * this_ptr, app::XmlQualifiedName * value, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x02369C20, void, CheckWhitespaceFacets, (app::FacetsChecker * this_ptr, app::String * * s, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x02369D30, app::Exception *, CheckPatternFacets, (app::FacetsChecker * this_ptr, app::RestrictionFacets * restriction, app::String * value))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, MatchEnumeration, (app::FacetsChecker * this_ptr, app::Object * value, app::ArrayList * enumeration, app::XmlSchemaDatatype * datatype))
    IL2CPP_REGISTER_METHOD(0x02369F60, app::RestrictionFacets *, ConstructRestriction, (app::FacetsChecker * this_ptr, app::DatatypeImplementation * datatype, app::XmlSchemaObjectCollection * facets, app::XmlNameTable * name_table))
    IL2CPP_REGISTER_METHODINFO(0x04766A70, FacetsChecker_ConstructRestriction__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0236A480, app::Decimal, Power, (int32_t x, int32_t y))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, ctor, (app::FacetsChecker * this_ptr))
}
