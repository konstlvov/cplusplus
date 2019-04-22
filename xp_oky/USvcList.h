//---------------------------------------------------------------------------

#ifndef USvcListH
#define USvcListH
//---------------------------------------------------------------------------
#include <windows.h>
#include <string>
#include "CommonAux.h"
using namespace std;


class CSvcList
{
private:
	static CSvcList *_instance;
  int _cp; //current position
	int _count; //���������� �������
	ENUM_SERVICE_STATUS_PROCESS *_entries;//�����, ���������� ���������� � ��������
  BOOL _IsEof, _IsBof;
  ENUM_SERVICE_STATUS_PROCESS* GetRawEntry();
  void AppSep(string &s, const string &value);// ApplySeparated: ��������� �������� � ������,
	//���� ����� �� �������, ���������� ��� �����������
public:
	static CSvcList* GetInstance();
  static void DestroyInstance();
	void Refresh();//������ ���������� ���������� �� ��������
  void MoveFirst();
  void MoveNext();
  bool IsEof();
  bool IsBof();
  string GetServiceName();
  string GetDisplayName();
  string GetServiceType();
  string GetCurrentState();
  string GetControlsAccepted();
  string GetWin32ExitCodeStr();
  BOOL GetWin32ExitCode(DWORD *pdwWin32ExitCode);
  BOOL GetServiceSpecificExitCode(DWORD *pdwServiceSpecificErrorCode);//��������� TRUE � ������ ������,
  //����� ��������� FALSE
  BOOL GetCheckPoint(DWORD *pdwCheckPoint);
  BOOL GetWaitHint(DWORD *pdwMillisecondsWaitHint);
  BOOL GetProcessId(DWORD *pdwProcessId);
  string GetServiceFlags();
protected:
	CSvcList();
  string GetErrorStatusString(); //���������� ���������� � ���, ������ �� �������
  //������� ������� � ������ � �������
};
#endif
