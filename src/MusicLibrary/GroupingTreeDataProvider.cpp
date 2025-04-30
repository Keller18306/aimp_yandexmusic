#include "GroupingTreeDataProvider.h"
#include "GroupingTreeDataProviderSelection.h"

HRESULT WINAPI GroupingTreeDataProvider::GetData(IAIMPMLGroupingTreeSelection *Selection, IAIMPMLGroupingTreeDataProviderSelection **Data)
{
    *Data = new GroupingTreeDataProviderSelection();

    return S_OK;
}

HRESULT WINAPI GroupingTreeDataProvider::AppendFilter(IAIMPMLDataFilterGroup *Filter, IAIMPMLGroupingTreeSelection *Selection)
{
    // int count = Selection->GetCount();

    // for (int i = 0; i < count; i++)
    // {
    //     IAIMPString **FieldName = nullptr;
    //     VARIANT *Value = nullptr;
    //     HRESULT status = Selection->GetValue(i, FieldName, Value);

    //     if (SUCCEEDED(status))
    //     {
    //         // Filter.Add(AFieldName, AValue, Null, AIMPML_FIELDFILTER_OPERATION_EQUALS, AFilter);
    //         IAIMPMLDataFieldFilter *FieldFilter = nullptr;
    //         status = Filter->Add(*FieldName, Value, nullptr, AIMPML_FIELDFILTER_OPERATION_EQUALS, &FieldFilter);
    //     }
    // }

    return S_OK;
}