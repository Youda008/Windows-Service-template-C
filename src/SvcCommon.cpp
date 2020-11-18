//======================================================================================================================
//  Functions needed in SvcMain, but useful for your own code too.
//======================================================================================================================

#include "SvcCommon.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "MyService.hpp" // only because of service name


SERVICE_STATUS_HANDLE g_svcStatusHandle;


void ReportSvcStatus( DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint )
{
#ifndef DEBUGGING_PROCESS
	static DWORD dwCheckPoint = 1;

	SERVICE_STATUS g_svcStatus;

	g_svcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	g_svcStatus.dwServiceSpecificExitCode = 0;

	g_svcStatus.dwCurrentState = dwCurrentState;
	g_svcStatus.dwWin32ExitCode = dwWin32ExitCode;
	g_svcStatus.dwWaitHint = dwWaitHint;

	if (dwCurrentState == SERVICE_START_PENDING)
		g_svcStatus.dwControlsAccepted = 0;
	else
		g_svcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	if (dwCurrentState == SERVICE_RUNNING || dwCurrentState == SERVICE_STOPPED)
		g_svcStatus.dwCheckPoint = 0;
	else
		g_svcStatus.dwCheckPoint = dwCheckPoint++;

	// Report the status of the service to the SCM
	SetServiceStatus( g_svcStatusHandle, &g_svcStatus );
#endif
}

void ReportSvcEvent( DWORD dwEventID, LPCTSTR szFormat, ... )
{
	va_list argList;
	va_start( argList, szFormat );

#ifndef DEBUGGING_PROCESS

	HANDLE hEventSource = RegisterEventSource( NULL, MY_SERVICE_NAME );

	if (hEventSource != NULL)
	{
		TCHAR buffer [80];
		_vsntprintf( buffer, 79, szFormat, argList );

		LPCTSTR lpszStrings [2] = { MY_SERVICE_NAME, buffer };

		ReportEvent(
			hEventSource,        // event log handle
			EVENTLOG_ERROR_TYPE, // event type
			0,                   // event category
			dwEventID,           // event identifier
			NULL,                // no security identifier
			2,                   // size of lpszStrings array
			0,                   // no binary data
			lpszStrings,         // array of strings
			NULL                 // no binary data
		);

		DeregisterEventSource(hEventSource);
	}

#else

	_vtprintf( szFormat, argList );
	_tprintf( _T("\n") );

#endif

	va_end( argList );
}
