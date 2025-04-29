#include "Plugin.h"

using namespace std;

IAIMPCore* Plugin::core_ptr = nullptr;

PWCHAR Plugin::InfoGet(int index) {
	static WCHAR name[] = L"Yandex Music";
	static WCHAR author[] = L"Keller";
	static WCHAR shortDesc[] = L"Short Description";
	static WCHAR fullDesc[] = L"Full Description of the Plugin";

	switch (index)
	{
	case AIMP_PLUGIN_INFO_NAME:
		return name;
	case AIMP_PLUGIN_INFO_AUTHOR:
		return author;
	case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
		return shortDesc;
	case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
		return fullDesc;
	}

	return nullptr;
}

DWORD WINAPI Plugin::InfoGetCategories() {
	return AIMP_PLUGIN_CATEGORY_ADDONS;
}

HRESULT WINAPI Plugin::Initialize(IAIMPCore* core) {
	return S_OK;
}

HRESULT WINAPI Plugin::Finalize() {
	return S_OK;
}

extern "C" {
	HRESULT __declspec(dllexport) WINAPI AIMPPluginGetHeader(IAIMPPlugin** header) {
		*header = new Plugin();

		return S_OK;
	}
}