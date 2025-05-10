#include "GroupingTreeDataProviderSelection.h"
#include "../helpers/AIMPString.h"

LongWord WINAPI GroupingTreeDataProviderSelection::GetFlags()
{
    return AIMPML_GROUPINGTREENODE_FLAG_STANDALONE;
}

HRESULT WINAPI GroupingTreeDataProviderSelection::GetDisplayValue(IAIMPString **S)
{
    *S = AIMPString(L"Test-" + std::to_wstring(index));

    return S_OK;
}

HRESULT WINAPI GroupingTreeDataProviderSelection::GetImageIndex(int *Index)
{
    *Index = AIMPML_FIELDIMAGE_FOLDER;

    return S_OK;
}

HRESULT WINAPI GroupingTreeDataProviderSelection::GetValue(IAIMPString **FieldName, VARIANT *Value)
{
    *FieldName = AIMPString(_dataField);

    VariantInit(Value);
    Value->vt = VT_I4;
    Value->lVal = index;

    return S_OK;
}

BOOL WINAPI GroupingTreeDataProviderSelection::NextRow()
{
    return ++index < 3;
}