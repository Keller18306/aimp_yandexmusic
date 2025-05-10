#include "Plugin.h"
#include "OptionsDialog.h"
#include "MusicLibrary/DataStorage.h"
#include <stdexcept>

using namespace std;

IAIMPCore *Plugin::core_ptr = nullptr;
Config *Plugin::config = nullptr;

IAIMPCore *Plugin::getAIMPCore()
{
	if (!core_ptr)
	{
		throw runtime_error("Core not initialized");
	}

	return core_ptr;
}

PWCHAR Plugin::InfoGet(int index)
{
	switch (index)
	{
	case AIMP_PLUGIN_INFO_NAME:
		return const_cast<PWCHAR>(name);
	case AIMP_PLUGIN_INFO_AUTHOR:
		return const_cast<PWCHAR>(author);
	case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
		return const_cast<PWCHAR>(shortDesc);
	case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
		return const_cast<PWCHAR>(fullDesc);
	}

	return nullptr;
}

DWORD WINAPI Plugin::InfoGetCategories()
{
	return AIMP_PLUGIN_CATEGORY_ADDONS;
}

HRESULT WINAPI Plugin::Initialize(IAIMPCore *core)
{
	core_ptr = core;

	config = new Config(core);
	DataStorage::RegisterExtension(core);
	OptionsDialog::RegisterExtension(core);

	return S_OK;
}

HRESULT WINAPI Plugin::Finalize()
{
	return S_OK;
}

extern "C"
{
	HRESULT __declspec(dllexport) WINAPI AIMPPluginGetHeader(IAIMPPlugin **header)
	{
		*header = new Plugin();

		return S_OK;
	}
}