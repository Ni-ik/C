#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <malloc.h>
#include <windowsx.h>
#include <stdio.h>
#include "SR5.h"
#pragma comment (lib,"SR5.lib")
    //�������� ������� ���������
    LRESULT CALLBACK Pr5_WndProc(HWND, UINT, WPARAM, LPARAM);
  	BOOL CALLBACK DialogInfo(HWND, UINT,WPARAM,LPARAM);  
	BOOL CALLBACK WndProc_TestProcParamDlg(HWND, UINT,WPARAM,LPARAM);  
    //���������� ����������
    LPCTSTR g_lpszClassName  = TEXT("sp_sr2_5_class");
	LPCTSTR g_lpszAplicationTitle = TEXT("SP_SR 2_5_���������� �.�. 40332-1"); 
	
	#define FILENAME "FILESR25.DAT" //��� ����������� � ������ ���

	HINSTANCE hInstance;
	WPARAM wPar;
	HANDLE hFile=NULL;
	 static HMENU hMenu;
	 int g_count=0;
	char symbols[]="aAoOiIuUeE����������������޸�";
	
	HANDLE ProcHandle;


	//��������� ������� �������� ����
	void WndProc_OnDestroy(HWND);
	void WndProc_OnClose(HWND);
	void WndProc_OnPaint(HWND);
	void WndProc_OnCommand(HWND, int, HWND, UINT);
		

		
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
   {
	   WNDCLASSEX wc;
	   MSG msg;
	   HWND hWnd;
	 
	    //��������� ��������� ������ ����
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
	   
	   //������������ ����� �������� ���� � ���������
	   if(!RegisterClassEx(&wc))
	   {
		   MessageBox(NULL,TEXT("������ ����������� ������ ����!"),TEXT("������"),MB_OK|MB_ICONERROR);
		   return FALSE;
	   }
	   //2-�� ������ ����������� ����
	  hMenu = LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));

	   //������ ������� ����
	   hWnd=CreateWindowEx(NULL,g_lpszClassName,
		   g_lpszAplicationTitle,
		   WS_OVERLAPPEDWINDOW,
		   600,
		   100,
		   600,
		   400,
		   NULL,
		   hMenu,//��������� ���� 2-� ������
		   hInstance,
		   NULL);
	   //�������� �������� �������� ����
	  if(!hWnd)
	   {
		   MessageBox(NULL,TEXT("���� �� �������!"),TEXT("������"),MB_OK|MB_ICONERROR);
		   return FALSE;
	  }
	  //����������� �������� ����
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
//-----------------------------������� ��������� �������� ����--------------------------------------
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
 

			
 char * FileString = new char [1000];
  char * FileName = new char [1000];
////=====================================������� ��������� ������ ����==================================
void WndProc_OnCommand(HWND hWnd,int wmld,HWND,UINT)
{	
	static HANDLE hFile;        // ��� ����������� ������� "����"
	static HANDLE hFileMap;     // ��� ����������� ������� '������������ ����'
	static LPVOID lpvFile;      // ��� ������ ������� � �������� ������������
  
	LPSTR  lpchANSI;     // ��������� �� ANSI ������
 
	 static DWORD  dwFileSize;   // ��� �������� ������� ����� 
	
 	
	STARTUPINFOA si={0};    // ��������� ��� �������
	PROCESS_INFORMATION pi;// CreateProcess 

	char * fileName = new char [1000];			//��� �����
	char * fileString = new char [1000];		//����� �� �����

	char * addString = new char [100];
 
	switch(wmld)
	{	
		case IDM_OPEN:
			{
					//��������� ������ �������������� �� �����
					loadFile(fileString,fileName);
					 FileName = fileName;
					 FileString = fileString;
					  if (!CopyFileA(FileName, FILENAME, FALSE)) 
							{
							// ���������� �� �������
							MessageBox( NULL,"������ �������� ����� �����!","SP_SR 2_5", MB_OK);
							break;
							}
					// ��������� ���� ��� ������ � ������. ��� ����� ������� ������ ���� "����".
							 hFile = CreateFileA(	
								 FILENAME,  // ��������� �� ������ � ������� �����
								  GENERIC_WRITE | GENERIC_READ, // ��������� ����� �������
											0,   //  ����� ����������,0 - ������������� ������ � �����.       
								  NULL,// LPSECURITY_ATTRIBUTES=0 - ������ �� �����������.
								  OPEN_EXISTING,//���� ���� �� ����������, �� ���������� ������.
								  FILE_ATTRIBUTE_NORMAL,//�������� �������� ��� ���� 
								  NULL //�� ������ ��� ������� ���� "����"
								  );
								 dwFileSize = GetFileSize(hFile, NULL);
								 if (hFile == INVALID_HANDLE_VALUE) 
									{  // ������� ���� �� �������
									MessageBox(	NULL, "������ �������� �����.", "SP_SR 2_5", MB_OK);
									break;
									}
							ModifyMenu(hMenu,IDM_OPEN,MF_GRAYED|MF_STRING,IDM_OPEN,TEXT("������� ����"));// �������� ����
							ModifyMenu(hMenu,IDM_PROECTION,MF_ENABLED|MF_STRING,IDM_PROECTION,TEXT("������������ ����"));// �������� ����
							ModifyMenu(hMenu,IDM_RESULT,MF_GRAYED|MF_STRING,IDM_RESULT,TEXT("�������� ���������"));// �������� ����
					
			}  
        break;
		case IDM_PROECTION:
			{
// ������ ������ �����. ������ �������� NULL, ��� ��� ��������������,
  // ��� ���� ������ 4 ��.
			
	
	// ������� ������ "������������ ����". 
	hFileMap = CreateFileMapping(	
                    hFile,  // ���������� ������������ ������� "����" 
                    NULL,   // 
                    PAGE_READWRITE, // �������� ������ ������� 
									  0,  // LPSECURITY_ATTRIBUTES
                   0,   //������� 32 �������
                    NULL  // � ������� 32 ������� ������� �����.
                    );
	if (hFileMap == NULL) 
		{	// ������� ������ "������������ ����" �� �������
		MessageBox(	NULL,"������ �������� ������������� �����.","SP_SR 2_5",    MB_OK);
		}
	else
	{
		MessageBox(	NULL,"������ ������ - ������������ ����.","SP_SR 2_5",    MB_OK);
		ModifyMenu(hMenu,IDM_SHOW,MF_ENABLED|MF_STRING,IDM_SHOW,TEXT("����������� �� �������� ������������"));// �������� ����
		ModifyMenu(hMenu,IDM_PROECTION,MF_GRAYED|MF_STRING,IDM_PROECTION,TEXT("������������ ����"));// �������� ����
	}
			}
        break;
		case IDM_SHOW:
			{
			// ��������� ����������� ����� �� ����������� �������� ������������ �
  // �������� �����, ������� � �������� ������������� ����� ����� � ������.
  
  lpvFile = MapViewOfFile(
                hFileMap, // ���������� ������� "������������ ����" 
                FILE_MAP_WRITE, // ����� �������
                0, // ������� 32 ������� �������� �� ������ �����, 
                0, // ������� 32 ������� �������� �� ������ �����
                0  // � ���������� ������������ ����. 0 - ���� ����.
                );

	if (lpvFile == NULL)
		{// ������������� ������� ������������� ����� �� �������
		MessageBox(	NULL, "������������� ������� ������������� ����� �� �������!", "SP_SR 2_5", MB_OK);
		CloseHandle (hFileMap);// ����� ������� ��������� �������� �������
		CloseHandle(hFile);
		break;
		}

		lpchANSI = (LPSTR) lpvFile;
		lpchANSI[dwFileSize] = 0;
		
 	if (strlen(FILENAME)!=0) //���� �������� ������ �������
		{
			g_count = countSymbols(symbols,FileString); //������������ ���������� ����
			sprintf(addString,"\n���������� ���� �� �������:%d\n",g_count); 
		
			lstrcpy(&lpchANSI[dwFileSize],addString);
			dwFileSize+=lstrlen(addString);
			lpchANSI[dwFileSize] = 0;
		
		}
		else
			MessageBox(hWnd, TEXT("������ ��������� �����!"),TEXT(""),MB_OK|MB_ICONERROR);
			MessageBox(	NULL, "������� ����������� �����!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_SHOW,MF_GRAYED|MF_STRING,IDM_SHOW,TEXT("����������� �� �������� ������������"));// �������� ����
				ModifyMenu(hMenu,IDM_CLOSESHOW,MF_ENABLED|MF_STRING,IDM_CLOSESHOW,TEXT("�������� �����������"));// �������� ����
		}
        break;
		case IDM_CLOSESHOW:
			{
			 // ��������� ������������� ����� � ���� ��������� ������������
				UnmapViewOfFile(lpvFile);
				MessageBox(	NULL, "������������� ����� �������!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_CLOSEPROECTION,MF_ENABLED|MF_STRING,IDM_CLOSEPROECTION,TEXT("������� ��������"));// �������� ����
				ModifyMenu(hMenu,IDM_CLOSESHOW,MF_GRAYED|MF_STRING,IDM_CLOSESHOW,TEXT("�������� �����������"));// �������� ����
			}
        break;
		case IDM_CLOSEPROECTION:
			{
		 // ��������� ������� ������ �� ������ ���� "������������ ����"
				CloseHandle(hFileMap);	
				MessageBox(	NULL, "��������� ������� ������ �� ������ ���� - ������������ ����!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_CLOSEPROECTION,MF_GRAYED|MF_STRING,IDM_CLOSEPROECTION,TEXT("������� ��������"));// �������� ����
				ModifyMenu(hMenu,IDM_CLOSEFILE,MF_ENABLED|MF_STRING,IDM_CLOSEFILE,TEXT("������� ����"));// �������� ����
			}
        break;
		case IDM_CLOSEFILE:
			{
		 		// ������� ����������� ����� �������� ������� ����.��� �����
				// ���������� ��������� ����� � ����� �� ������� ����,
				// � ����� ���� ������� ���������� � ���� ����� ����� �����
				// ���� "������������ ����"
				 SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
				 SetEndOfFile(hFile);
				CloseHandle(hFile);// ��������� ������� ������ �� ������ ���� "����"
				MessageBox(	NULL," ��������� ������� ������ �� ������ ���� - ����!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_RESULT,MF_ENABLED|MF_STRING,IDM_RESULT,TEXT("�������� ���������"));// �������� ����
				ModifyMenu(hMenu,IDM_CLOSEFILE,MF_GRAYED|MF_STRING,IDM_CLOSEFILE,TEXT("������� ����"));// �������� ����
			}
        break;
		case IDM_RESULT:
			{
			// ��������� NOTEPAD � ��������� � ���� ��������� ����,
			 // ����� ������� ����� ����� ������
				si.cb = sizeof (si);// ��������� ���� ������� ��������� si
				si.wShowWindow = SW_SHOW;// ������ ����� ������ ���� NOTEPAD
				si.dwFlags = STARTF_USESHOWWINDOW;// ������������� ���� - ���������
                 // �������� ���� wShowWindow
				TCHAR cmdpar[260];
				wsprintf(cmdpar,"notepad.exe %s", FILENAME);
				if( CreateProcessA(	NULL,cmdpar, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))				 
				{
					// ���� ������� ������, ����������� 
					// ����������� ������ � ��������	
					CloseHandle(pi.hThread);
					CloseHandle(pi.hProcess);
					ModifyMenu(hMenu,IDM_OPEN,MF_ENABLED|MF_STRING,IDM_OPEN,TEXT("������� ����"));// �������� ����
				}	
			}
        break;
		case IDM_EXIT:
			{
			DestroyWindow(hWnd);	
			}
        break;
		default:
			break;
	}
}

//================================������� ��������� ����=============================================
void WndProc_OnPaint(HWND hWnd)
{
	HDC hDC;
	PAINTSTRUCT ps;
	hDC=BeginPaint(hWnd,&ps);
	EndPaint(hWnd,&ps);	
}
//======================================������� �������� ����==========================================
void WndProc_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
	FORWARD_WM_CLOSE(hWnd,DefWindowProc);
}
//===============================������� ��� ���������� ����================================
void WndProc_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
	FORWARD_WM_DESTROY(hWnd,DefWindowProc);
}




