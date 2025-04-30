#pragma once
#include <aimp_sdk/apiMusicLibrary.h>
#include "../helpers/IUnknownBridge.h"

class GroupingTreeDataProvider : public IUnknownBridge<IAIMPMLGroupingTreeDataProvider, &IID_IAIMPMLGroupingTreeDataProvider>
{
public:
    HRESULT WINAPI AppendFilter(IAIMPMLDataFilterGroup *Filter, IAIMPMLGroupingTreeSelection *Selection);
    HRESULT WINAPI GetData(IAIMPMLGroupingTreeSelection *Selection, IAIMPMLGroupingTreeDataProviderSelection **Data);

    DWORD WINAPI GetCapabilities() { return AIMPML_GROUPINGTREEDATAPROVIDER_CAP_HIDEALLDATA; };
    HRESULT WINAPI GetFieldForAlphabeticIndex(IAIMPString **FieldName) { return E_NOTIMPL; }
};