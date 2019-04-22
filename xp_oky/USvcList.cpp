//---------------------------------------------------------------------------

#include <windows.h>
#pragma hdrstop

#include "USvcList.h"
#include <stdlib.h>

using namespace CommonAux;

CSvcList* CSvcList::_instance = NULL;

CSvcList::CSvcList()
{
	_entries = 0; // так надо делать, потому что иначе есть шанс, что
  // _entries будет показывать на что угодно, но не будет NULL,
  // и тогда на него в ф-ции Refresh() сработает delete [],
  // и все сломается.
  _cp = 0;
  _count = 0;
  _IsEof = _IsBof = TRUE;
	Refresh();
}

CSvcList* CSvcList::GetInstance()
{
	if (! _instance) _instance = new CSvcList;
  return _instance;
}

void CSvcList::DestroyInstance()
{
	if (_instance)
  {
  	if (_instance->_entries)
    	delete [] _instance->_entries;
  	delete _instance;
  }
  _instance = NULL;
}

void CSvcList::Refresh()
{
  SC_HANDLE sm;
  DWORD err = 0;
  sm = OpenSCManager(
  	NULL,
    SERVICES_ACTIVE_DATABASE,
    SC_MANAGER_ALL_ACCESS);
	err = GetLastError();
  if (err)
  	OutputDebugString(AuxSysErrorMessage(err).c_str() );
  DWORD bytes_needed = 0;
  DWORD entries_returned = 0;
  DWORD resume_handle = 0;
  BOOL success = EnumServicesStatusEx(
  	sm,
    SC_ENUM_PROCESS_INFO,
    SERVICE_DRIVER | SERVICE_WIN32,
    SERVICE_STATE_ALL,
    0,//buffer
		0,//buf_size
		&bytes_needed,
    &entries_returned,
    &resume_handle,
    NULL);
	err = GetLastError();
  if (err)
  	OutputDebugString (AuxSysErrorMessage(err).c_str() );
  if (_entries)
  	delete [] _entries;
	_entries = (ENUM_SERVICE_STATUS_PROCESS*) new BYTE[bytes_needed];
  success = EnumServicesStatusEx(
  	sm,
    SC_ENUM_PROCESS_INFO,
    SERVICE_DRIVER | SERVICE_WIN32,
    SERVICE_STATE_ALL,
    (BYTE*) _entries,//buffer
		bytes_needed,//buf_size
		&bytes_needed,
    &entries_returned,
    &resume_handle,
    NULL);
  if (! success)
  {
		err = GetLastError();
  	if (err)
  		OutputDebugString (AuxSysErrorMessage(err).c_str() );
	}
  _count = entries_returned;
  MoveFirst();
}

void CSvcList::MoveFirst()
{
	_cp = 0;
  _IsBof = TRUE;
  if (_count == 0) _IsEof = TRUE;
  else _IsEof = FALSE;
}

void CSvcList::MoveNext()
{
	if (_cp < _count)  {_IsBof = FALSE;  ++ _cp;}
  if (_cp == _count || _count == 0) _IsEof = TRUE;
}

ENUM_SERVICE_STATUS_PROCESS* CSvcList::GetRawEntry()
{
	if (_count != 0 && !_IsEof)
  	return &_entries[_cp];
  else return NULL;
}
bool CSvcList::IsEof()
{
	return _IsEof;
}
bool CSvcList::IsBof()
{
	return _IsBof;
}
string CSvcList::GetServiceName()
{
	ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e) return e->lpServiceName;
  else return GetErrorStatusString();
}

string CSvcList::GetDisplayName()
{
	ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e) return e->lpDisplayName;
  else return GetErrorStatusString();
}

string CSvcList::GetErrorStatusString()
{
	if (_IsEof) return "SvcListError: EOF reached";
  if (_count == 0) return "SvcListError: no entries in buffer";
  return "SvcListError: Unknown error";
}

string CSvcList::GetServiceType()
{
	DWORD st = 0;//service type
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	st = e->ServiceStatusProcess.dwServiceType;
  	string s = "";
    if (st & SERVICE_FILE_SYSTEM_DRIVER)
			AppSep(s, "SERVICE_FILE_SYSTEM_DRIVER");
    if (st & SERVICE_KERNEL_DRIVER)
    	AppSep(s, "SERVICE_KERNEL_DRIVER");
    if (st & SERVICE_WIN32_OWN_PROCESS)
    	AppSep(s, "SERVICE_WIN32_OWN_PROCESS");
    if (st & SERVICE_WIN32_SHARE_PROCESS)
    	AppSep(s, "SERVICE_WIN32_SHARE_PROCESS");
    if (st & SERVICE_INTERACTIVE_PROCESS)
    	AppSep(s, "SERVICE_INTERACTIVE_PROCESS");
    return s;
  }
  else return GetErrorStatusString();
}

string CSvcList::GetCurrentState()
{
	DWORD cs = 0;//current state
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	cs = e->ServiceStatusProcess.dwCurrentState;
    string s = "";
    if (cs & SERVICE_STOPPED)
    	AppSep(s, "SERVICE_STOPPED");
    if (cs & SERVICE_START_PENDING)
    	AppSep(s, "SERVICE_START_PENDING");
    if (cs & SERVICE_STOP_PENDING)
    	AppSep(s, "SERVICE_STOP_PENDING");
    if (cs & SERVICE_RUNNING)
    	AppSep(s, "SERVICE_RUNNING");
    if (cs & SERVICE_CONTINUE_PENDING)
    	AppSep(s, "SERVICE_CONTINUE_PENDING");
    if (cs & SERVICE_PAUSE_PENDING)
    	AppSep(s, "SERVICE_PAUSE_PENDING");
    if (cs & SERVICE_PAUSED)
    	AppSep(s, "SERVICE_PAUSED");
    return s;
  }
  else return GetErrorStatusString();
}

string CSvcList::GetControlsAccepted()
{
	DWORD ca = 0;//controls accepted
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
    ca = e->ServiceStatusProcess.dwControlsAccepted;
    string s = "";
    if (ca & SERVICE_ACCEPT_NETBINDCHANGE)
    	AppSep(s, "SERVICE_ACCEPT_NETBINDCHANGE");
    if (ca & SERVICE_ACCEPT_PARAMCHANGE)
    	AppSep(s, "SERVICE_ACCEPT_PARAMCHANGE");
    if(ca & SERVICE_ACCEPT_PAUSE_CONTINUE)
    	AppSep(s, "SERVICE_ACCEPT_PAUSE_CONTINUE");
    if (ca & SERVICE_ACCEPT_SHUTDOWN)
    	AppSep(s, "SERVICE_ACCEPT_SHUTDOWN");
    if (ca & SERVICE_ACCEPT_STOP)
			AppSep(s, "SERVICE_ACCEPT_STOP");
    if (ca & SERVICE_ACCEPT_HARDWAREPROFILECHANGE)
    	AppSep(s, "SERVICE_ACCEPT_HARDWAREPROFILECHANGE");
    if (ca & SERVICE_ACCEPT_POWEREVENT)
    	AppSep(s, "SERVICE_ACCEPT_POWEREVENT");
    if (ca & SERVICE_ACCEPT_SESSIONCHANGE)
    	AppSep(s, "SERVICE_ACCEPT_SESSIONCHANGE");
    return s;
  }
  else return GetErrorStatusString();
}

string CSvcList::GetWin32ExitCodeStr()
{
	DWORD ec = 0;//exit code
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
    ec = e->ServiceStatusProcess.dwWin32ExitCode;
    string s = "";
    if (ec == ERROR_SERVICE_SPECIFIC_ERROR)
    	s = "ERROR_SERVICE_SPECIFIC_ERROR";
    else if (ec == NO_ERROR)
    	s = "NO_ERROR";
    else //неизвестное значение ec
    {
    	char buf[35];
      itoa(ec, buf, 16);
      s = buf;
      s = "0x" + s;
    }
    return s;
  }
  else return GetErrorStatusString();
}

BOOL CSvcList::GetServiceSpecificExitCode(DWORD *pdwServiceSpecificErrorCode)
{
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	if (e->ServiceStatusProcess.dwWin32ExitCode != ERROR_SERVICE_SPECIFIC_ERROR)
    	return FALSE;//значение dwServiceSpecificExitCode имеет смысл только если
      //dwWin32ExitCode равен ERROR_SERVICE_SPECIFIC_ERROR
    *pdwServiceSpecificErrorCode = e->ServiceStatusProcess.dwServiceSpecificExitCode;
    return TRUE;
  }
  else return FALSE;
}

BOOL CSvcList::GetWin32ExitCode(DWORD *pdwWin32ExitCode)
{
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
    *pdwWin32ExitCode = e->ServiceStatusProcess.dwWin32ExitCode;
    return TRUE;
  }
  else return FALSE;
}

BOOL CSvcList::GetCheckPoint(DWORD *pdwCheckPoint)
{
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	DWORD cs = e->ServiceStatusProcess.dwCurrentState;
    if (cs & SERVICE_START_PENDING
    		|| cs & SERVICE_STOP_PENDING
        || cs & SERVICE_CONTINUE_PENDING
        || cs & SERVICE_PAUSE_PENDING)
    {
    	*pdwCheckPoint = e->ServiceStatusProcess.dwCheckPoint;
      return TRUE;//значение CheckPoint имеет смысл только если сервис находится
      //в каком-либо из этих состояний
    }
    else return FALSE;
	}
  else return FALSE;
}

BOOL CSvcList::GetWaitHint(DWORD *pdwMillisecondsWaitHint)
{
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	*pdwMillisecondsWaitHint = e->ServiceStatusProcess.dwWaitHint;
    return TRUE;
  }
  else return FALSE;
}

BOOL CSvcList::GetProcessId(DWORD *pdwProcessId)
{
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	*pdwProcessId = e->ServiceStatusProcess.dwProcessId;
    return TRUE;
  }
  else return FALSE;
}

string CSvcList::GetServiceFlags()
{
  ENUM_SERVICE_STATUS_PROCESS *e = GetRawEntry();
  if (e)
  {
  	DWORD sf = e->ServiceStatusProcess.dwServiceFlags;
  	string s = "";
		if (sf & 0)
    	AppSep(s, "0");
    if (sf & SERVICE_RUNS_IN_SYSTEM_PROCESS)
    	AppSep(s, "SERVICE_RUNS_IN_SYSTEM_PROCESS");
    return s;
  }
  else return "Error getting ServiceFlags value";
}

void CSvcList::AppSep(string &s, const string &value)
{
	if (s.length() == 0) s = value;
  else
  {
  	s += " | ";
    s += value;
  }
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

