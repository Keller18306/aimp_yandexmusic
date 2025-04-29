#pragma once
#include <apiPlugin.h>
#include "helpers/IUnknownBridge.h"

class Plugin : public IUnknownBridge<IAIMPPlugin>
{
public:
	static IAIMPCore *getAIMPCore();

	PWCHAR WINAPI InfoGet(int index);
	DWORD WINAPI InfoGetCategories();
	HRESULT WINAPI Initialize(IAIMPCore* core);
	HRESULT WINAPI Finalize();
	void WINAPI SystemNotification(int NotifyID, IUnknown* Data) {}

private:
	static IAIMPCore* core_ptr;
};