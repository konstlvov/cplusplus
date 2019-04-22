#pragma hdrstop
#include "UEnvVarList.h"
#pragma package(smart_init)
#include <stdlib.h>

CEnvVarList::CEnvVarList()
{
	Refresh();
}


//nvpair - null-terminated string ������� MyVarName=MyVarValue
BOOL CEnvVarList::ParseNameValue(const char* nvpair, string &name, string &value)
{
	//��� ������� ����� ���� �����-�� ������� ����� � ���������� ������ =
  //����� ���
  if (*nvpair == '=')
  	while (*nvpair++ != '=');
	TCHAR buf[4096];
  int i = 0;
	while ( (buf[i++] = *nvpair++) != '='
  				&& sizeof (buf) / sizeof(TCHAR)  > i  );
  //�������� �����
  buf[i-1] = 0;
  name = buf;
  value = nvpair;
  if (name != "")  return TRUE;
  else return FALSE;
}

//����� ��������� ���������� � ���������� ���������
//��������� 0 ���� ������, 1 ��� ������ - ���� OK
BOOL CEnvVarList::Refresh()
{
	_vars.clear();
  ENV_VAR_INFO vi;
	char *pEnv = NULL;
  pEnv = (char*) GetEnvironmentStrings();
  char buf[4096];
  //������ ��� ��������, ��� ��� ������ �� null-terminated strings,
  //��������� ����� ������������� ����� ������
  char *spos = pEnv;
  if (pEnv)
  {
  	while ( *pEnv  ) // �� ����� �����
    {
    	while (*pEnv++); //����� ������
      lstrcpy(buf,spos);
      spos = pEnv;
      if (ParseNameValue(buf, vi.var_name, vi.var_value) == TRUE)
      	_vars.insert(_vars.end(), vi);
    }
    FreeEnvironmentStrings(pEnv);
		return TRUE;
  }
  else return FALSE;
}

int CEnvVarList::Count()
{
	return _vars.size();
}


const ENV_VAR_INFO& CEnvVarList::operator[] (const int index) const
{
	//������� exception, ���� index ������ ������� �������,
  //�� � ������.
	return _vars.at(index);
}

