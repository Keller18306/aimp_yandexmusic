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
    printf("TEST!!!!!!!!!!!!!!!!!!");
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

HRESULT WINAPI DataStorage::GetFields(int Schema, IAIMPObjectList **List)
{
    Plugin::getAIMPCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void **>(List));

    switch (Schema)
    {
    case AIMPML_FIELDS_SCHEMA_ALL:
    {
        IAIMPMLDataField *prop = nullptr;
        Plugin::getAIMPCore()->CreateObject(IID_IAIMPMLDataField, reinterpret_cast<void **>(&prop));

        prop->SetValueAsObject(AIMPML_FIELD_PROPID_NAME, AIMPString(AIMPML_RESERVED_FIELD_ID));
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_TYPE, AIMPML_FIELDTYPE_STRING);
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_FLAGS, AIMPML_FIELDFLAG_FILTERING);

        (*List)->Add(prop);

        Plugin::getAIMPCore()->CreateObject(IID_IAIMPMLDataField, reinterpret_cast<void **>(&prop));

        prop->SetValueAsObject(AIMPML_FIELD_PROPID_NAME, AIMPString(AIMPML_RESERVED_FIELD_FILENAME));
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_TYPE, AIMPML_FIELDTYPE_STRING);
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_FLAGS, AIMPML_FIELDFLAG_FILTERING);

        (*List)->Add(prop);

        Plugin::getAIMPCore()->CreateObject(IID_IAIMPMLDataField, reinterpret_cast<void **>(&prop));

        prop->SetValueAsObject(AIMPML_FIELD_PROPID_NAME, AIMPString(L"Test Label"));
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_TYPE, AIMPML_FIELDTYPE_STRING);
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_FLAGS, AIMPML_FIELDFLAG_FILTERING);

        (*List)->Add(prop);

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
        Presets->Add(AIMPString(L"Test12312"), AIMPString(L"Test12312"), 0, new GroupingTreeDataProvider(), &Preset);
    }

    return S_OK;
}

HRESULT WINAPI DataStorage::GetData(IAIMPObjectList *Fields, IAIMPMLDataFilter *Filter, IUnknown *Reserved, /*in /out*/ IUnknown **PageID, IUnknown **Data)
{
    return S_OK;
}