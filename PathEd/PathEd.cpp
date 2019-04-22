//---------------------------------------------------------------------------
#include "stdafx.h"
#include "resource.h"


//---------------------------------------------------------------------------


HWND g_hMain = 0;
HWND g_hListBox = 0;
HWND g_hEdit = 0;
HWND g_hCombo = 0;

WNDPROC g_pOldEditWndProc = 0;
WNDPROC g_pOldListWndProc = 0;
WNDPROC g_pOldComboWndProc = 0;



TCHAR STR_USER[100];
TCHAR STR_SYSTEM[100];
TCHAR STR_MACHINE_ENV_SUBKEY[256];
TCHAR STR_USER_ENV_SUBKEY[256];
TCHAR STR_ABOUT_HELP[4096];
TCHAR STR_ABOUTBOX_CAPTION[100];
TCHAR STR_ERRORBOX_CAPTION[100];
TCHAR STR_INSERT_HINT[200];
TCHAR STR_ERROR_OPEN_KEY[400];
TCHAR STR_ERROR_READING_LINE_FROM_LIST[400];
TCHAR STR_ERROR_WRITE_VALUE_TO_REGISTRY[400];
TCHAR STR_ERROR_CREATE_MAINWND[400];
TCHAR STR_ERROR_QUERY_VALUE_FROM_REGISTRY[400];
TCHAR STR_QUERY_UPDATE_VARIABLE[200];

struct CurrentListState
{
	TCHAR EnvVarName[256];
	BOOL m_bModified; // флаг ставится, когда произошла модификация переменной
  CurrentListState()
  {
  	EnvVarName[0] = '\0';
  	m_bModified = FALSE;
  }
} g_Cls;


void LoadResources(HINSTANCE h);
void AddListBoxItem(LPCTSTR text);
void ListBoxSelChange();
void EditBoxEnterPressed();
void MoveSelectionUp();
void MoveSelectionDown();
void SetEditText(LPCTSTR text);
void ClearListBox();
void ShowErrorMessage(LPCTSTR text);
void ParseSemicolonString(LPCTSTR s);
void RegistryQueryRegExpandValue(HKEY Key, LPCTSTR Subkey, LPCTSTR ParamName, LPTSTR OutputValue);
void ParseEnvironmentVariable(LPCTSTR VarName);
void ComboSelectionChanged();
void UpdateVariable();
int QueryUpdateVariable();
void ResizeControls();
BOOL IsRegistryParameterExists(HKEY Key, LPCTSTR Subkey, LPCTSTR ParamName);
void RegistryUpdateRegExpandValue(HKEY Key, LPCTSTR Subkey, LPCTSTR ParamName, LPTSTR NewValue);
void MoveStringUp();
void MoveStringDown();

LRESULT APIENTRY ComboWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	SHORT ss = GetKeyState(VK_SHIFT);
	BOOL shift_pressed = ss & 0x8000 ? TRUE : FALSE; //high-order bit indicates that key is down
	switch(msg)
	{
  	case WM_KEYDOWN:
    	if (VK_TAB == wparam)
		{
			if (shift_pressed)
			{
				SetFocus(g_hEdit);
				break;
			}
			else
			{
				SetFocus(g_hListBox);
				break;
			}
		}
	}
	return CallWindowProc(g_pOldComboWndProc, hwnd, msg, wparam, lparam);
}

LRESULT APIENTRY EditWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	SHORT ss = GetKeyState(VK_SHIFT);
	BOOL shift_pressed = ss & 0x8000 ? TRUE : FALSE; //high-order bit indicates that key is down
	ss = GetKeyState(VK_CONTROL);
	BOOL ctrl_pressed = ss & 0x8000 ? TRUE : FALSE;
	switch(msg)
	{
  	case WM_KEYDOWN:
  		if (VK_RETURN == wparam)
    		EditBoxEnterPressed();
      if (VK_TAB == wparam)
			{
				if (shift_pressed)
				{
					SetFocus(g_hListBox);
					break;
				}
				else
				{
      		SetFocus(g_hCombo);
					break;
				}
			}
      if (VK_UP == wparam)
      {
				if (ctrl_pressed)
					MoveStringUp();
				else
      		MoveSelectionUp();
        return 0;
      }
      if (VK_DOWN == wparam)
      {
				if (ctrl_pressed)
					MoveStringDown();
				else
      		MoveSelectionDown();
        return 0;
      }
  	default:
    	break;
	}
	return CallWindowProc(g_pOldEditWndProc, hwnd, msg, wparam, lparam);
}

LRESULT APIENTRY ListWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	SHORT ss = GetKeyState(VK_SHIFT);
	BOOL shift_pressed = ss & 0x8000 ? TRUE : FALSE; //high-order bit indicates that key is down
	ss = GetKeyState(VK_CONTROL);
	BOOL ctrl_pressed = ss & 0x8000 ? TRUE : FALSE;
	switch(msg)
  {
  	case WM_KEYDOWN:
   	if (VK_TAB == wparam)
		{
			if (shift_pressed)
			{
				SetFocus(g_hCombo);
				break;
			}
			else
			{
   			SetFocus(g_hEdit);
				break;
			}
		}
		if (VK_F2 == wparam)
		{
			SetFocus(g_hEdit);
			break;
		}
		if (VK_UP == wparam)
		{
			if (ctrl_pressed)
			{
				MoveStringUp();
				return 0;
			}
		}
		if (VK_DOWN == wparam)
		{
				if (ctrl_pressed)
				{
					MoveStringDown();
					return 0;
				}
		}
    default:
    	break;
  }
	return CallWindowProc(g_pOldListWndProc, hwnd, msg, wparam, lparam);
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
  {
  	case WM_SIZE:
    	ResizeControls();
      break;
  	case WM_DESTROY:
	    PostQuitMessage(0);
  	  return 0;
    case WM_CLOSE:
    {
    	int r = QueryUpdateVariable();
      switch(r)
      {
      	case IDYES:
	      	UpdateVariable();
  	      DestroyWindow(g_hMain);
          break;
        case IDNO:
        	DestroyWindow(g_hMain);
          break;
      }
      return 0;
    }
    case WM_COMMAND:
      if (HIWORD(wparam) == 0) // notification from menu
      {
      	switch(LOWORD(wparam))
        {
					case ID_FILE_EXIT:
        		PostQuitMessage(0);
          	return 0;
          case ID_HELP_ABOUT:
          	MessageBox(hwnd, STR_ABOUT_HELP, STR_ABOUTBOX_CAPTION, MB_OK);
            return 0;
          case ID_COMMAND_UPDENVVAR:
          	UpdateVariable();
            return 0;
          default:
						return 0;
        }
      }
      if (HIWORD(wparam) == LBN_SELCHANGE) //notification from list box
      {
      	ListBoxSelChange();
        return 0;
      }
      if (HIWORD(wparam) == CBN_SELENDOK) // notification from combo box
      {
      	ComboSelectionChanged();
        return 0;
      }
    case WM_ACTIVATE:
    {
    	if (WA_ACTIVE == wparam || WA_CLICKACTIVE == wparam)
      {
      	SetFocus(g_hEdit);
        return 0;
      }
    }
    default:
    	break;
  }
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadResources(hInstance);
	DWORD err = 0;
  WNDCLASS wc;
  ZeroMemory(&wc, sizeof wc);
	wc.style = CS_SAVEBITS | CS_DBLCLKS;
  wc.lpfnWndProc = MainWndProc;
	wc.hInstance = hInstance;
  wc.hIcon = 0;//default icon
  wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
  wc.lpszClassName = _T("PathEdMainWindowClass");
  ATOM wca; //window class atom
  wca = RegisterClass(&wc);
	err = GetLastError();

  g_hMain = CreateWindow(
  	(LPTSTR) MAKELPARAM(wca,0),
    _T("PATH Editor"),
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100,
    100,
    800,
    600,
    0, // parent window
    LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MAIN_MENU) ), //menu
    hInstance,
    0);//lParam
  if (! g_hMain)
  {
  	err = GetLastError();
  	TCHAR buf[256];
    _stprintf(buf, STR_ERROR_CREATE_MAINWND, err);
    MessageBox(0, buf, STR_ERRORBOX_CAPTION, MB_OK | MB_ICONSTOP);
    return 1;
  }
  g_hCombo = CreateWindowEx(
  	WS_EX_CLIENTEDGE,
    _T("COMBOBOX"),
    _T("EnvVar"),
    WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST,
    0, 0, 750, 300,
    g_hMain,
    0,
    hInstance,
    0);
  g_pOldComboWndProc = (WNDPROC) SetWindowLongPtr(g_hCombo, GWLP_WNDPROC, (LONG_PTR) ComboWndProc);
  SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) _T("PATH"));
  SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) _T("LIB"));
  SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) _T("INCLUDE"));
  SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) _T("OS2LIBPATH"));
  SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) _T("PATHEXT"));
  SendMessage(g_hCombo, CB_SETCURSEL, 0, 0);

  g_hListBox = CreateWindowEx(
  	WS_EX_CLIENTEDGE,
    _T("LISTBOX"),
    _T("File"),
    WS_CHILD | WS_TABSTOP | WS_VISIBLE | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
    0,30,800,500,
    g_hMain,
    0,//menu
    hInstance,
    0);
  g_pOldListWndProc = (WNDPROC) SetWindowLongPtr(g_hListBox, GWLP_WNDPROC, (LONG_PTR) ListWndProc);
  HFONT lbfont = 0;
  lbfont = CreateFont(16, 0, GM_COMPATIBLE, GM_COMPATIBLE, FW_NORMAL, FALSE, FALSE, FALSE,
  ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Courier"));
  if (lbfont)
  {
  	SendMessage(g_hListBox, WM_SETFONT, (WPARAM) lbfont, MAKELPARAM(TRUE,0) );
    SendMessage(g_hCombo, WM_SETFONT, (WPARAM) lbfont, MAKELPARAM(TRUE,0) );
  }

  g_hEdit = CreateWindowEx(
  	WS_EX_CLIENTEDGE,
    _T("EDIT"),
    _T("Edit"),
    WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_NOHIDESEL,
    0, 530, 800, 20,
    g_hMain, 0, hInstance,0);
  g_pOldEditWndProc = (WNDPROC) SetWindowLongPtr(g_hEdit, GWLP_WNDPROC, (LONG_PTR) EditWndProc);
  SendMessage(g_hEdit, WM_SETFONT, (WPARAM) lbfont, MAKELPARAM(TRUE,0) );
  //начальная настройка
  SetFocus(g_hEdit);
  SetEditText(_T(""));
  ComboSelectionChanged();
  ResizeControls();

  MSG msg;
  while (GetMessage(&msg, 0, 0, 0))
  {
 		TranslateMessage(&msg);
   	DispatchMessage(&msg);
  }
	return msg.wParam;
}
//---------------------------------------------------------------------------

void AddListBoxItem(LPCTSTR text)
{
	if (! g_hListBox) return;
  SendMessage(g_hListBox, LB_ADDSTRING, 0, (long) text);
}

void ListBoxSelChange()
{
	int cur_sel = SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
  if (cur_sel == LB_ERR) return;
	TCHAR buf[4096];
  int str_len = SendMessage(g_hListBox, LB_GETTEXT, cur_sel, (LPARAM) buf);
  if (str_len == LB_ERR) return;
  if (lstrcmpi (buf, STR_SYSTEM) == 0
  		|| lstrcmpi(buf, STR_USER) == 0)
	{
  	SetEditText(_T(""));
	}
	else if (lstrcmpi (buf, _T("*") ) == 0) 
	{
		SetEditText( STR_INSERT_HINT );
	}
  else
	{
  	SetEditText(buf);
	}
  SendMessage(g_hEdit, EM_SETSEL, 0, -1);//select all text in edit
}

//изменить выделенную строку в списке на то, что находится в EditBox
//если в списке на этом месте ключевые слова :SYSTEM или :USER, то не менять
//если в списке звездочка, то
	//{если меняется не на пустую строку, добавить строку со звездочкой сразу после вставленной
  //если меняется на пустую строку, то оставить звездочку}
//если строка меняется на пустую строку, то удалить ее из списка
void EditBoxEnterPressed()
{
  int zindex = SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
  if (zindex == LB_ERR) return;
  TCHAR buf[4096], list_buf[4096];
  SendMessage(g_hListBox, LB_GETTEXT, zindex, (LPARAM) list_buf);
  //не надо менять ключевые слова
  if (lstrcmpi(list_buf, STR_SYSTEM) == 0
  		|| lstrcmpi(list_buf, STR_USER) == 0) return;
  SendMessage(g_hEdit, WM_GETTEXT, sizeof buf,(LPARAM) buf);
  //не надо добавлять лишние ключевые слова
  if (lstrcmpi(buf, STR_SYSTEM) == 0
  		|| lstrcmpi(buf, STR_USER) == 0
      || lstrcmpi(buf, _T("*")) == 0) return;

	if (lstrcmpi(list_buf, _T("*")) == 0) // добавление строки в список
  {
  	if (lstrcmpi(buf, _T("")) == 0 || lstrcmpi(buf, _T("*")) == 0) return;
    else
    {
		  zindex = SendMessage(g_hListBox, LB_INSERTSTRING, zindex, (LPARAM) buf);
  		if (zindex == LB_ERR || zindex == LB_ERRSPACE) return;
  		SendMessage(g_hListBox, LB_SETCURSEL, zindex, 0);
      g_Cls.m_bModified = TRUE;
    }
  }
  int remaining = SendMessage(g_hListBox, LB_DELETESTRING, zindex, 0);
  if (remaining == LB_ERR) return;
  if (lstrcmpi(buf, _T("")) == 0) // ввод пустого значения приведет к удалению строки
  {
    SendMessage(g_hListBox, LB_SETCURSEL, zindex - 1, 0);
    ListBoxSelChange();
    g_Cls.m_bModified = TRUE;
  	return;
  }
  // обновление строки
  if ( lstrcmpi(buf, list_buf) != 0) g_Cls.m_bModified = TRUE;
  zindex = SendMessage(g_hListBox, LB_INSERTSTRING, zindex, (LPARAM) buf);
  if (zindex == LB_ERR || zindex == LB_ERRSPACE) return;
  SendMessage(g_hListBox, LB_SETCURSEL, zindex, 0);
}

void MoveSelectionUp()
{
	int i = SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
  if (LB_ERR == i) return;
  if (i) SendMessage(g_hListBox, LB_SETCURSEL, i - 1, 0);
  ListBoxSelChange();
}

void MoveSelectionDown()
{
	int i = SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
  if (LB_ERR == i) i = 0;
  int c = SendMessage(g_hListBox, LB_GETCOUNT, 0, 0);
  if (LB_ERR == c) return;
  if (i < c-1 ) SendMessage(g_hListBox, LB_SETCURSEL, i + 1, 0);
  ListBoxSelChange();
}

void SetEditText(LPCTSTR text)
{
	if (text) SendMessage(g_hEdit, WM_SETTEXT, 0, (LPARAM) text);
}

void ClearListBox()
{
	LONG remaining;
	while ( (remaining = SendMessage(g_hListBox, LB_DELETESTRING, 0, 0))
  			&& remaining != LB_ERR );
}



void ShowErrorMessage(LPCTSTR text)
{
	MessageBox(g_hMain, text, STR_ERRORBOX_CAPTION, MB_OK | MB_ICONSTOP);
}

void ParseSemicolonString(LPCTSTR s)
{
  TCHAR *i;
  TCHAR buf[MAX_PATH];
  i= buf; //iterator
  while ( *i++ = *s++ )
  {
    if (*s == ';' || *s == '\0')
    {
    	*i = '\0';
			if (lstrcmpi(buf, _T("")) != 0) AddListBoxItem(buf);
      i = buf ;
			if (*s != 0) ++s;
    }
  }
}


void RegistryQueryRegExpandValue(HKEY Key, LPCTSTR Subkey, LPCTSTR ParamName, LPTSTR OutputValue)
{
	TCHAR buf[400];
	HKEY k;
  LONG ret;
  ret = RegOpenKeyEx(
  	Key,
    Subkey,
    0,
    KEY_ALL_ACCESS,
    &k);
  if (ret != ERROR_SUCCESS)
  {
    _stprintf(buf, STR_ERROR_OPEN_KEY, Subkey, ret);
    ShowErrorMessage(buf);
    return;
  }
  DWORD bytes_needed;
  DWORD type = REG_EXPAND_SZ;
  ret = RegQueryValueEx(
  	k,
    ParamName,
    0,
    &type,
    0,
    &bytes_needed);
  ret = RegQueryValueEx(
  	k,
    ParamName,
    0,
    &type,
    (LPBYTE)OutputValue,
    &bytes_needed);
  if (ERROR_SUCCESS != ret)
  {
  	_stprintf(buf, STR_ERROR_QUERY_VALUE_FROM_REGISTRY, ParamName, ret);
    //ShowErrorMessage(buf);
    //возвращает 0x02 если нет такого ключа
    return;
  }
  RegCloseKey(k);
}

void ParseEnvironmentVariable(LPCTSTR VarName)
{
	TCHAR buf[4096]; ZeroMemory(buf, sizeof buf);
	RegistryQueryRegExpandValue(HKEY_LOCAL_MACHINE,
		STR_MACHINE_ENV_SUBKEY,
  	VarName,
		buf);
  AddListBoxItem(STR_SYSTEM);
  ParseSemicolonString(buf);
  AddListBoxItem(_T("*"));
 	RegistryQueryRegExpandValue(HKEY_CURRENT_USER,
		STR_USER_ENV_SUBKEY,
  	VarName,
		buf);
  AddListBoxItem(STR_USER);
  ParseSemicolonString(buf);
  AddListBoxItem(_T("*"));
}

void ComboSelectionChanged()
{
	int ret = QueryUpdateVariable();
  if (IDCANCEL == ret)
  {
  	//поставить старый selection в ComboBox
    //он должен быть в g_Cls.EnvVarName
    int prev_index = SendMessage(g_hCombo, CB_FINDSTRING, -1, (LPARAM)g_Cls.EnvVarName);
    if (CB_ERR == prev_index) return;
    SendMessage(g_hCombo, CB_SETCURSEL, prev_index, 0);
  	return;
  }
	if (IDYES ==  ret ) UpdateVariable();
  int zi = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
  TCHAR buf[256];
  if (CB_ERR == SendMessage(g_hCombo, CB_GETLBTEXT, zi, (LPARAM) buf)) return;
	ClearListBox();
  SendMessage(g_hEdit, WM_SETTEXT, 0, 0);
  ParseEnvironmentVariable(buf);
  g_Cls.m_bModified = FALSE;
  lstrcpy(g_Cls.EnvVarName, buf);
}


//взять имя переменной из g_Cls.EnvVarName
 //пройтись по списку и сделать semicolon-separated string
 //записать в реестр
 //отправить всем сообщение
void UpdateVariable()
{
	LONG lres = 0;
	TCHAR buf[400]; // для хранения одного токена
  ZeroMemory(buf, sizeof buf / sizeof buf[0]);
  TCHAR *sysrs = new TCHAR[40000];
  ZeroMemory(sysrs, 40000);
  TCHAR *urs = new TCHAR[40000];
  ZeroMemory(urs, 40000);
	int cnt = SendMessage(g_hListBox, LB_GETCOUNT, 0, 0);
  if (LB_ERR == cnt) return;
  BOOL user = FALSE;
  for (int i = 0; i < cnt; ++i)
  {
		lres = SendMessage(g_hListBox, LB_GETTEXT, i, (LPARAM) buf);
    if (LB_ERR == lres)
    {
      ShowErrorMessage(STR_ERROR_READING_LINE_FROM_LIST);
      return;
    }
    if (lstrcmpi(buf, STR_USER) == 0) user = TRUE;
    if (lstrcmpi (buf, STR_SYSTEM) == 0
    		|| lstrcmpi(buf, _T("*")) == 0
        || lstrcmpi(buf, STR_USER) == 0 ) continue;
    buf[lres] = 0; //terminating string with 0
    if (!user)
    {
    	if (lstrlen (sysrs) > 0) lstrcat(sysrs, _T(";\0"));
    	lstrcat(sysrs, buf);
    }
    else
    {
    	if (lstrlen (urs) > 0) lstrcat (urs, _T(";\0"));
      lstrcat(urs, buf);
    }
  }

  //MessageBox(g_hMain, sysrs, STR_SYSTEM, MB_OK);
  //MessageBox(g_hMain, urs, STR_USER, MB_OK);
	//return;

	RegistryUpdateRegExpandValue(
  	HKEY_LOCAL_MACHINE,
    STR_MACHINE_ENV_SUBKEY,
    g_Cls.EnvVarName,
    sysrs);

  RegistryUpdateRegExpandValue(
  	HKEY_CURRENT_USER,
    STR_USER_ENV_SUBKEY,
    g_Cls.EnvVarName,
    urs);

  delete [] sysrs;
  delete [] urs;
	//видимо, STR_USER_ENV_SUBKEY = "Environment"  - какое-то ключевое слово
  SendMessageTimeout(
  	HWND_BROADCAST,
    WM_SETTINGCHANGE,
    0, (LPARAM) STR_USER_ENV_SUBKEY,
    SMTO_BLOCK,
    500,
    0);
  g_Cls.m_bModified = FALSE;
}

int QueryUpdateVariable()
{
	TCHAR q[256];
	if (g_Cls.m_bModified)
  {
    _stprintf(q, STR_QUERY_UPDATE_VARIABLE, g_Cls.EnvVarName);
		return MessageBox(g_hMain, q , STR_ABOUTBOX_CAPTION, MB_YESNOCANCEL | MB_ICONQUESTION);
  }
  return IDNO;
}

void ResizeControls()
{
	RECT rc;
  GetClientRect(g_hMain, &rc);
  MoveWindow(g_hCombo, 0, 0, rc.right, 20, TRUE);
  MoveWindow(g_hListBox, 0, 25, rc.right, rc.bottom - rc.top - 25 - 20, TRUE);
  MoveWindow(g_hEdit, 0, rc.bottom - 20, rc.right, 20, TRUE);
}


BOOL IsRegistryParameterExists(HKEY Key, LPCTSTR Subkey, LPCTSTR ParamName)
{
	HKEY k;
  LONG ret;
  DWORD type = REG_EXPAND_SZ;
  DWORD bytes_needed = 0;
  ret = RegOpenKeyEx(
  	Key,
    Subkey,
    0,
    KEY_ALL_ACCESS,
    &k);
  if (ret != ERROR_SUCCESS)	return FALSE;
  ret = RegQueryValueEx(
  	k,
    ParamName,
    0,
    &type,
    0,
    &bytes_needed);
  if (ERROR_SUCCESS == ret)
  {
  	RegCloseKey(k);
    return TRUE;
  }
  else
  {
  	RegCloseKey(k);
  	return FALSE;
  }
}

void RegistryUpdateRegExpandValue(HKEY Key, LPCTSTR Subkey, LPCTSTR ParamName, LPTSTR NewValue)
{
	TCHAR buf[400];
	HKEY k;
  LONG ret;
  DWORD type = REG_EXPAND_SZ;
  ret = RegOpenKeyEx(
  	Key,
    Subkey,
    0,
    KEY_ALL_ACCESS,
    &k);
  if (ret != ERROR_SUCCESS)
  {
    _stprintf(buf, STR_ERROR_OPEN_KEY, Subkey, ret);
    ShowErrorMessage(buf);
    return;
  }
  DWORD cblen = lstrlen(NewValue) + 1;
  ret = RegSetValueEx(
  	k,
    ParamName,
    0,
    type,
    (LPBYTE) NewValue,
    cblen * sizeof TCHAR);
  if (ret != ERROR_SUCCESS)
  {
  	_stprintf(buf, STR_ERROR_WRITE_VALUE_TO_REGISTRY,
      Key == HKEY_LOCAL_MACHINE ? _T("HKEY_LOCAL_MACHINE") : _T("HKEY_CURRENT_USER"),
      Subkey,
      ParamName,
      NewValue);
      ShowErrorMessage(buf);
  }
  RegCloseKey(k);
}

//сдвинуть строку вверх, если она не не первая, или выше ее спецсимвол
void MoveStringUp()
{
	TCHAR buf_curr[MAX_PATH], buf_above[MAX_PATH];
	LONG selected = SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
	if (LB_ERR == selected || selected < 2) return;
	SendMessage(g_hListBox, LB_GETTEXT, selected, (LPARAM) buf_curr);
	SendMessage(g_hListBox, LB_GETTEXT, selected - 1, (LPARAM) buf_above);
	if (lstrcmpi(buf_above, STR_SYSTEM) == 0
			|| lstrcmpi(buf_above, STR_USER) == 0
			|| lstrcmpi(buf_above, _T("*") ) == 0 
			|| lstrcmpi(buf_curr, STR_SYSTEM) == 0
			|| lstrcmpi(buf_curr, STR_USER) == 0
			|| lstrcmpi(buf_curr, _T("*")) == 0)  return;

	SendMessage(g_hListBox, LB_DELETESTRING, selected, 0);
	SendMessage(g_hListBox, LB_INSERTSTRING, selected, (LPARAM) buf_above);
	SendMessage(g_hListBox, LB_DELETESTRING, selected - 1, 0);
	SendMessage(g_hListBox, LB_INSERTSTRING, selected - 1, (LPARAM) buf_curr);
	
	SendMessage(g_hListBox, LB_SETCURSEL, selected - 1, 0);
	g_Cls.m_bModified = TRUE;
}



//сдвинуть строку вниз, если она не последняя, или ниже ее спецсимвол
void MoveStringDown()
{
	TCHAR buf_curr[MAX_PATH], buf_below[MAX_PATH];
	LONG selected = SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
	LONG cnt = SendMessage(g_hListBox, LB_GETCOUNT, 0, 0);
	if (LB_ERR == selected || selected > cnt - 2) return;
	SendMessage(g_hListBox, LB_GETTEXT, selected, (LPARAM) buf_curr);
	SendMessage(g_hListBox, LB_GETTEXT, selected + 1, (LPARAM) buf_below);
	if (lstrcmpi(buf_curr, STR_SYSTEM) == 0
			|| lstrcmpi(buf_curr, STR_USER) == 0
			|| lstrcmpi(buf_curr, _T("*")) == 0
			|| lstrcmpi(buf_below, STR_SYSTEM) == 0
			|| lstrcmpi(buf_below, STR_USER) == 0
			|| lstrcmpi(buf_below, _T("*")) == 0) return;
	SendMessage(g_hListBox, LB_DELETESTRING, selected, 0);
	SendMessage(g_hListBox, LB_INSERTSTRING, selected, (LPARAM) buf_below);
	SendMessage(g_hListBox, LB_DELETESTRING, selected + 1, 0);
	SendMessage(g_hListBox, LB_INSERTSTRING, selected + 1, (LPARAM) buf_curr);

	SendMessage(g_hListBox, LB_SETCURSEL, selected + 1, 0);
	g_Cls.m_bModified = TRUE;
}


void LoadResources(HINSTANCE h)
{
	#define LOADSTR(NAME) LoadString(h, IDS_##NAME, STR_##NAME, sizeof STR_##NAME / sizeof *STR_##NAME)
	LOADSTR(USER);
	LOADSTR(SYSTEM);
	LOADSTR(MACHINE_ENV_SUBKEY);
	LOADSTR(USER_ENV_SUBKEY);
	LOADSTR(ABOUT_HELP);
	LOADSTR(ABOUTBOX_CAPTION);
	LOADSTR(ERRORBOX_CAPTION);
	LOADSTR(INSERT_HINT);
	LOADSTR(ERROR_OPEN_KEY);
	LOADSTR(ERROR_READING_LINE_FROM_LIST);
	LOADSTR(ERROR_WRITE_VALUE_TO_REGISTRY);
	LOADSTR(ERROR_CREATE_MAINWND);
	LOADSTR(ERROR_QUERY_VALUE_FROM_REGISTRY);
	LOADSTR(QUERY_UPDATE_VARIABLE);
	#undef LOADSTR
	//LoadString(h, IDS_QUERY_UPDATE_VARIABLE, STR_QUERY_UPDATE_VARIABLE, sizeof STR_QUERY_UPDATE_VARIABLE / sizeof *STR_QUERY_UPDATE_VARIABLE);
}
