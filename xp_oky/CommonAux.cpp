#pragma hdrstop
#include "CommonAux.h"
#pragma package(smart_init)
namespace CommonAux
{
using namespace std;

string AuxSysErrorMessage(const DWORD ErrorCode)
{
	LPVOID buffer = 0;
	int Len = FormatMessage(
  	FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER
    | FORMAT_MESSAGE_IGNORE_INSERTS,
    0,
  	ErrorCode,
    0,
    (LPTSTR) &buffer,
    0,
    0);
  if (Len)
  {
		string s( (const char*) buffer);
    LocalFree(buffer);
  	return s;
  }
  else return string("");
}

}//namespace CommonAux

