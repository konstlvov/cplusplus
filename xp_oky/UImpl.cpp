//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop
#include "UImpl.h"
#include "USvcList.h"
#include "UEnvVarList.h"
#pragma package(smart_init)
#pragma comment (lib, "opends60.lib")//этот .lib - файл надо самостоятельно
//изготовить из библиотеки opends60.dll при помощи утилиты implib.exe

//ошибки
#define NO_ERRORS_OCCURED 0
#define WRONG_NUMBER_OF_PARAMETERS 1
#define ODS_FUNCTION_FAILED 2
#define WRONG_PARAMETER_TYPE 3
#define WRONG_PARAMETER_DIRECTION 4
#define OUTPUT_PARAMETER_LENGTH_NOT_ENOUGH 5

#define __CHECK_RET(sp,r)  if (FAIL == r) {\
  	SendODSError(sp);\
    return ODS_FUNCTION_FAILED;}

TCriticalSection CS;

int SendInfoMessage(SRV_PROC *sp, const char *format, ...)
{
	AnsiString s = "";
  va_list arg_ptr;
  va_start(arg_ptr, format);
  s.vprintf(format, arg_ptr);
  va_end(arg_ptr);
  int ret;
  ret = srv_sendmsg(
  	sp,
    SRV_MSG_INFO,
    0,//msgnum
    1,//severity
    1,//state
    0,//not supported
    0,//not supported
    0,//line number
    s.c_str(),
    SRV_NULLTERM);
  if (ret == FAIL)
  	OutputDebugString("srv_sendmsg возвратила FAIL");
  return ret;
}
int SendODSError(SRV_PROC *sp)
{
	return SendInfoMessage(sp,  "Внутрення ошибка ODS");
}

//типичная hello world процедура.
//возвратим в первом и единственном output-параметре символьную строку "Hello, World!"
SRVRETCODE xp_hello_impl(SRV_PROC *sp)
{
	const int param_number = 1;//порядковый номер параметра
	//количество параметров; если процедура была вызвана без параметров, вернет -1
	int num_params = srv_rpcparams(sp);
  if (num_params != 1)
  {
  	SendInfoMessage(sp, "Передано неверное количество параметров");
		return WRONG_NUMBER_OF_PARAMETERS;//мы ожидаем только один параметр
  }
  BYTE bType; //тип параметра
  ULONG cbMaxLen;// максимальная длина параметра
  ULONG cbActualLen;
  BYTE *pbData;//данные
  BOOL fNull; // is null?
  int ret;
  ret = srv_paraminfo(
  	sp,
    param_number,//номер параметра
    &bType,
    &cbMaxLen,
    &cbActualLen,
    NULL,//не писать в буфер, только получить информацию о типе, длине,
    		//максимальной длине и т.д.
    &fNull);
	if (ret != SUCCEED)
  {
  	OutputDebugString("Функция srv_paraminfo не возвратила SUCCEED");
    SendInfoMessage(sp, "Внутренняя ошибка ODS");
    return ODS_FUNCTION_FAILED;
  }
  if (bType != SRVBIGVARCHAR)
  {
  	SendInfoMessage(sp, "Передан параметр неверного типа данных, ожидается varchar");
    return WRONG_PARAMETER_TYPE;
  }
	int param_status = 0;
  param_status = srv_paramstatus(sp, param_number);
  if (!(param_status & 0x01) || param_status == -1) //это не output-параметр
  {
  	SendInfoMessage (sp, "Передан параметр с неправильным модификатором направления,"
    	" необходимо передавать параметр с модификатором OUTPUT");
  	return WRONG_PARAMETER_DIRECTION;
  }
  AnsiString out = "Hello, World!";
  if (out.Length() > cbMaxLen)
  {
  	SendInfoMessage(sp, "Длина выходного параметра недостаточна");
    return OUTPUT_PARAMETER_LENGTH_NOT_ENOUGH;
  }
	int set_status;
  set_status = srv_paramsetoutput(
  	sp,
    param_number,
		out.c_str(),
    out.Length(),
    FALSE);//not null
	if (set_status == FAIL)
  {
  	OutputDebugString("srv_paramsetoutput возвратила FAIL");
    SendInfoMessage(sp, "Внутренняя ошибка ODS");
    return ODS_FUNCTION_FAILED;
  }
  return NO_ERRORS_OCCURED;
}

SRVRETCODE xp_hello1_impl(SRV_PROC *sp)
{
	struct Record
  {
  	int id;
  	char *first_name;
		char *last_name;
  };
  Record records[] = {1001, "Иван", "Иванов",
  										1002, "Петр", "Петров"};
	//описываем первую колонку
  int ret;
  ret = srv_describe(
  	sp,
    NULL,//номер столбца, в настоящее время не поддерживается
    "ID",
    SRV_NULLTERM,
    SRVINT4,
    4,
    SRVINT4,
    4,
    NULL);
  if (ret == FAIL)
  {
  	SendInfoMessage(sp, "Внутренняя ошибка ODS");
    return ODS_FUNCTION_FAILED;
  }
  //описываем вторую колонку
  ret = srv_describe(
  	sp,
    NULL,
    "Имя",
    SRV_NULLTERM,
    SRVBIGVARCHAR,
    8000,
    SRVBIGVARCHAR,
    8000,
    NULL);
  if (ret == FAIL)
  {
  	SendInfoMessage(sp, "Внутренняя ошибка ODS");
    return ODS_FUNCTION_FAILED;
  }
  //описываем третью колонку
  ret = srv_describe(
  	sp,
    NULL,
    "Фамилия",
    SRV_NULLTERM,
    SRVBIGVARCHAR,
    8000,
    SRVBIGVARCHAR,
    8000,
    NULL);
  if (ret == FAIL)
  {
  	SendInfoMessage(sp, "Внутренняя ошибка ODS");
    return ODS_FUNCTION_FAILED;
  }
  for (int i = 0; i < sizeof records / sizeof records[0]; ++i)
  {
  	srv_setcollen(sp, 1, sizeof (int) );
    srv_setcoldata(sp, 1, &records[i].id);

    srv_setcollen(sp, 2, strlen(records[i].first_name));
    srv_setcoldata(sp, 2, records[i].first_name);

    srv_setcollen(sp, 3, strlen(records[i].last_name));
    srv_setcoldata(sp, 3, records[i].last_name);

    srv_sendrow(sp);
  }
  srv_senddone(sp, SRV_DONE_FINAL | SRV_DONE_COUNT, 0, 1);
  SendInfoMessage(sp, "Выполнение прошло без ошибок");
	return NO_ERRORS_OCCURED;
}


SRVRETCODE xp_svclist_impl(SRV_PROC *sp)
{
	using namespace std;
	int ret = 0;
	TSimpleLock lock(&CS.cs);
  AnsiString sname = "Имя сервиса";
  ret = srv_describe(sp, 1, sname.c_str(), SRV_NULLTERM, SRVBIGVARCHAR, 8000,
    SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)

  AnsiString sdesc = "Описание сервиса";
  ret = srv_describe(sp, 2, sdesc.c_str(), SRV_NULLTERM, SRVBIGVARCHAR, 8000,
    SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)

  AnsiString stype = "Тип сервиса";
  ret = srv_describe(sp, 3, stype.c_str(), SRV_NULLTERM,
  	SRVBIGVARCHAR, 8000, SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)

  AnsiString sstate = "Текущее состояние";
  ret = srv_describe(sp, 4, sstate.c_str(), SRV_NULLTERM,
  	SRVBIGVARCHAR, 8000, SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)

  AnsiString sca = "Допустимые операции управления";//service controls accepted
  ret = srv_describe(sp, 5, sca.c_str(), SRV_NULLTERM,
  	SRVBIGVARCHAR, 8000, SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)

  AnsiString pidh = "Идентификатор процесса";
  ret = srv_describe(sp, 6, pidh.c_str(), SRV_NULLTERM,
  	SRVINT4, sizeof (int), SRVINT4, sizeof(int), NULL);
  __CHECK_RET(sp, ret)

  AnsiString sfh = "Флаги сервиса";
  ret = srv_describe(sp, 7, sfh.c_str(), SRV_NULLTERM,
  	SRVBIGVARCHAR, 8000, SRVBIGVARCHAR, 8000, NULL);
	__CHECK_RET(sp, ret)

	CSvcList *l = CSvcList::GetInstance();
  l->Refresh();
  l->MoveFirst();
	while (! l->IsEof() )
  {
		string sn = l->GetServiceName();
  	srv_setcollen(sp, 1, sn.length() );
		srv_setcoldata(sp, 1, (void*)sn.c_str() );

    string dn = l->GetDisplayName();
    srv_setcollen(sp, 2, dn.length() );
    srv_setcoldata(sp, 2, (void*) dn.c_str() );

    string st = l->GetServiceType();
    srv_setcollen(sp, 3, st.length() );
    srv_setcoldata(sp, 3, (void*) st.c_str() );

    string ss = l->GetCurrentState();
    srv_setcollen(sp, 4, ss.length() );
    srv_setcoldata(sp, 4, (void*) ss.c_str() );

    string sca = l->GetControlsAccepted();
    srv_setcollen(sp, 5, sca.length() );
    srv_setcoldata(sp, 5, (void*) sca.c_str() );

		DWORD pid = 0;
    BOOL succ = l->GetProcessId(&pid);
    if (succ)
    {
    	srv_setcollen(sp, 6, sizeof (int));
      srv_setcoldata(sp, 6, &pid);
    }
    else //поставить значение NULL в случае ошибки
    {
    	srv_setcollen(sp, 6, 0);
      //srv_setcoldata вызывать не обязательно, если длина колонки была установлена в 0
    }

    string sf = l->GetServiceFlags();
    srv_setcollen(sp, 7, sf.length() );
    srv_setcoldata(sp, 7, (void*) sf.c_str() );

		srv_sendrow(sp);
    l->MoveNext();
  }
  srv_senddone(sp, SRV_DONE_FINAL | SRV_DONE_COUNT, 0, 0);
  //чтобы можно было выполнять DestroyInstance, надо реализовывать
  //потоковую безопасность (наверное, если ее не реализует сам SQL Server)
  //Реализовано через объект TSimpleLock
  CSvcList::DestroyInstance();
	return NO_ERRORS_OCCURED;
}


SRVRETCODE xp_envar_impl(SRV_PROC *sp)
{
	using namespace std;
	int ret = 0;
	TSimpleLock lock(&CS.cs);
  AnsiString var_name_h = "Переменная окружения";
  ret = srv_describe(sp, 1, var_name_h.c_str(), SRV_NULLTERM, SRVBIGVARCHAR, 8000,
    SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)
  AnsiString var_value_h = "Значение";
  ret = srv_describe(sp, 1, var_value_h.c_str(), SRV_NULLTERM, SRVBIGVARCHAR, 8000,
    SRVBIGVARCHAR, 8000, NULL);
  __CHECK_RET(sp, ret)
  CEnvVarList l;
  l.Refresh();

  int cnt = l.Count();
  for (int i = 0; i < cnt; ++i)
  {
 		string vn = l[i].var_name;
  	srv_setcollen(sp, 1, vn.length() );
		srv_setcoldata(sp, 1, (void*)vn.c_str() );

    string vv = l[i].var_value;
    srv_setcollen(sp, 2, vv.length() );
    srv_setcoldata(sp, 2, (void*)vv.c_str() );

    srv_sendrow(sp);
	}
	srv_senddone(sp, SRV_DONE_FINAL | SRV_DONE_COUNT, 0, 0);
	return NO_ERRORS_OCCURED;
}
