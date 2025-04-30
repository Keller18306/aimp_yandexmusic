#pragma once
#include <aimp_sdk/apiMusicLibrary.h>
#include "../helpers/IUnknownBridge.h"

class GroupingTreeDataProviderSelection : public IUnknownBridge<IAIMPMLGroupingTreeDataProviderSelection, &IID_IAIMPMLGroupingTreeDataProviderSelection>
{
public:
    HRESULT WINAPI GetDisplayValue(IAIMPString **S);
    LongWord WINAPI GetFlags();
    HRESULT WINAPI GetImageIndex(int *Index);
    HRESULT WINAPI GetValue(IAIMPString **FieldName, VARIANT *Value);
    BOOL WINAPI NextRow();

private:
    unsigned int index = 0;
};