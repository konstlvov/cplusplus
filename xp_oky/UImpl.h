//---------------------------------------------------------------------------

#ifndef UImplH
#define UImplH
#include <srv.h>
#include <windows.h>

//---------------------------------------------------------------------------

SRVRETCODE xp_hello_impl(SRV_PROC *sp);
SRVRETCODE xp_hello1_impl(SRV_PROC *sp);
SRVRETCODE xp_svclist_impl(SRV_PROC *sp);
SRVRETCODE xp_envar_impl(SRV_PROC *sp);

struct TCriticalSection
{
	CRITICAL_SECTION cs;
  TCriticalSection() {InitializeCriticalSection(&cs);}
  ~TCriticalSection() {DeleteCriticalSection(&cs);}
};

struct TSimpleLock
{
        CRITICAL_SECTION *pcs;
        TSimpleLock(CRITICAL_SECTION* cs)
                :pcs(cs)
        {
                EnterCriticalSection(pcs);
        }
        virtual ~TSimpleLock()
        {
                LeaveCriticalSection(pcs);
        }
};

extern TCriticalSection CS;
#endif
