
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


//ôóíêöèÿ ÷èòàåò ôàéë è âîçâðàùàåò string - ïðîèòàííóþ ñòðîêó, fileName - èìÿ ôàéëà êîòîðîå ÷èòàëè 
void loadFile(char * string, char * fileName)
{
		OPENFILENAME ofn;   // ñòðóêòóðà íóæíà äëÿ îòêðûòèÿ äèàëîêà îòêðûòèÿ ôàéëà
		BOOL fRet ;
		HANDLE hFile;
		string[0] = '\0';
		char * buffer = new char[1000]; //äëÿ ôîðìèðîâàíèé ñîîáùåíèé ñ îøèáêàìè 
			//Èíèöàëèçàöèÿ OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;  // hwnd – äåñêðèïòîð îêíà–âëâäåëüöà
		ofn.lpstrFile = fileName;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = MAX_BYTES;
		// Ôîðìèðîâàíèå ìàññèâà ñòðîê øàáëîíîâ ôèëüòðà
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1; // Èíäåêñ äëÿ òåêóùåãî øàáëîíà ôèëüòðà
		ofn.lpstrFileTitle = NULL; // Áåç çàãîëîâêà
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL; // Â êà÷åñòâå íà÷àëüíîãî òåêóùèé êàòàëîã
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		// Îòîáðàæåíèå äèàëîãîâîãî îêíà
		fRet = GetOpenFileName(&ofn);
		if (fRet == FALSE) 
		{
			DWORD error = CommDlgExtendedError();
			if (error!=0) //åñëè áûëà îøèáêà à íå ïîëüçîâàòåëü íàæàë cancel
			{
				sprintf(buffer,"Îøèáêà â äèàëîãîâîì îêíå ¹: 0x%x", error);
				MessageBox(NULL,buffer,"Îøèáêà!",MB_OK);
			}
			return;//îøèáêà â äàëîãå
		}

		//îòêðûâàåì ôàéë 
		hFile = CreateFile(ofn.lpstrFile, GENERIC_READ,
	        0, (LPSECURITY_ATTRIBUTES) NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);

		//Ïðîâåðêà êîððåêòíîñòè îòêðûòèÿ ôàéëà
		if(hFile == INVALID_HANDLE_VALUE) 
		{
			MessageBox(NULL,"Ôàéë íå Çàãðóæåí!","Îøèáêà!",MB_OK);
			return;
		}

		//×òåíèå èç ôàéëà â áóôåð
		DWORD dwNumbOfBytes;
		ReadFile(hFile, string, MAX_BYTES, &dwNumbOfBytes,NULL);
		string[dwNumbOfBytes] = '\0';

		if(hFile)
		{
			CloseHandle(hFile);
		}
}

//ïîäñ÷èòûâàåò êîëè÷åñâî ñëîâ, íà÷èíàþùèõñÿ íà ãëàñíóþ
int  countSymbols(char * symbols, char * string)
{
	int count = 0;

	if (string == NULL) //ïðîâåðêà âõîäíûõ ïàðàìåòðîâ
		return 0;
	//äëÿ îïðåäåëåíèÿ ïåðâîé ãëàññíîé â òåêñòå
	if(strchr(symbols,string[0])>0)
	{
		count++;
	}

	for (int i=0; i<(strlen(string)-1); i++) // èäåì ïî ñòðîêå
	{
		if (string[i]==' ') // ïðîâåðÿåì êàæäûé ñèìâîë ñîäåðæèòñÿ îí â ñïèñêå ñèìâîëîâ èëè íåò
		{
			if(strchr(symbols,string[i+1])>0)
			{
			count ++; // åñëè ñîäåðæèòüñÿ òî óâåëè÷èâàåì ñ÷åò÷èê
			}
		}
	}

	return count;
}
