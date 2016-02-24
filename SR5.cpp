#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <malloc.h>
#include <windowsx.h>
#include <stdio.h>
#include "SR5.h"
#pragma comment (lib,"SR5.lib")
    //прототип оконной процедуры
    LRESULT CALLBACK Pr5_WndProc(HWND, UINT, WPARAM, LPARAM);
  	BOOL CALLBACK DialogInfo(HWND, UINT,WPARAM,LPARAM);  
	BOOL CALLBACK WndProc_TestProcParamDlg(HWND, UINT,WPARAM,LPARAM);  
    //глобальные переменные
    LPCTSTR g_lpszClassName  = TEXT("sp_sr2_5_class");
	LPCTSTR g_lpszAplicationTitle = TEXT("SP_SR 2_5_Петрашевич Н.С. 40332-1"); 
	
	#define FILENAME "FILESR25.DAT" //для копирования в данный фай

	HINSTANCE hInstance;
	WPARAM wPar;
	HANDLE hFile=NULL;
	 static HMENU hMenu;
	 int g_count=0;
	char symbols[]="aAoOiIuUeEаАоОиИеЕуУыиИяЯюЮёЁ";
	
	HANDLE ProcHandle;


	//прототипы функций главного окна
	void WndProc_OnDestroy(HWND);
	void WndProc_OnClose(HWND);
	void WndProc_OnPaint(HWND);
	void WndProc_OnCommand(HWND, int, HWND, UINT);
		

		
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
   {
	   WNDCLASSEX wc;
	   MSG msg;
	   HWND hWnd;
	 
	    //заполняем структуру класса окна
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
		   MessageBox(NULL,TEXT("Ошибка регистрации класса окна!"),TEXT("Ошибка"),MB_OK|MB_ICONERROR);
		   return FALSE;
	   }
	   //2-ой способ подключения меню
	  hMenu = LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));

	   //создаём главное окно
	   hWnd=CreateWindowEx(NULL,g_lpszClassName,
		   g_lpszAplicationTitle,
		   WS_OVERLAPPEDWINDOW,
		   600,
		   100,
		   600,
		   400,
		   NULL,
		   hMenu,//указываем меню 2-й способ
		   hInstance,
		   NULL);
	   //проверка создания главного окна
	  if(!hWnd)
	   {
		   MessageBox(NULL,TEXT("Окно не создано!"),TEXT("Ошибка"),MB_OK|MB_ICONERROR);
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
//-----------------------------оконная процедура главного окна--------------------------------------
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
////=====================================функция обработки команд меню==================================
void WndProc_OnCommand(HWND hWnd,int wmld,HWND,UINT)
{	
	static HANDLE hFile;        // Для дескриптора объекта "файл"
	static HANDLE hFileMap;     // Для дескриптора объекта 'проецируемый файл'
	static LPVOID lpvFile;      // Для адреса региона в адресном пространстве
  
	LPSTR  lpchANSI;     // Указатель на ANSI строку
 
	 static DWORD  dwFileSize;   // Для значения размера файла 
	
 	
	STARTUPINFOA si={0};    // Структуры для функции
	PROCESS_INFORMATION pi;// CreateProcess 

	char * fileName = new char [1000];			//имя файла
	char * fileString = new char [1000];		//текст из файла

	char * addString = new char [100];
 
	switch(wmld)
	{	
		case IDM_OPEN:
			{
					//получение адреса идентификатора по имени
					loadFile(fileString,fileName);
					 FileName = fileName;
					 FileString = fileString;
					  if (!CopyFileA(FileName, FILENAME, FALSE)) 
							{
							// Копироание не удалось
							MessageBox( NULL,"Ошибка создания копии файла!","SP_SR 2_5", MB_OK);
							break;
							}
					// Открываем файл для чтения и записи. Для этого создаем объект ядра "Файл".
							 hFile = CreateFileA(	
								 FILENAME,  // Указатель на строку с имененм файла
								  GENERIC_WRITE | GENERIC_READ, // Требуемый режим доступа
											0,   //  Режим разделения,0 - безраздельный доступ к файлу.       
								  NULL,// LPSECURITY_ATTRIBUTES=0 - объект не наследуемый.
								  OPEN_EXISTING,//Если файл не существует, то возвратить ошибку.
								  FILE_ATTRIBUTE_NORMAL,//Оставить атрибуты как есть 
								  NULL //Не давать имя объекту ядра "Файл"
								  );
								 dwFileSize = GetFileSize(hFile, NULL);
								 if (hFile == INVALID_HANDLE_VALUE) 
									{  // Открыть файл не удалось
									MessageBox(	NULL, "Ошибка открытия файла.", "SP_SR 2_5", MB_OK);
									break;
									}
							ModifyMenu(hMenu,IDM_OPEN,MF_GRAYED|MF_STRING,IDM_OPEN,TEXT("Выбрать файл"));// изменить меню
							ModifyMenu(hMenu,IDM_PROECTION,MF_ENABLED|MF_STRING,IDM_PROECTION,TEXT("Проецировать файл"));// изменить меню
							ModifyMenu(hMenu,IDM_RESULT,MF_GRAYED|MF_STRING,IDM_RESULT,TEXT("Показать результат"));// изменить меню
					
			}  
        break;
		case IDM_PROECTION:
			{
// Узнаем размер файла. Второй параметр NULL, так как предполагается,
  // что файл меньше 4 Гб.
			
	
	// Создаем объект "проецируемый файл". 
	hFileMap = CreateFileMapping(	
                    hFile,  // Дескриптор проецирумого объекта "Файл" 
                    NULL,   // 
                    PAGE_READWRITE, // Атрибуты защиты страниц 
									  0,  // LPSECURITY_ATTRIBUTES
                   0,   //Младшие 32 разряда
                    NULL  // и старшие 32 разряда размера файла.
                    );
	if (hFileMap == NULL) 
		{	// Открыть объект "проецируемый файл" не удалось
		MessageBox(	NULL,"Ошибка открытия проецируемого файла.","SP_SR 2_5",    MB_OK);
		}
	else
	{
		MessageBox(	NULL,"Создан объект - проецируемый файл.","SP_SR 2_5",    MB_OK);
		ModifyMenu(hMenu,IDM_SHOW,MF_ENABLED|MF_STRING,IDM_SHOW,TEXT("Отображение на адресное пространство"));// изменить меню
		ModifyMenu(hMenu,IDM_PROECTION,MF_GRAYED|MF_STRING,IDM_PROECTION,TEXT("Проецировать файл"));// изменить меню
	}
			}
        break;
		case IDM_SHOW:
			{
			// Открываем отображение файла на виртуальное адресное пространство и
  // получаем адрес, начиная с которого располагается образ файла в памяти.
  
  lpvFile = MapViewOfFile(
                hFileMap, // Дескриптор объекта "Проецируемый файл" 
                FILE_MAP_WRITE, // Режим доступа
                0, // Старшие 32 разряда смещения от начала файла, 
                0, // младшие 32 разряда смещения от начала файла
                0  // и количество отображаемых байт. 0 - весь файл.
                );

	if (lpvFile == NULL)
		{// Спроецировать оконное представление файла не удалось
		MessageBox(	NULL, "Спроецировать оконное представление файла не удалось!", "SP_SR 2_5", MB_OK);
		CloseHandle (hFileMap);// Перед выходом закрываем открытые объекты
		CloseHandle(hFile);
		break;
		}

		lpchANSI = (LPSTR) lpvFile;
		lpchANSI[dwFileSize] = 0;
		
 	if (strlen(FILENAME)!=0) //если загрузка прошла успешно
		{
			g_count = countSymbols(symbols,FileString); //подсчитываем количество слов
			sprintf(addString,"\nКоличество слов на гласную:%d\n",g_count); 
		
			lstrcpy(&lpchANSI[dwFileSize],addString);
			dwFileSize+=lstrlen(addString);
			lpchANSI[dwFileSize] = 0;
		
		}
		else
			MessageBox(hWnd, TEXT("Ошибка обработки файла!"),TEXT(""),MB_OK|MB_ICONERROR);
			MessageBox(	NULL, "Создано отображение файла!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_SHOW,MF_GRAYED|MF_STRING,IDM_SHOW,TEXT("Отображение на адресное пространство"));// изменить меню
				ModifyMenu(hMenu,IDM_CLOSESHOW,MF_ENABLED|MF_STRING,IDM_CLOSESHOW,TEXT("Закрытие отображения"));// изменить меню
		}
        break;
		case IDM_CLOSESHOW:
			{
			 // Закрываем представление файла в окне адресного пространства
				UnmapViewOfFile(lpvFile);
				MessageBox(	NULL, "Представление файла закрыто!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_CLOSEPROECTION,MF_ENABLED|MF_STRING,IDM_CLOSEPROECTION,TEXT("Закрыть проекцию"));// изменить меню
				ModifyMenu(hMenu,IDM_CLOSESHOW,MF_GRAYED|MF_STRING,IDM_CLOSESHOW,TEXT("Закрытие отображения"));// изменить меню
			}
        break;
		case IDM_CLOSEPROECTION:
			{
		 // Уменьшаем счетчик ссылок на объект ядра "Проецируемый файл"
				CloseHandle(hFileMap);	
				MessageBox(	NULL, "Уменьшили счетчик ссылок на объект ядра - Проецируемый файл!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_CLOSEPROECTION,MF_GRAYED|MF_STRING,IDM_CLOSEPROECTION,TEXT("Закрыть проекцию"));// изменить меню
				ModifyMenu(hMenu,IDM_CLOSEFILE,MF_ENABLED|MF_STRING,IDM_CLOSEFILE,TEXT("Закрыть файл"));// изменить меню
			}
        break;
		case IDM_CLOSEFILE:
			{
		 		// Удаляем добавленный ранее концевой нулевой байт.Для этого
				// перемещаем указатель файла в конец на нулевой байт,
				// а затем даем команду установить в этом месте конец файла
				// ядра "Проецируемый файл"
				 SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
				 SetEndOfFile(hFile);
				CloseHandle(hFile);// Уменьшаем счетчик ссылок на объект ядра "Файл"
				MessageBox(	NULL," Уменьшаем счетчик ссылок на объект ядра - Файл!", "SP_SR 2_5", MB_OK);
				ModifyMenu(hMenu,IDM_RESULT,MF_ENABLED|MF_STRING,IDM_RESULT,TEXT("Показать результат"));// изменить меню
				ModifyMenu(hMenu,IDM_CLOSEFILE,MF_GRAYED|MF_STRING,IDM_CLOSEFILE,TEXT("Закрыть файл"));// изменить меню
			}
        break;
		case IDM_RESULT:
			{
			// Запускаем NOTEPAD и загружаем в него созданный файл,
			 // чтобы увидеть плоды своих трудов
				si.cb = sizeof (si);// Заполняем поле размера структуры si
				si.wShowWindow = SW_SHOW;// Задаем режим показа окна NOTEPAD
				si.dwFlags = STARTF_USESHOWWINDOW;// Устанавливаем флаг - учитывать
                 // значение поля wShowWindow
				TCHAR cmdpar[260];
				wsprintf(cmdpar,"notepad.exe %s", FILENAME);
				if( CreateProcessA(	NULL,cmdpar, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))				 
				{
					// Если процесс создан, освобождаем 
					// дескрипторы потока и процесса	
					CloseHandle(pi.hThread);
					CloseHandle(pi.hProcess);
					ModifyMenu(hMenu,IDM_OPEN,MF_ENABLED|MF_STRING,IDM_OPEN,TEXT("Выбрать файл"));// изменить меню
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

//================================функция отрисовки окна=============================================
void WndProc_OnPaint(HWND hWnd)
{
	HDC hDC;
	PAINTSTRUCT ps;
	hDC=BeginPaint(hWnd,&ps);
	EndPaint(hWnd,&ps);	
}
//======================================функция закрытия окна==========================================
void WndProc_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
	FORWARD_WM_CLOSE(hWnd,DefWindowProc);
}
//===============================функция при разрушении окна================================
void WndProc_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
	FORWARD_WM_DESTROY(hWnd,DefWindowProc);
}




