#pragma once

#include "aimp_sdk/apiCore.h"

template <typename T, const IID *InterfaceIID = nullptr>
class IUnknownBridge : public T, public IUnknown
{
public:
	IUnknownBridge() : refCount(1) {}

	HRESULT WINAPI QueryInterface(REFIID riid, void **ppvObj) override
	{
		if (!ppvObj)
			return E_INVALIDARG;

		*ppvObj = nullptr;

		if (IsEqualIID(riid, IID_IUnknown) || (InterfaceIID && IsEqualIID(riid, *InterfaceIID)))
		{
			*ppvObj = (LPVOID)this;
			AddRef();

			return NOERROR;
		}

		return E_NOINTERFACE;
	}

	ULONG WINAPI AddRef() override
	{
		return InterlockedIncrement(&refCount);
	}

	ULONG WINAPI Release() override
	{
		ULONG ulRefCount = InterlockedDecrement(&refCount);

		if (ulRefCount == 0)
		{
			delete this;
		}

		return ulRefCount;
	}

private:
	ULONG refCount;
};

class IUnknownBridgeBase : public virtual IUnknown
{
public:
	IUnknownBridgeBase() : refCount(1) {}

	HRESULT WINAPI QueryInterface(REFIID riid, void **ppvObj) override
	{
		if (!ppvObj)
			return E_INVALIDARG;

		*ppvObj = nullptr;

		// Проверка только на IUnknown — в базовой версии
		if (IsEqualIID(riid, IID_IUnknown))
		{
			*ppvObj = (LPVOID)this;
			AddRef();
			return NOERROR;
		}

		return E_NOINTERFACE;
	}

	ULONG WINAPI AddRef() override
	{
		return InterlockedIncrement(&refCount);
	}

	ULONG WINAPI Release() override
	{
		ULONG ulRefCount = InterlockedDecrement(&refCount);

		if (ulRefCount == 0)
		{
			delete this;
		}

		return ulRefCount;
	}

private:
	ULONG refCount;
};