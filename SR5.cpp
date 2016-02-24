
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


//функция читает файл и возвращает string - проитанную строку, fileName - имя файла которое читали 
void loadFile(char * string, char * fileName)
{
		OPENFILENAME ofn;   // структура нужна для открытия диалока открытия файла
		BOOL fRet ;
		HANDLE hFile;
		string[0] = '\0';
		char * buffer = new char[1000]; //для формирований сообщений с ошибками 
			//Иницализация OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;  // hwnd – дескриптор окна–влвдельца
		ofn.lpstrFile = fileName;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = MAX_BYTES;
		// Формирование массива строк шаблонов фильтра
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1; // Индекс для текущего шаблона фильтра
		ofn.lpstrFileTitle = NULL; // Без заголовка
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL; // В качестве начального текущий каталог
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		// Отображение диалогового окна
		fRet = GetOpenFileName(&ofn);
		if (fRet == FALSE) 
		{
			DWORD error = CommDlgExtendedError();
			if (error!=0) //если была ошибка а не пользователь нажал cancel
			{
				sprintf(buffer,"Ошибка в диалоговом окне №: 0x%x", error);
				MessageBox(NULL,buffer,"Ошибка!",MB_OK);
			}
			return;//ошибка в далоге
		}

		//открываем файл 
		hFile = CreateFile(ofn.lpstrFile, GENERIC_READ,
	        0, (LPSECURITY_ATTRIBUTES) NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);

		//Проверка корректности открытия файла
		if(hFile == INVALID_HANDLE_VALUE) 
		{
			MessageBox(NULL,"Файл не Загружен!","Ошибка!",MB_OK);
			return;
		}

		//Чтение из файла в буфер
		DWORD dwNumbOfBytes;
		ReadFile(hFile, string, MAX_BYTES, &dwNumbOfBytes,NULL);
		string[dwNumbOfBytes] = '\0';

		if(hFile)
		{
			CloseHandle(hFile);
		}
}

//подсчитывает количесво слов, начинающихся на гласную
int  countSymbols(char * symbols, char * string)
{
	int count = 0;

	if (string == NULL) //проверка входных параметров
		return 0;
	//для определения первой глассной в тексте
	if(strchr(symbols,string[0])>0)
	{
		count++;
	}

	for (int i=0; i<(strlen(string)-1); i++) // идем по строке
	{
		if (string[i]==' ') // проверяем каждый символ содержится он в списке символов или нет
		{
			if(strchr(symbols,string[i+1])>0)
			{
			count ++; // если содержиться то увеличиваем счетчик
			}
		}
	}

	return count;
}
