////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v5.40 build 2650
//
//  Purpose:   ThreadPool API
//
//  Author:    Artem Izmaylov
//             � 2006-2025
//             www.aimp.ru
//
#ifndef apiThreadingH
#define apiThreadingH

#include <unknwn.h>
#include "apiTypes.h"

static const GUID IID_IAIMPTask 		       = {0x41494D50, 0x5461, 0x736B, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPTaskOwner           = {0x41494D50, 0x5461, 0x736B, 0x4F, 0x77, 0x6E, 0x65, 0x72, 0x32, 0x00, 0x00};
static const GUID IID_IAIMPTaskPriority        = {0x41494D50, 0x5461, 0x736B, 0x50, 0x72, 0x69, 0x6F, 0x72, 0x69, 0x74, 0x79};
static const GUID IID_IAIMPServiceThreads      = {0x41494D50, 0x5372, 0x7654, 0x68, 0x72, 0x65, 0x61, 0x64, 0x73, 0x00, 0x00};

// Flags for IAIMPServiceThreads.Cancel and IAIMPServiceThreads.ExecuteInMainThread
const int AIMP_SERVICE_THREADS_FLAGS_WAITFOR = 0x1;

// IAIMPTaskPriority.GetPriority
const int AIMP_TASK_PRIORITY_NORMAL = 0;
const int AIMP_TASK_PRIORITY_LOW    = 1;
const int AIMP_TASK_PRIORITY_HIGH   = 2;

/* IAIMPTaskOwner */

class IAIMPTaskOwner: public IUnknown
{
	public:
		virtual BOOL WINAPI IsCanceled() = 0;
};

/* IAIMPTask */

class IAIMPTask: public IUnknown
{
	public:
		virtual void WINAPI Execute(IAIMPTaskOwner* Owner) = 0;
};

/* IAIMPTaskPriority */

class IAIMPTaskPriority: public IUnknown
{
	public:
		virtual int WINAPI GetPriority() = 0;
};

/* IAIMPServiceThreads */

class IAIMPServiceThreads: public IUnknown
{
	public:
		virtual HRESULT WINAPI ExecuteInMainThread(IAIMPTask* Task, LongWord Flags) = 0;
		virtual HRESULT WINAPI ExecuteInThread(IAIMPTask* Task, TTaskHandle *TaskHandle) = 0;
		virtual HRESULT WINAPI Cancel(TTaskHandle TaskHandle, LongWord Flags) = 0;
		virtual HRESULT WINAPI WaitFor(TTaskHandle TaskHandle) = 0;
};

#endif // !apiThreadingH
