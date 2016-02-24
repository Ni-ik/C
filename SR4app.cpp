#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <windowsx.h>
#include <stdio.h>
#include "SR4.h"

#pragma comment(lib,"SR4.lib")
    //прототип оконной процедуры
    LRESULT CALLBACK Pr5_WndProc(HWND, UINT, WPARAM, LPARAM);

    //глобальные переменные
    LPCTSTR g_lpszClassName  = TEXT("DLL");
	LPCTSTR g_lpszAplicationTitle = TEXT("Ћ–2-4 ѕетрашевич"); 
	
	LPTSTR ProcImage = TEXT("C:\\Windows\\system32\\notepad.exe");
	static TCHAR CmdParam[260] = TEXT("notepad.exe ");
	HANDLE ThreadHandle;
	HANDLE ProcHandle;
	int g_count=0;
	char symbols[]="aAoOiIuUeEајоќи»е≈у”ыи»€яюёЄ®";

	HINSTANCE hInstance;
	WPARAM wPar;
	void WndProc_OnDestroy(HWND);
	void WndProc_OnClose(HWND);
	void WndProc_OnPaint(HWND);
	void WndProc_OnCommand(HWND, int, HWND, UINT);
	void CreatMyProcess(HWND);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
   {
	   WNDCLASSEX wc;
	   MSG msg;
	   HWND hWnd;

	    //заполн€ем структуру класса окна
	   memset(&wc,0,sizeof(WNDCLASSEX));
	   wc.cbSize=sizeof(WNDCLASSEX);
	   wc.lpszClassName=g_lpszClassName;
	   wc.lpfnWndProc=Pr5_WndProc;
	   wc.style=CS_VREDRAW|CS_HREDRAW;
	   wc.hInstance =hInstance;
	   wc.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	   wc.hCursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
	   wc.hbrBackground=CreateSolidBrush(RGB(255,255,255));
	    wc.lpszMenuName=NULL;
	   wc.cbClsExtra=0;
	   wc.cbWndExtra=0;
	   
	   //регистрируем класс главного окна с проверкой
	   if(!RegisterClassEx(&wc))
	   {
		   MessageBox(NULL,TEXT("ќшибка регистрации класса окна!"),TEXT("ќшибка"),MB_OK|MB_ICONERROR);
		   return FALSE;
	   }
	   //2-ой способ подключени€ меню
	    HMENU hMenu = LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
	 
	   //создаЄм главное окно
	   hWnd=CreateWindowEx(NULL,g_lpszClassName,
		   g_lpszAplicationTitle,
		   WS_OVERLAPPEDWINDOW,
		   100,
		   100,
		   800,
		   600,
		   NULL,
		   hMenu,
		   hInstance,
		   NULL);
	   //проверка создани€ главного окна
	  if(!hWnd)
	   {
		   MessageBox(NULL,TEXT("ќкно не создано!"),TEXT("ќшибка"),MB_OK|MB_ICONERROR);
		   return FALSE;
	  }
	  //отображение главного окна
		   ShowWindow(hWnd,nCmdShow);
		   UpdateWindow(hWnd);					

				     while(GetMessage(&msg,NULL,0,0))
				   {
					 	   TranslateMessage(&msg);	  
					    	DispatchMessage(&msg);	 
				   }
	   return msg.wParam;
}
//////////////////////////////////////////////////////////////////////////////
//-----------------------------оконна€ процедура главного окна--------------------------------------
 LRESULT CALLBACK Pr5_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	wPar=wParam;
	switch(msg)
	{			
	       	HANDLE_MSG(hWnd,WM_COMMAND,WndProc_OnCommand);
            HANDLE_MSG(hWnd,WM_PAINT,WndProc_OnPaint);
			HANDLE_MSG(hWnd,WM_CLOSE,WndProc_OnClose);
			HANDLE_MSG(hWnd,WM_DESTROY,WndProc_OnDestroy);
			default:
				return(DefWindowProc(hWnd,msg,wParam,lParam));
			}
	return FALSE;
}

 //функци€ обработки команд меню
void WndProc_OnCommand(HWND hWnd,int wmld,HWND,UINT)
{	
	char * fileName = new char [1000];			//им€ файла
	char * fileString = new char [1000];		//текст из файла
	char * addString = new char [100];
	char * fileName1 = new char [100];

	switch(wmld)
	{		
		
	case IDM_OPEN_COUNT:
           {
			g_count=0; 
		loadFile(fileString,fileName);	//загружаем текст из файла
		
		if (strlen(fileName)!=0) //если загрузка прошла успешно
		{
			g_count = countSymbols(symbols,fileString); //подсчитываем количество разделителей
			sprintf(addString,"\n оличество слов на гласную:%d",g_count); 
			updateFile(fileName,addString); //дописываем в файл строку
			MessageBox(hWnd, TEXT("          ‘айл обработан!            "),TEXT(""),MB_OK);
			MessageBox(hWnd, addString,TEXT(""),MB_OK);
		}
		else
			MessageBox(hWnd, TEXT("ќшибка обработки файла!"),TEXT(""),MB_OK|MB_ICONERROR);
		wsprintf((LPSTR)CmdParam, "notepad.exe %s", fileName);
		   }    
		break;
	case IDM_SHOW_FILE:
			{
				CreatMyProcess(hWnd);
				//закроем дескрипторы созданного процесса и потока, 
				//чтобы отв€зать дочерний процесс от родительского приложени€
				CloseHandle(ProcHandle);
				CloseHandle(ThreadHandle);	
			}
			break;
	
		case IDM_EXIT:
             MessageBox(hWnd, TEXT("         ¬ыбран пункт '¬ыход'        "),TEXT("ћеню ‘айл"),MB_OK);
		     DestroyWindow(hWnd);
		break;
		
	}
}

//функци€ отрисовки окна
void WndProc_OnPaint(HWND hWnd)
{
	HDC hDC;
	PAINTSTRUCT ps;
	hDC=BeginPaint(hWnd,&ps);
	EndPaint(hWnd,&ps);
}

//функци€ закрыти€ окна
void WndProc_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
	FORWARD_WM_CLOSE(hWnd,DefWindowProc);
}
//функци€ при разрушении окна
void WndProc_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
	FORWARD_WM_DESTROY(hWnd,DefWindowProc);
}

void CreatMyProcess(HWND hWnd)
{
	BOOL success;
	static PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb=sizeof(si);
	success=CreateProcess(ProcImage, CmdParam,NULL , NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if(!success)
		MessageBox(hWnd,TEXT("ќшибка создани€ процесса!"),NULL,MB_OK|MB_ICONERROR);
	ProcHandle=pi.hProcess;
	ThreadHandle=pi.hThread;	
}







