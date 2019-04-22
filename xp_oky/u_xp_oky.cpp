#include <vcl.h>
#include <windows.h>
#include <srv.h>
#pragma hdrstop

#include "UImpl.h"

//предопределенные значения
#define XP_OKY_VERSION 1

//декларации функций
extern "C" __declspec (dllexport) SRVRETCODE xp_hello(SRV_PROC *sp);
extern "C" __declspec (dllexport) ULONG __GetXpVersion();
extern "C" __declspec (dllexport) SRVRETCODE xp_hello1(SRV_PROC *sp);
extern "C" __declspec (dllexport) SRVRETCODE xp_svclist(SRV_PROC *sp);
extern "C" __declspec (dllexport) SRVRETCODE xp_envar(SRV_PROC *sp);

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}



ULONG __GetXpVersion()
{
	return ODS_VERSION;
}

SRVRETCODE xp_hello(SRV_PROC *sp)
{
	return xp_hello_impl(sp);
}


SRVRETCODE xp_hello1(SRV_PROC *sp)
{
	return xp_hello1_impl(sp);
}

SRVRETCODE xp_svclist(SRV_PROC *sp)
{
	return xp_svclist_impl(sp);
}

SRVRETCODE xp_envar(SRV_PROC *sp)
{
	return xp_envar_impl(sp);
}
