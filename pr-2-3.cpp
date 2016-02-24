#include <conio.h>
#include <stdio.h>
#include <Windows.h>

#define SleepTime 150000000
int nStart=1;
HANDLE hTimer;

void main()
{
	HWND hwnd;
	BOOL fNote;
	TCHAR Buffer[100];
	LARGE_INTEGER li;
	PROCESS_INFORMATION pi;

	printf("Lab 2-3 Petrashevich Nikolay gr. 40332 (timer)\nPlease wait for 15 seconds");
	li.QuadPart=-(1*SleepTime);//устанавливаем время первого запуска
	hTimer=CreateWaitableTimer(NULL, FALSE, NULL); //создаём таймер
	if(SetWaitableTimer(hTimer,&li,1000,NULL, NULL, FALSE))	//устанавливаем таймер и если удачно, идём дальше
	{
		STARTUPINFO si;	//для гачала процесса
		ZeroMemory(&si,sizeof(STARTUPINFO));
		si.cb=sizeof(STARTUPINFO);
		while(nStart<=10)
		{
					WaitForSingleObject(hTimer, INFINITE); //ждём сигнал от таймера- первый через 15 сек и затем через 1 сек
					if(nStart==1)  //при первом запуске
					{	//создаем процесс
						fNote=CreateProcess(L"c:\\Windows\\System32\\NOTEPAD.EXE", NULL , NULL, NULL, 0, 0,NULL, NULL, &si, &pi);
						if(!fNote) //если не создался
							{
								MessageBox(NULL, L"Не удалось запустить блокнот",NULL, MB_OK);
								return;
							}
						Sleep(500);	 //ожидание, пока инициализируется окно
						hwnd=FindWindow(NULL, L"Безымянный - Блокнот");//находим окно блокнота
						if(hwnd==NULL) //если не создалось
							{
								MessageBox(NULL, L"Не удалось определить блокнот",NULL, MB_OK);
								return;
							}
						wsprintf(Buffer,TEXT("Запуск %d"),nStart);
						SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)Buffer);//в заголовке устанавливаем запуск №1
					} //конец if
					else
					{
						wsprintf(Buffer,TEXT("Запуск %d"),nStart);
						SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)Buffer);//в заголовке устанавливаем запуск №1
					}//Конец else
			nStart++;
		}//конец while
	}//конец if
TerminateProcess(pi.hProcess, 0);//заканчиваем процесс через 10 циклов
printf("\nPress any key to exit\n");
getch();

	

}