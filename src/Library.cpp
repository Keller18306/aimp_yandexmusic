#include "Library.h"
#include "helpers/AIMPString.h"
#include "Plugin.h"

HRESULT Library::RegisterExtension(IAIMPCore *core)
{
    return core->RegisterExtension(IID_IAIMPServiceMusicLibrary, static_cast<IAIMPMLExtensionDataStorage *>(new Library()));
}

void Library::Initialize(IAIMPMLDataStorageManager *Manager)
{
    printf("TEST!!!!!!!!!!!!!!!!!!");
}

void Library::Finalize()
{
}

HRESULT WINAPI Library::GetValueAsObject(int PropertyID, REFIID IID, void **Value)
{
    switch (PropertyID)
    {
    case AIMPML_DATASTORAGE_PROPID_ID:
        *Value = AIMPString(L"testPluginId");
        break;

    case AIMPML_DATASTORAGE_PROPID_CAPTION:
        *Value = AIMPString(L"TEST CAPTION");
        break;
    }

    return S_OK;
}

HRESULT WINAPI Library::GetValueAsInt32(int PropertyID, int *Value)
{
    if (PropertyID == AIMPML_DATASTORAGE_PROPID_CAPABILITIES)
    {
        Value = 0;
    }

    return S_OK;
}

HRESULT WINAPI Library::GetFields(int Schema, IAIMPObjectList **List)
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

        prop->SetValueAsObject(AIMPML_FIELD_PROPID_NAME, AIMPString(AIMPML_RESERVED_FIELD_FILENAME));
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_TYPE, AIMPML_FIELDTYPE_STRING);
        prop->SetValueAsInt32(AIMPML_FIELD_PROPID_FLAGS, AIMPML_FIELDFLAG_FILTERING);

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

HRESULT WINAPI Library::GetGroupingPresets(int Schema, IAIMPMLGroupingPresets *Presets)
{
    if (Schema == AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
    {
        IAIMPMLGroupingPreset *Preset = nullptr;
        Presets->Add(AIMPString(L"Test12312"), nullptr, 0, new GroupingTreeDataProvider(), &Preset);
    }

    return S_OK;
}

HRESULT WINAPI Library::GetData(IAIMPObjectList *Fields, IAIMPMLDataFilter *Filter, IUnknown *Reserved, /*in /out*/ IUnknown **PageID, IUnknown **Data)
{
    return S_OK;
}

HRESULT WINAPI GroupingTreeDataProvider::AppendFilter(IAIMPMLDataFilterGroup *Filter, IAIMPMLGroupingTreeSelection *Selection)
{
    return S_OK;
}

HRESULT WINAPI GroupingTreeDataProvider::GetData(IAIMPMLGroupingTreeSelection *Selection, IAIMPMLGroupingTreeDataProviderSelection **Data)
{
    return S_OK;
}