#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Xml::XmlTextWriter {
    IL2CPP_REGISTER_METHOD(0x01FBCAE0, void, ctor_1, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBCC40, void, ctor_2, (app::XmlTextWriter * this_ptr, app::Stream * w, app::Encoding * encoding))
    IL2CPP_REGISTER_METHOD(0x01FBCF70, void, ctor_3, (app::XmlTextWriter * this_ptr, app::String * filename, app::Encoding * encoding))
    IL2CPP_REGISTER_METHOD(0x01FBD100, void, ctor_4, (app::XmlTextWriter * this_ptr, app::TextWriter * w))
    IL2CPP_REGISTER_METHOD(0x01FBD2A0, app::Stream *, get_BaseStream, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBD380, void, set_Namespaces, (app::XmlTextWriter * this_ptr, bool value))
    IL2CPP_REGISTER_METHODINFO(0x0472DDB0, XmlTextWriter_set_Namespaces__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBD450, void, set_Formatting, (app::XmlTextWriter * this_ptr, app::Formatting__Enum value))
    IL2CPP_REGISTER_METHOD(0x01FBD460, void, set_QuoteChar, (app::XmlTextWriter * this_ptr, uint16_t value))
    IL2CPP_REGISTER_METHODINFO(0x0476EBD8, XmlTextWriter_set_QuoteChar__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBD540, void, WriteStartDocument_1, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBD550, void, WriteStartDocument_2, (app::XmlTextWriter * this_ptr, bool standalone))
    IL2CPP_REGISTER_METHOD(0x01FBD570, void, WriteEndDocument, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0476C150, XmlTextWriter_WriteEndDocument__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBD730, void, WriteDocType, (app::XmlTextWriter * this_ptr, app::String * name, app::String * pubid, app::String * sysid, app::String * subset))
    IL2CPP_REGISTER_METHODINFO(0x04774E38, XmlTextWriter_WriteDocType__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBDAB0, void, WriteStartElement, (app::XmlTextWriter * this_ptr, app::String * prefix, app::String * local_name, app::String * ns))
    IL2CPP_REGISTER_METHODINFO(0x04709A28, XmlTextWriter_WriteStartElement__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBE080, void, WriteEndElement, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBE090, void, WriteFullEndElement, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBE0A0, void, WriteStartAttribute, (app::XmlTextWriter * this_ptr, app::String * prefix, app::String * local_name, app::String * ns))
    IL2CPP_REGISTER_METHODINFO(0x04766BC0, XmlTextWriter_WriteStartAttribute__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBE870, void, WriteEndAttribute, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0475F2C8, XmlTextWriter_WriteEndAttribute__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBE930, void, WriteCData, (app::XmlTextWriter * this_ptr, app::String * text))
    IL2CPP_REGISTER_METHODINFO(0x0471DCB8, XmlTextWriter_WriteCData__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBEAE0, void, WriteComment, (app::XmlTextWriter * this_ptr, app::String * text))
    IL2CPP_REGISTER_METHODINFO(0x04718CB8, XmlTextWriter_WriteComment__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBECB0, void, WriteProcessingInstruction, (app::XmlTextWriter * this_ptr, app::String * name, app::String * text))
    IL2CPP_REGISTER_METHODINFO(0x04777D88, XmlTextWriter_WriteProcessingInstruction__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBEF50, void, WriteEntityRef, (app::XmlTextWriter * this_ptr, app::String * name))
    IL2CPP_REGISTER_METHODINFO(0x04718B20, XmlTextWriter_WriteEntityRef__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF0A0, void, WriteCharEntity, (app::XmlTextWriter * this_ptr, uint16_t ch))
    IL2CPP_REGISTER_METHODINFO(0x047188E0, XmlTextWriter_WriteCharEntity__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF2B0, void, WriteWhitespace, (app::XmlTextWriter * this_ptr, app::String * ws))
    IL2CPP_REGISTER_METHODINFO(0x047219A0, XmlTextWriter_WriteWhitespace__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF400, void, WriteString, (app::XmlTextWriter * this_ptr, app::String * text))
    IL2CPP_REGISTER_METHODINFO(0x04721CE8, XmlTextWriter_WriteString__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF4F0, void, WriteSurrogateCharEntity, (app::XmlTextWriter * this_ptr, uint16_t low_char, uint16_t high_char))
    IL2CPP_REGISTER_METHODINFO(0x04764D58, XmlTextWriter_WriteSurrogateCharEntity__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF5E0, void, WriteChars, (app::XmlTextWriter * this_ptr, app::Char__Array * buffer, int32_t index, int32_t count))
    IL2CPP_REGISTER_METHODINFO(0x04767F68, XmlTextWriter_WriteChars__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF6E0, void, WriteRaw_1, (app::XmlTextWriter * this_ptr, app::Char__Array * buffer, int32_t index, int32_t count))
    IL2CPP_REGISTER_METHODINFO(0x0478D960, XmlTextWriter_WriteRaw__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF7E0, void, WriteRaw_2, (app::XmlTextWriter * this_ptr, app::String * data))
    IL2CPP_REGISTER_METHODINFO(0x047941A8, XmlTextWriter_WriteRaw_1__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBF8C0, void, WriteBase64, (app::XmlTextWriter * this_ptr, app::Byte__Array * buffer, int32_t index, int32_t count))
    IL2CPP_REGISTER_METHODINFO(0x0476B390, XmlTextWriter_WriteBase64__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBFAD0, void, WriteBinHex, (app::XmlTextWriter * this_ptr, app::Byte__Array * buffer, int32_t index, int32_t count))
    IL2CPP_REGISTER_METHODINFO(0x04791EB8, XmlTextWriter_WriteBinHex__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBFBD0, app::WriteState__Enum, get_WriteState, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBFC40, void, Close, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01F3EE40, void, Flush, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FBFDC0, app::String *, LookupPrefix, (app::XmlTextWriter * this_ptr, app::String * ns))
    IL2CPP_REGISTER_METHODINFO(0x0477F6A8, XmlTextWriter_LookupPrefix__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FBFF20, void, StartDocument, (app::XmlTextWriter * this_ptr, int32_t standalone))
    IL2CPP_REGISTER_METHODINFO(0x047589B8, XmlTextWriter_StartDocument__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC0270, void, AutoComplete, (app::XmlTextWriter * this_ptr, app::XmlTextWriter_Token__Enum token))
    IL2CPP_REGISTER_METHODINFO(0x04763150, XmlTextWriter_AutoComplete__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC08B0, void, AutoCompleteAll, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FC0900, void, InternalWriteEndElement, (app::XmlTextWriter * this_ptr, bool long_format))
    IL2CPP_REGISTER_METHODINFO(0x0473BA50, XmlTextWriter_InternalWriteEndElement__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC0D20, void, WriteEndStartTag, (app::XmlTextWriter * this_ptr, bool empty))
    IL2CPP_REGISTER_METHOD(0x01FC1340, void, WriteEndAttributeQuote, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FC13C0, void, Indent, (app::XmlTextWriter * this_ptr, bool before_end_element))
    IL2CPP_REGISTER_METHOD(0x01FC14C0, void, PushNamespace, (app::XmlTextWriter * this_ptr, app::String * prefix, app::String * ns, bool declared))
    IL2CPP_REGISTER_METHODINFO(0x04725290, XmlTextWriter_PushNamespace__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC1860, void, AddNamespace, (app::XmlTextWriter * this_ptr, app::String * prefix, app::String * ns, bool declared))
    IL2CPP_REGISTER_METHOD(0x01FC1BD0, void, AddToNamespaceHashtable, (app::XmlTextWriter * this_ptr, int32_t namespace_index))
    IL2CPP_REGISTER_METHOD(0x01FC1DA0, void, PopNamespaces, (app::XmlTextWriter * this_ptr, int32_t index_from, int32_t index_to))
    IL2CPP_REGISTER_METHOD(0x01FC1ED0, app::String *, GeneratePrefix, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FC2030, void, InternalWriteProcessingInstruction, (app::XmlTextWriter * this_ptr, app::String * name, app::String * text))
    IL2CPP_REGISTER_METHOD(0x01FC2180, int32_t, LookupNamespace, (app::XmlTextWriter * this_ptr, app::String * prefix))
    IL2CPP_REGISTER_METHOD(0x01FC2310, int32_t, LookupNamespaceInCurrentScope, (app::XmlTextWriter * this_ptr, app::String * prefix))
    IL2CPP_REGISTER_METHOD(0x01FC2540, app::String *, FindPrefix, (app::XmlTextWriter * this_ptr, app::String * ns))
    IL2CPP_REGISTER_METHOD(0x01FC2680, void, ValidateName, (app::XmlTextWriter * this_ptr, app::String * name, bool is_n_c_name))
    IL2CPP_REGISTER_METHODINFO(0x0471A050, XmlTextWriter_ValidateName__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC2940, void, HandleSpecialAttribute, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0478BB20, XmlTextWriter_HandleSpecialAttribute__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC2CA0, void, VerifyPrefixXml, (app::XmlTextWriter * this_ptr, app::String * prefix, app::String * ns))
    IL2CPP_REGISTER_METHODINFO(0x047635A0, XmlTextWriter_VerifyPrefixXml__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01FC2E20, void, PushStack, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FC2F40, void, FlushEncoders, (app::XmlTextWriter * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01FC2F70, void, cctor, ())
}
