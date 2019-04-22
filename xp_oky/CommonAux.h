//---------------------------------------------------------------------------

#ifndef CommonAuxH
#define CommonAuxH
#include <string>
#include <windows.h>
//---------------------------------------------------------------------------
namespace CommonAux
{
	using namespace std;
  string AuxSysErrorMessage(const DWORD ErrorCode);
};
#endif
