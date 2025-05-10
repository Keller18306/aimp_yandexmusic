#include "DataStorage.h"
#include "../helpers/AIMPString.h"
#include "../Plugin.h"
#include "GroupingTreeDataProvider.h"

HRESULT DataStorage::RegisterExtension(IAIMPCore *core)
{
    return core->RegisterExtension(IID_IAIMPServiceMusicLibrary, static_cast<IAIMPMLExtensionDataStorage *>(new DataStorage()));
}

void DataStorage::Initialize(IAIMPMLDataStorageManager *Manager)
{
    // printf("TEST!!!!!!!!!!!!!!!!!!");
}

void DataStorage::Finalize()
{
}

HRESULT WINAPI DataStorage::GetValueAsObject(int PropertyID, REFIID IID, void **Value)
{
    switch (PropertyID)
    {
    case AIMPML_DATASTORAGE_PROPID_ID:
        *Value = AIMPString(Plugin::id + std::wstring(L".DataStorage"));
        break;

    case AIMPML_DATASTORAGE_PROPID_CAPTION:
        *Value = AIMPString(L"TEST CAPTION");
        break;
    }

    return S_OK;
}

HRESULT WINAPI DataStorage::GetValueAsInt32(int PropertyID, int *Value)
{
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
    {
        Value = 0;
    }

    return S_OK;
}

IAIMPMLDataField *DataStorage::_createDataField(const wchar_t *name, const int dataType, const int flags)
{
    IAIMPMLDataField *prop = nullptr;

    Plugin::getAIMPCore()->CreateObject(IID_IAIMPMLDataField, reinterpret_cast<void **>(&prop));

    prop->SetValueAsObject(AIMPML_FIELD_PROPID_NAME, AIMPString(name));
    prop->SetValueAsInt32(AIMPML_FIELD_PROPID_TYPE, dataType);
    prop->SetValueAsInt32(AIMPML_FIELD_PROPID_FLAGS, flags);

    return prop;
}

HRESULT WINAPI DataStorage::GetFields(int Schema, IAIMPObjectList **List)
{
    Plugin::getAIMPCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void **>(List));

    switch (Schema)
    {
    case AIMPML_FIELDS_SCHEMA_ALL:
    {
        (*List)->Add(_createDataField(AIMPML_RESERVED_FIELD_ID, AIMPML_FIELDTYPE_STRING, AIMPML_FIELDFLAG_FILTERING));
        (*List)->Add(_createDataField(AIMPML_RESERVED_FIELD_FILENAME, AIMPML_FIELDTYPE_STRING, AIMPML_FIELDFLAG_FILTERING));
        (*List)->Add(_createDataField(L"Test Label", AIMPML_FIELDTYPE_STRING, AIMPML_FIELDFLAG_FILTERING));
        (*List)->Add(_createDataField(L"Internal", AIMPML_FIELDTYPE_STRING, AIMPML_FIELDFLAG_INTERNAL));

        break;
    }

    case AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT:
    case AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS:
    case AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS:
    {
        (*List)->Add(AIMPString(AIMPML_RESERVED_FIELD_ID));
        (*List)->Add(AIMPString(AIMPML_RESERVED_FIELD_FILENAME));
        (*List)->Add(AIMPString(L"Test Label"));
        break;
    }
    }

    return S_OK;
}

HRESULT WINAPI DataStorage::GetGroupingPresets(int Schema, IAIMPMLGroupingPresets *Presets)
{
    if (Schema == AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
    {
        IAIMPMLGroupingPreset *Preset = nullptr;
        Presets->Add(AIMPString(L"Test12312"), AIMPString(L"Test12312"), 0, new GroupingTreeDataProvider(L"Internal"), &Preset);
    }

    return S_OK;
}

HRESULT WINAPI DataStorage::GetData(IAIMPObjectList *Fields, IAIMPMLDataFilter *Filter, IUnknown *Reserved, /*in /out*/ IUnknown **PageID, IUnknown **Data)
{
    for (int i = 0; i < Fields->GetCount(); i++)
    {
        IAIMPString *aimpString = nullptr;
        Fields->GetObject(i, IID_IAIMPString, reinterpret_cast<void **>(&aimpString));
        wchar_t *str = aimpString->GetData();
    }

    if (*PageID == nullptr)
    {
        (*Data) = reinterpret_cast<IUnknown *>(new DataProviderSelection());
        // (*PageID) = reinterpret_cast<IUnknown *>(new TestPage());
    }

    return S_OK;
}

DOUBLE WINAPI DataProviderSelection::GetValueAsFloat(int FieldIndex)
{
    return 1.234;
}

int WINAPI DataProviderSelection::GetValueAsInt32(int FieldIndex)
{
    return 123;
}

INT64 WINAPI DataProviderSelection::GetValueAsInt64(int FieldIndex)
{
    return 321;
}

TChar *WINAPI DataProviderSelection::GetValueAsString(int FieldIndex, int *Length)
{
    std::wstring str;

    if (FieldIndex == 1)
    {
        str = std::wstring(L"vk://Audios/290331922_456239849_b3efb23759022da206.mp3");
    }
    else if (FieldIndex == 3)
    {
        str = std::wstring(L"Test-0");
    }
    else
    {
        str = std::wstring(L"test1");
    }

    *Length = str.length();

    wchar_t *result = new wchar_t[str.length()];
    wcscpy(result, str.c_str());

    return result;
}

BOOL WINAPI DataProviderSelection::NextRow()
{
    return false;
}