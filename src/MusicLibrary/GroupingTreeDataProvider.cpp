#include "GroupingTreeDataProvider.h"
#include "GroupingTreeDataProviderSelection.h"

HRESULT WINAPI GroupingTreeDataProvider::GetData(IAIMPMLGroupingTreeSelection *Selection, IAIMPMLGroupingTreeDataProviderSelection **Data)
{
    *Data = new GroupingTreeDataProviderSelection(_dataField);

    return S_OK;
}

HRESULT WINAPI GroupingTreeDataProvider::AppendFilter(IAIMPMLDataFilterGroup *Filter, IAIMPMLGroupingTreeSelection *Selection)
{
    // Filter->BeginUpdate();

    // Filter->SetValueAsInt32(AIMPML_FILTERGROUP_OPERATION, AIMPML_FILTERGROUP_OPERATION_AND);

    // int count = Selection->GetCount();

    // for (int i = 0; i < count; i++)
    // {
    //     IAIMPString *FieldName = nullptr;
    //     VARIANT Value;
    //     HRESULT status = Selection->GetValue(i, &FieldName, &Value);
    //     wchar_t *test = FieldName->GetData();

    //     if (SUCCEEDED(status))
    //     {
    //         // Filter.Add(AFieldName, AValue, Null, AIMPML_FIELDFILTER_OPERATION_EQUALS, AFilter);
    //         IAIMPMLDataFieldFilter *FieldFilter = nullptr;
    //         VARIANT Value2;

    //         VariantInit(&Value2);

    //         status = Filter->Add(FieldName, &Value, &Value2, AIMPML_FIELDFILTER_OPERATION_EQUALS, &FieldFilter);

    //         if (SUCCEEDED(status))
    //         {
    //             __debugbreak();
    //         }
    //     }
    // }

    // Filter->EndUpdate();

    return S_OK;
}