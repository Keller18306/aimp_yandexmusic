#pragma once
#include <aimp_sdk/apiPlugin.h>
#include "helpers/IUnknownBridge.h"

class Plugin : public IUnknownBridge<IAIMPPlugin>
{
public:
	static constexpr const WCHAR id[] = L"AIMP.YA_MUSIC";
	static constexpr const WCHAR name[] = L"Yandex Music";
	static constexpr const WCHAR author[] = L"Keller";
	static constexpr const WCHAR shortDesc[] = L"Short Description";
	static constexpr const WCHAR fullDesc[] = L"Full Description of the Plugin";

	static IAIMPCore *getAIMPCore();

	PWCHAR WINAPI InfoGet(int index);
	DWORD WINAPI InfoGetCategories();
	HRESULT WINAPI Initialize(IAIMPCore* core);
	HRESULT WINAPI Finalize();
	void WINAPI SystemNotification(int NotifyID, IUnknown* Data) {}

private:
	static IAIMPCore* core_ptr;
};