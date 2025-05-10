#pragma once
#include <aimp_sdk/apiMusicLibrary.h>
#include "../helpers/IUnknownBridge.h"

class GroupingTreeDataProvider : public IUnknownBridge<IAIMPMLGroupingTreeDataProvider, &IID_IAIMPMLGroupingTreeDataProvider>
{
public:
    GroupingTreeDataProvider(const wchar_t *dataField) : _dataField(dataField) {};

    HRESULT WINAPI AppendFilter(IAIMPMLDataFilterGroup *Filter, IAIMPMLGroupingTreeSelection *Selection);
    HRESULT WINAPI GetData(IAIMPMLGroupingTreeSelection *Selection, IAIMPMLGroupingTreeDataProviderSelection **Data);

    DWORD WINAPI GetCapabilities() { return AIMPML_GROUPINGTREEDATAPROVIDER_CAP_HIDEALLDATA; };
    HRESULT WINAPI GetFieldForAlphabeticIndex(IAIMPString **FieldName) { return E_NOTIMPL; }

private:
    const wchar_t *_dataField;
};