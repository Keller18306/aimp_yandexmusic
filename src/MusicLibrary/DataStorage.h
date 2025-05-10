#pragma once
#include <aimp_sdk/apiMusicLibrary.h>
#include "../helpers/IUnknownBridge.h"
// #include "ymcppapi/ymapi.hpp"

enum class MusicLibraryCategory
{
    MyMusic,
    Test1,
    Test2
};

class DataStorage : public IUnknownBridge<IAIMPMLExtensionDataStorage, &IID_IAIMPMLExtensionDataStorage>, IAIMPMLDataProvider2
{
public:
    typedef IUnknownBridge<IAIMPMLExtensionDataStorage, &IID_IAIMPMLExtensionDataStorage> Base;

    static HRESULT RegisterExtension(IAIMPCore *core);

    void WINAPI
    Initialize(IAIMPMLDataStorageManager *Manager);
    void WINAPI Finalize();

    HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value);
    HRESULT WINAPI GetValueAsObject(int propertyID, REFIID IID, void **Value);
    HRESULT WINAPI GetFields(int Schema, IAIMPObjectList **List);
    HRESULT WINAPI GetGroupingPresets(int Schema, IAIMPMLGroupingPresets *Presets);

    HRESULT WINAPI GetData(IAIMPObjectList *Fields, IAIMPMLDataFilter *Filter, IUnknown *Reserved, /*in /out*/ IUnknown **PageID, IUnknown **Data);

    virtual void WINAPI FlushCache(int Reserved) {}

    virtual HRESULT WINAPI ConfigLoad(IAIMPConfig *Config, IAIMPString *Section) { return S_OK; }
    virtual HRESULT WINAPI ConfigSave(IAIMPConfig *Config, IAIMPString *Section) { return S_OK; }
    virtual void WINAPI BeginUpdate() {}
    virtual void WINAPI EndUpdate() {}
    virtual HRESULT WINAPI Reset() { return E_NOTIMPL; }
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double *Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64 *Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value) { return E_NOTIMPL; }
    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown *Value) { return E_NOTIMPL; }

    virtual ULONG WINAPI AddRef() { return Base::AddRef(); }
    virtual ULONG WINAPI Release() { return Base::Release(); }
    virtual HRESULT WINAPI QueryInterface(REFIID riid, void **ppvObject)
    {
        if (riid == IID_IAIMPMLDataProvider2)
        {
            *ppvObject = static_cast<IAIMPMLDataProvider2 *>(this);
            this->AddRef();

            return S_OK;
        }

        return Base::QueryInterface(riid, ppvObject);
    }

private:
    IAIMPMLDataField *_createDataField(const wchar_t *name, const int dataType, const int flags);
};

class DataProviderSelection : public IUnknownBridge<IAIMPMLDataProviderSelection, &IID_IAIMPMLDataProviderSelection>
{
    DOUBLE WINAPI GetValueAsFloat(int FieldIndex);
    int WINAPI GetValueAsInt32(int FieldIndex);
    INT64 WINAPI GetValueAsInt64(int FieldIndex);
    TChar *WINAPI GetValueAsString(int FieldIndex, int *Length);
    BOOL WINAPI NextRow();
};

class TestPage : public IUnknownBridgeBase
{
};