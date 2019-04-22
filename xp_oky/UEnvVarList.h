#ifndef UEnvVarListH
#define UEnvVarListH
#include <windows.h>
#include <string>
#include <vector>
//����� ������������ � ���� ������� ������ STL,
//����� ���� �� ������������ ����� ���� ���������� ����� �������������
using namespace std;

struct ENV_VAR_INFO
{
  string var_name;
  string var_value;
};

class CEnvVarList
{
private:
  vector<ENV_VAR_INFO> _vars;
  BOOL ParseNameValue(const char* nvpair, string &name, string &value);
public:
	const ENV_VAR_INFO& operator[] (const int index) const;
	BOOL Refresh();
  int Count();
	CEnvVarList();
};
#endif
