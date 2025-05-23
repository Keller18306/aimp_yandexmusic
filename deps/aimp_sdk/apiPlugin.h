////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v5.40 build 2650
//
//  Purpose:   Plugin Header API
//
//  Author:    Artem Izmaylov
//             � 2006-2025
//             www.aimp.ru
//
#ifndef apiPluginH
#define apiPluginH

#include <unknwn.h>
#include "apiCore.h"
#include "apiTypes.h"
 
// IAIMPPlugin.InfoGetCategories
const int  AIMP_PLUGIN_CATEGORY_ADDONS   = 1;
const int  AIMP_PLUGIN_CATEGORY_DECODERS = 2;
const int  AIMP_PLUGIN_CATEGORY_VISUALS  = 4;
const int  AIMP_PLUGIN_CATEGORY_DSP	     = 8;
const int  AIMP_PLUGIN_CATEGORY_ENCODER  = 16;

// IAIMPPlugin.InfoGet
const int  AIMP_PLUGIN_INFO_NAME              = 0x0;
const int  AIMP_PLUGIN_INFO_AUTHOR            = 0x1;
const int  AIMP_PLUGIN_INFO_SHORT_DESCRIPTION = 0x2;
const int  AIMP_PLUGIN_INFO_FULL_DESCRIPTION  = 0x3;
  
// IAIMPPlugin.SystemNotification
const int  AIMP_SYSTEM_NOTIFICATION_SERVICE_ADDED   = 0x1;
const int  AIMP_SYSTEM_NOTIFICATION_SERVICE_REMOVED = 0x2;
const int  AIMP_SYSTEM_NOTIFICATION_EXTENSION_REMOVED = 0x3;


static const GUID IID_IAIMPExternalSettingsDialog = {0x41494D50, 0x4578, 0x7472, 0x6E, 0x4F, 0x70, 0x74, 0x44, 0x6C, 0x67, 0x00};

/* IAIMPExternalSettingsDialog */
  
class IAIMPExternalSettingsDialog: public IUnknown
{
	public:
		virtual void WINAPI Show(HWND ParentWindow) = 0;
};
  
/* IAIMPPlugin */

class IAIMPPlugin: public IUnknown
{
	public:
		// Information about the plugin
		virtual TChar* WINAPI InfoGet(int Index) = 0;
		virtual LongWord WINAPI InfoGetCategories() = 0;
		// Initialization / Finalization
		virtual HRESULT WINAPI Initialize(IAIMPCore* Core) = 0;
		virtual HRESULT WINAPI Finalize() = 0;
		// System Notifications
		virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data) = 0;
};

// Export function name: AIMPPluginGetHeader
typedef HRESULT (WINAPI *TAIMPPluginGetHeaderProc)(IAIMPPlugin **Header);
#endif // !apiPluginH
