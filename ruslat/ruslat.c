/*
RusLat – индикатор текущей раскладки клавиатуры. Версия 1.7.9 от 12.08.00

Данная программа представляет собой свободно распространяемый
программный продукт; вы можете распространять ее далее и\или изменять
на условиях Стандартной публичной лицензии GNU, опубликованной
"Free Software Foundation" - либо ее версии номер 2, либо (по вашему
выбору) любой более поздней ее версии.

Распространяя данный программный продукт, мы надеемся что он окажется
полезным, но НЕ ДАЕМ НИКАКИХ ГАРАНТИЙ, даже подразумеваемой гарантии
ПРИГОДНОСТИ К КУПЛЕ-ПРОДАЖЕ или ИСПОЛЬЗОВАНИЮ В КОНКРЕТНЫХ ЦЕЛЯХ
(см. "Стандартную публичную лицензию GNU").

Вместе с данной программой вы должны были получить копию "Стандартной
публичной лицензии GNU"; если это не так, напишите в Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

E-mail: e-vasil@yandex.ru
Web: winapi32.narod.ru 
*/

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <string.h>
#include <shellapi.h>
#include <winuser.h>
#include <cpl.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "ruslatres.h"

#define MYWM_NOTIFYICON WM_USER+1

HINSTANCE hInst;
HWND hwndMain;
HKL kbl;
HWND CurApp;
DWORD idthd;
//
NOTIFYICONDATA tnid;

HICON hIconRus;
HICON hIconEng;
HICON hIconUkr;
HICON hIconDch;
HICON hIconLat;
HICON hIconLit;
HICON hIconSpn;
HICON hIconEst;
HICON hIconFra;

//HWND hMenu;
HMENU hMenu;

int oldmode, newmode;
HANDLE mutex;

char IniFileName[1024];
int iSnd;
char sSnd[256];
int iNT=0;

void SoundBeep(int iHz)
{
int OldP;
int iCnt;
	if (iNT==1)
		{
			Beep(iHz,50);
		} else
			{
				iCnt=11932800/iHz;
				_outp( 0x43, 0xb6 );
				_outp( 0x42,iCnt-abs(iCnt/256)*256);
				_outp( 0x42, abs(iCnt / 256) );
				OldP = _inp( 0x61 );
				_outp( 0x61, OldP | 0x3 );
				Sleep(50);
				_outp( 0x61, OldP );
			}
};

void setmod(int mode)
{
		switch(mode)
			{
				case 1049:
					tnid.hIcon = hIconRus;
					lstrcpyn(tnid.szTip, "Russian", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(4000);
					break;

				case 1033:
					tnid.hIcon = hIconEng;
					lstrcpyn(tnid.szTip, "English (USA)", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(4500);
					break;

				case 1058:
					tnid.hIcon = hIconUkr;
					lstrcpyn(tnid.szTip, "Ukrainian", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(5000);
					break;

				case 1031:
					tnid.hIcon = hIconDch;
					lstrcpyn(tnid.szTip, "German (St)", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(5500);
					break;

				case 1062:
					tnid.hIcon = hIconLat;
					lstrcpyn(tnid.szTip, "Latvian", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(6000);
					break;

				case 1063:
					tnid.hIcon = hIconLit;
					lstrcpyn(tnid.szTip, "Lithuanian", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(6500);
					break;

				case 1034:
					tnid.hIcon = hIconSpn;
					lstrcpyn(tnid.szTip, "Spanish (Tr)", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(7000);
					break;

				case 1061:
					tnid.hIcon = hIconEst;
					lstrcpyn(tnid.szTip, "Estonian", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(7500);
					break;

				case 1036:
					tnid.hIcon = hIconFra;
					lstrcpyn(tnid.szTip, "French (St)", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					if(iSnd==1)SoundBeep(8500);
					break;

				default:
					tnid.hIcon = LoadIcon (NULL, IDI_QUESTION) ;
					lstrcpyn(tnid.szTip, "Not determined", sizeof(tnid.szTip));
					Shell_NotifyIcon(NIM_MODIFY,&tnid);
					break;
			}
}

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	POINT pt;

	switch (msg) {
	case MYWM_NOTIFYICON:
		switch (lParam)
		{
		case WM_RBUTTONDOWN:
			GetCursorPos(&pt);
			SetForegroundWindow(hwndMain);
            TrackPopupMenuEx(hMenu, TPM_HORIZONTAL | TPM_LEFTALIGN, pt.x, pt.y, hwndMain,NULL);
            PostMessage(hwnd, WM_USER, 0, 0);
			break;
		}
	break;

	case WM_TIMER:

		CurApp=GetForegroundWindow();
		idthd=GetWindowThreadProcessId(CurApp,NULL);
		kbl=GetKeyboardLayout(idthd);
		newmode=(int)LOWORD(kbl);

	if (newmode!=oldmode)
		{
			oldmode=newmode;
			setmod(newmode);
		};

		return 1;
	case WM_COMMAND:
		switch (LOWORD (wParam))
        	{
            case IDM_EXIT:
				SendMessage (hwndMain, WM_CLOSE, 0, 0) ;
				break;
			case  IDM_ABOUT:
				ShellAbout(0,"RusLat(ver. 1.7.9)","E_mail: e_vasil@newmail.ru",NULL);
				break;
			case  IDM_PROP:
				WinExec("rundll32.exe shell32.dll,Control_RunDLL Main.cpl @1,1",SW_SHOWDEFAULT);
				break;

			case IDM_RSOUND:
				if(iSnd==0)
					{
						CheckMenuItem(hMenu,IDM_RSOUND,MF_CHECKED);
						iSnd=1;
					}else
					{
						CheckMenuItem(hMenu,IDM_RSOUND,MF_UNCHECKED);
						iSnd=0;
						RedrawWindow(NULL,NULL,NULL,RDW_FRAME);
					}
			wsprintf(sSnd,"%i",iSnd);
			GetWindowsDirectory(IniFileName,1024);
			wsprintf(IniFileName,"%s\\ruslat.ini",IniFileName);
			WritePrivateProfileString ("Options","Sound",sSnd,IniFileName);
			break;

			}
		break;

	case WM_DESTROY:
		Shell_NotifyIcon(NIM_DELETE,&tnid);
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		hMenu = LoadMenu (hInst,"PopMenu") ;
		hMenu = GetSubMenu (hMenu, 0) ;
		break;

	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;
	WNDCLASS wc;
	DWORD dwVer;

	hInst = hInstance;
	memset(&wc,0,sizeof(WNDCLASS));
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = "ruslatWndClass";
	RegisterClass(&wc);
		hwndMain=CreateWindow("ruslatWndClass","ruslat",0,
		0,0,0,0,
		NULL,
		NULL,
		hInst,
		NULL);
		ShowWindow(hwndMain,SW_HIDE);

		hIconRus=LoadIcon(hInst,"a");
		hIconEng=LoadIcon(hInst,"b");
		hIconUkr=LoadIcon(hInst,"c");
		hIconDch=LoadIcon(hInst,"d");
		hIconLat=LoadIcon(hInst,"e");
		hIconLit=LoadIcon(hInst,"f");
		hIconSpn=LoadIcon(hInst,"j");
		hIconEst=LoadIcon(hInst,"k");
		hIconFra=LoadIcon(hInst,"l");

		tnid.cbSize = sizeof(NOTIFYICONDATA);
		tnid.hWnd = hwndMain;
		tnid.uID = 505;
		tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		tnid.uCallbackMessage = MYWM_NOTIFYICON;
    	Shell_NotifyIcon(NIM_ADD, &tnid);

		GetWindowsDirectory(IniFileName,1024);
		wsprintf(IniFileName,"%s\\ruslat.ini",IniFileName);
		iSnd=GetPrivateProfileInt("Options","Sound",0,IniFileName);
		if(iSnd==1) CheckMenuItem(hMenu,IDM_RSOUND,MF_CHECKED);
		if(iSnd==0) CheckMenuItem(hMenu,IDM_RSOUND,MF_UNCHECKED);

		dwVer = GetVersion();
		if (dwVer < 0x80000000) iNT=1;



	SetTimer(hwndMain,1,100,NULL);
	while (GetMessage(&msg,NULL,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	return msg.wParam;
}

