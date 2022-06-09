#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <windowsx.h>
#include <stdio.h>
#include "SR4.h"

#pragma comment(lib,"SR4.lib")
    //ïðîòîòèï îêîííîé ïðîöåäóðû
    LRESULT CALLBACK Pr5_WndProc(HWND, UINT, WPARAM, LPARAM);

    //ãëîáàëüíûå ïåðåìåííûå
    LPCTSTR g_lpszClassName  = TEXT("DLL");
	LPCTSTR g_lpszAplicationTitle = TEXT("ËÐ2-4 Ïåòðàøåâè÷"); 
	
	LPTSTR ProcImage = TEXT("C:\\Windows\\system32\\notepad.exe");
	static TCHAR CmdParam[260] = TEXT("notepad.exe ");
	HANDLE ThreadHandle;
	HANDLE ProcHandle;
	int g_count=0;
	char symbols[]="aAoOiIuUeEàÀîÎèÈåÅóÓûèÈÿßþÞ¸¨";

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

	    //çàïîëíÿåì ñòðóêòóðó êëàññà îêíà
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
	   
	   //ðåãèñòðèðóåì êëàññ ãëàâíîãî îêíà ñ ïðîâåðêîé
	   if(!RegisterClassEx(&wc))
	   {
		   MessageBox(NULL,TEXT("Îøèáêà ðåãèñòðàöèè êëàññà îêíà!"),TEXT("Îøèáêà"),MB_OK|MB_ICONERROR);
		   return FALSE;
	   }
	   //2-îé ñïîñîá ïîäêëþ÷åíèÿ ìåíþ
	    HMENU hMenu = LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
	 
	   //ñîçäà¸ì ãëàâíîå îêíî
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
	   //ïðîâåðêà ñîçäàíèÿ ãëàâíîãî îêíà
	  if(!hWnd)
	   {
		   MessageBox(NULL,TEXT("Îêíî íå ñîçäàíî!"),TEXT("Îøèáêà"),MB_OK|MB_ICONERROR);
		   return FALSE;
	  }
	  //îòîáðàæåíèå ãëàâíîãî îêíà
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
//-----------------------------îêîííàÿ ïðîöåäóðà ãëàâíîãî îêíà--------------------------------------
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

 //ôóíêöèÿ îáðàáîòêè êîìàíä ìåíþ
void WndProc_OnCommand(HWND hWnd,int wmld,HWND,UINT)
{	
	char * fileName = new char [1000];			//èìÿ ôàéëà
	char * fileString = new char [1000];		//òåêñò èç ôàéëà
	char * addString = new char [100];
	char * fileName1 = new char [100];

	switch(wmld)
	{		
		
	case IDM_OPEN_COUNT:
           {
			g_count=0; 
		loadFile(fileString,fileName);	//çàãðóæàåì òåêñò èç ôàéëà
		
		if (strlen(fileName)!=0) //åñëè çàãðóçêà ïðîøëà óñïåøíî
		{
			g_count = countSymbols(symbols,fileString); //ïîäñ÷èòûâàåì êîëè÷åñòâî ðàçäåëèòåëåé
			sprintf(addString,"\nÊîëè÷åñòâî ñëîâ íà ãëàñíóþ:%d",g_count); 
			updateFile(fileName,addString); //äîïèñûâàåì â ôàéë ñòðîêó
			MessageBox(hWnd, TEXT("          Ôàéë îáðàáîòàí!            "),TEXT(""),MB_OK);
			MessageBox(hWnd, addString,TEXT(""),MB_OK);
		}
		else
			MessageBox(hWnd, TEXT("Îøèáêà îáðàáîòêè ôàéëà!"),TEXT(""),MB_OK|MB_ICONERROR);
		wsprintf((LPSTR)CmdParam, "notepad.exe %s", fileName);
		   }    
		break;
	case IDM_SHOW_FILE:
			{
				CreatMyProcess(hWnd);
				//çàêðîåì äåñêðèïòîðû ñîçäàííîãî ïðîöåññà è ïîòîêà, 
				//÷òîáû îòâÿçàòü äî÷åðíèé ïðîöåññ îò ðîäèòåëüñêîãî ïðèëîæåíèÿ
				CloseHandle(ProcHandle);
				CloseHandle(ThreadHandle);	
			}
			break;
	
		case IDM_EXIT:
             MessageBox(hWnd, TEXT("         Âûáðàí ïóíêò 'Âûõîä'        "),TEXT("Ìåíþ Ôàéë"),MB_OK);
		     DestroyWindow(hWnd);
		break;
		
	}
}

//ôóíêöèÿ îòðèñîâêè îêíà
void WndProc_OnPaint(HWND hWnd)
{
	HDC hDC;
	PAINTSTRUCT ps;
	hDC=BeginPaint(hWnd,&ps);
	EndPaint(hWnd,&ps);
}

//ôóíêöèÿ çàêðûòèÿ îêíà
void WndProc_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
	FORWARD_WM_CLOSE(hWnd,DefWindowProc);
}
//ôóíêöèÿ ïðè ðàçðóøåíèè îêíà
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
		MessageBox(hWnd,TEXT("Îøèáêà ñîçäàíèÿ ïðîöåññà!"),NULL,MB_OK|MB_ICONERROR);
	ProcHandle=pi.hProcess;
	ThreadHandle=pi.hThread;	
}







