
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include "SR5.h"


#define SR5_EXPORTS
#define MAX_BYTES 1000

#pragma comment(linker, "/SECTION:.SHARED,RWS")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(NULL,"Hi",NULL,MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
		
	}
	return TRUE;
}


//������� ������ ���� � ���������� string - ���������� ������, fileName - ��� ����� ������� ������ 
void loadFile(char * string, char * fileName)
{
		OPENFILENAME ofn;   // ��������� ����� ��� �������� ������� �������� �����
		BOOL fRet ;
		HANDLE hFile;
		string[0] = '\0';
		char * buffer = new char[1000]; //��� ������������ ��������� � �������� 
			//������������ OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;  // hwnd � ���������� ��������������
		ofn.lpstrFile = fileName;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = MAX_BYTES;
		// ������������ ������� ����� �������� �������
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1; // ������ ��� �������� ������� �������
		ofn.lpstrFileTitle = NULL; // ��� ���������
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL; // � �������� ���������� ������� �������
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		// ����������� ����������� ����
		fRet = GetOpenFileName(&ofn);
		if (fRet == FALSE) 
		{
			DWORD error = CommDlgExtendedError();
			if (error!=0) //���� ���� ������ � �� ������������ ����� cancel
			{
				sprintf(buffer,"������ � ���������� ���� �: 0x%x", error);
				MessageBox(NULL,buffer,"������!",MB_OK);
			}
			return;//������ � ������
		}

		//��������� ���� 
		hFile = CreateFile(ofn.lpstrFile, GENERIC_READ,
	        0, (LPSECURITY_ATTRIBUTES) NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);

		//�������� ������������ �������� �����
		if(hFile == INVALID_HANDLE_VALUE) 
		{
			MessageBox(NULL,"���� �� ��������!","������!",MB_OK);
			return;
		}

		//������ �� ����� � �����
		DWORD dwNumbOfBytes;
		ReadFile(hFile, string, MAX_BYTES, &dwNumbOfBytes,NULL);
		string[dwNumbOfBytes] = '\0';

		if(hFile)
		{
			CloseHandle(hFile);
		}
}

//������������ ��������� ����, ������������ �� �������
int  countSymbols(char * symbols, char * string)
{
	int count = 0;

	if (string == NULL) //�������� ������� ����������
		return 0;
	//��� ����������� ������ �������� � ������
	if(strchr(symbols,string[0])>0)
	{
		count++;
	}

	for (int i=0; i<(strlen(string)-1); i++) // ���� �� ������
	{
		if (string[i]==' ') // ��������� ������ ������ ���������� �� � ������ �������� ��� ���
		{
			if(strchr(symbols,string[i+1])>0)
			{
			count ++; // ���� ����������� �� ����������� �������
			}
		}
	}

	return count;
}
