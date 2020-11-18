//======================================================================================================================
//  Functions needed in SvcMain, but useful for your own code too.
//======================================================================================================================

#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // just because of DWORD ffs


// Uncomment this if you want to debug why your service is not starting properly.
// That will make your code compile as a standard executable which you can run directly.
//#define DEBUGGING_PROCESS


extern SERVICE_STATUS_HANDLE g_svcStatusHandle;

void ReportSvcStatus( DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint );

void ReportSvcEvent( DWORD dwEventID, LPCTSTR szFormat, ... );
