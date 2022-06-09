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
	li.QuadPart=-(1*SleepTime);//óñòàíàâëèâàåì âðåìÿ ïåðâîãî çàïóñêà
	hTimer=CreateWaitableTimer(NULL, FALSE, NULL); //ñîçäà¸ì òàéìåð
	if(SetWaitableTimer(hTimer,&li,1000,NULL, NULL, FALSE))	//óñòàíàâëèâàåì òàéìåð è åñëè óäà÷íî, èä¸ì äàëüøå
	{
		STARTUPINFO si;	//äëÿ ãà÷àëà ïðîöåññà
		ZeroMemory(&si,sizeof(STARTUPINFO));
		si.cb=sizeof(STARTUPINFO);
		while(nStart<=10)
		{
					WaitForSingleObject(hTimer, INFINITE); //æä¸ì ñèãíàë îò òàéìåðà- ïåðâûé ÷åðåç 15 ñåê è çàòåì ÷åðåç 1 ñåê
					if(nStart==1)  //ïðè ïåðâîì çàïóñêå
					{	//ñîçäàåì ïðîöåññ
						fNote=CreateProcess(L"c:\\Windows\\System32\\NOTEPAD.EXE", NULL , NULL, NULL, 0, 0,NULL, NULL, &si, &pi);
						if(!fNote) //åñëè íå ñîçäàëñÿ
							{
								MessageBox(NULL, L"Íå óäàëîñü çàïóñòèòü áëîêíîò",NULL, MB_OK);
								return;
							}
						Sleep(500);	 //îæèäàíèå, ïîêà èíèöèàëèçèðóåòñÿ îêíî
						hwnd=FindWindow(NULL, L"Áåçûìÿííûé - Áëîêíîò");//íàõîäèì îêíî áëîêíîòà
						if(hwnd==NULL) //åñëè íå ñîçäàëîñü
							{
								MessageBox(NULL, L"Íå óäàëîñü îïðåäåëèòü áëîêíîò",NULL, MB_OK);
								return;
							}
						wsprintf(Buffer,TEXT("Çàïóñê %d"),nStart);
						SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)Buffer);//â çàãîëîâêå óñòàíàâëèâàåì çàïóñê ¹1
					} //êîíåö if
					else
					{
						wsprintf(Buffer,TEXT("Çàïóñê %d"),nStart);
						SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)Buffer);//â çàãîëîâêå óñòàíàâëèâàåì çàïóñê ¹1
					}//Êîíåö else
			nStart++;
		}//êîíåö while
	}//êîíåö if
TerminateProcess(pi.hProcess, 0);//çàêàí÷èâàåì ïðîöåññ ÷åðåç 10 öèêëîâ
printf("\nPress any key to exit\n");
getch();

	

}
