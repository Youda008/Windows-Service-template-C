//======================================================================================================================
//  Add your own code here.
//======================================================================================================================

#include "MyService.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#include "SvcCommon.hpp"
#include "EventLogMessages.h"


const TCHAR * MY_SERVICE_NAME = _T("TemperatureService");

static HANDLE g_svcStopEvent = NULL;  // this event will be used to signal the main loop to exit


bool MyServiceInit()
{
	// Add your own init code here.
	// Be sure to periodically call ReportSvcStatus() with SERVICE_START_PENDING.

	// Create an event that will be used to signal an exit.
	g_svcStopEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	if (g_svcStopEvent == NULL)
	{
		ReportSvcEvent( SVCEVENT_CUSTOM_ERROR, _T("Failed to create stop event") );
		return false;
	}

	return true;
}

void MyServiceRun()
{
	// Add your main service processing code here.

	DWORD waitResult = 0;
	do
	{
		// Main processing loop

		// If the SvcCtrlHandler signals to stop the service, wake up and exit immediatelly.
		// If there is no signal, wait 1 second and repeat.
		waitResult = WaitForSingleObject( g_svcStopEvent, 1000 );
	}
	while (waitResult == WAIT_TIMEOUT);
}

void MyServiceStop()
{
	// Add your own signal to stop your service

	SetEvent( g_svcStopEvent );
}

void MyServiceCleanup()
{
	// Add your own cleanup code here.

	CloseHandle( g_svcStopEvent );
}
