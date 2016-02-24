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
	li.QuadPart=-(1*SleepTime);//������������� ����� ������� �������
	hTimer=CreateWaitableTimer(NULL, FALSE, NULL); //������ ������
	if(SetWaitableTimer(hTimer,&li,1000,NULL, NULL, FALSE))	//������������� ������ � ���� ������, ��� ������
	{
		STARTUPINFO si;	//��� ������ ��������
		ZeroMemory(&si,sizeof(STARTUPINFO));
		si.cb=sizeof(STARTUPINFO);
		while(nStart<=10)
		{
					WaitForSingleObject(hTimer, INFINITE); //��� ������ �� �������- ������ ����� 15 ��� � ����� ����� 1 ���
					if(nStart==1)  //��� ������ �������
					{	//������� �������
						fNote=CreateProcess(L"c:\\Windows\\System32\\NOTEPAD.EXE", NULL , NULL, NULL, 0, 0,NULL, NULL, &si, &pi);
						if(!fNote) //���� �� ��������
							{
								MessageBox(NULL, L"�� ������� ��������� �������",NULL, MB_OK);
								return;
							}
						Sleep(500);	 //��������, ���� ���������������� ����
						hwnd=FindWindow(NULL, L"���������� - �������");//������� ���� ��������
						if(hwnd==NULL) //���� �� ���������
							{
								MessageBox(NULL, L"�� ������� ���������� �������",NULL, MB_OK);
								return;
							}
						wsprintf(Buffer,TEXT("������ %d"),nStart);
						SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)Buffer);//� ��������� ������������� ������ �1
					} //����� if
					else
					{
						wsprintf(Buffer,TEXT("������ %d"),nStart);
						SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)Buffer);//� ��������� ������������� ������ �1
					}//����� else
			nStart++;
		}//����� while
	}//����� if
TerminateProcess(pi.hProcess, 0);//����������� ������� ����� 10 ������
printf("\nPress any key to exit\n");
getch();

	

}