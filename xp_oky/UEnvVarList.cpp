#pragma hdrstop
#include "UEnvVarList.h"
#pragma package(smart_init)
#include <stdlib.h>

CEnvVarList::CEnvVarList()
{
	Refresh();
}


//nvpair - null-terminated string формата MyVarName=MyVarValue
BOOL CEnvVarList::ParseNameValue(const char* nvpair, string &name, string &value)
{
	//там вначале блока идут какие-то сетевые диски с лидирующим знаком =
  //уберу его
  if (*nvpair == '=')
  	while (*nvpair++ != '=');
	TCHAR buf[4096];
  int i = 0;
	while ( (buf[i++] = *nvpair++) != '='
  				&& sizeof (buf) / sizeof(TCHAR)  > i  );
  //завершим нулем
  buf[i-1] = 0;
  name = buf;
  value = nvpair;
  if (name != "")  return TRUE;
  else return FALSE;
}

//метод обновляет информацию о переменных окружения
//возвратит 0 если ошибка, 1 или больше - если OK
BOOL CEnvVarList::Refresh()
{
	_vars.clear();
  ENV_VAR_INFO vi;
	char *pEnv = NULL;
  pEnv = (char*) GetEnvironmentStrings();
  char buf[4096];
  //примем для простоты, что это массив из null-terminated strings,
  //последняя стока заканчивается двумя нулями
  char *spos = pEnv;
  if (pEnv)
  {
  	while ( *pEnv  ) // не конец блока
    {
    	while (*pEnv++); //конец строки
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
	//выкинет exception, если index больше размера вектора,
  //ну и пускай.
	return _vars.at(index);
}

