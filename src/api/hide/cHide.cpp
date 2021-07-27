#include "cHide.h"
cHideClass pHideMe;

int cHideClass::_atoi(const char *s)
{
	int z = 0, n = 0;
	while (isspace(*s)) s++;
	if (*s == '-') { z = 1; s++; }
	else if (*s == '+') s++;
	while (isdigit(*s)) n = 10 * n + *s++ - '0';
	 
	return (z ? -n : n);
}

inline char * cHideClass::_strstr(const char *source, const char *word)
{
	const char *bp = word;
	const char *back_pos;
	while (*source != 0 && source != 0 && word != 0)
	{
		back_pos = source;
		while (toupper(*back_pos++) == toupper(*word++))
		{
			if (*word == 0)
			{
				return (char*)(back_pos - strlen(bp));
			}
		}
		++source;
		word = bp;
	}
	 
	return 0;
}

std::wstring cHideClass::UTF8ToWstring(const std::string& str)
{
	return AnsiToWstring(str, CP_UTF8);
}

std::wstring cHideClass::AnsiToWstring(const std::string& input, DWORD locale /*= CP_ACP*/)
{
	wchar_t buf[8192] = { 0 };
	MultiByteToWideChar(locale, 0, input.c_str(), (int)input.length(), buf, ARRAYSIZE(buf));
	 
	return buf;
}

int cHideClass::str_len(const char *str)
{
	int n = 0;
	while (*str++)
		n++; // ������� ������� ��� ��������� ����
	return n;
}

int cHideClass::str_cmp(const char* str1, const char* str2)
{
	int result = 0;
	int str1_len = str_len(str1);
	int str2_len = str_len(str2);
	while (*str1 || *str2)
	{
		if (*str1 > *str2)
		{
			result = 1;
			break;
		}
		else if (*str1 < *str2)
		{
			result = -1;
			break;
		}
		str1++;
		str2++;
	}
	 
	if (!result && (str1_len < str2_len))
		result = 1;
	else if (!result && (str1_len > str2_len))
		result = -1;
	return result;
}

HMODULE cHideClass::_GetModuleHandle(const wchar_t* szModule)//GetModuleHandle
{
	LDR_MODULE* pModule;

	_asm
	{
		MOV EAX, FS:[0x18];    // TEB (Thread Environment Block)
		MOV EAX, [EAX + 0x30]; // PEB (Process Environment Block)
		MOV EAX, [EAX + 0x0C]; // pModule
		MOV EAX, [EAX + 0x0C]; // pModule->InLoadOrderModuleList.Flink
		MOV pModule, EAX;
	}

	while (pModule->BaseAddress)
	{
		if (_wcsicmp(pModule->BaseDllName.Buffer, szModule) == 0)
		{
			return (HMODULE)pModule->BaseAddress;
		}
		pModule = (LDR_MODULE*)pModule->InLoadOrderModuleList.Flink; // grab the next module in the list
	}

	 
	return NULL;
}
FARPROC  cHideClass::_GetProcAddress(HMODULE hModule, const char* lpProcName)
{
	ULONG PE;
	PIMAGE_EXPORT_DIRECTORY ED;
	PULONG NamePointerRVA;
	PUSHORT OrdinalTableRVA;
	PULONG AddressTableRVA;

	ULONG ret = 0;
	USHORT hint = 0;
	USHORT index;
	char * name;
	ULONG addr;
	ULONG CNT_FUNC;

	if ((ULONG)lpProcName <= 0xFFFF)// ���� ������ �� ��������
	{
		hint = (USHORT)lpProcName; // ������� ��� �������
	}

	if (hModule) // ���� ������ ������ ������ �������
	{
		PE = *(ULONG*)((ULONG)hModule + 0x3C) + (ULONG)hModule;// ����� PE ���������
		ED = (PIMAGE_EXPORT_DIRECTORY)(*(ULONG*)((ULONG)PE + 0x78) + (ULONG)hModule); // ����� ������� ��������

		NamePointerRVA = (ULONG*)(ED->AddressOfNames + (ULONG)hModule); // ����� ������� ����
		OrdinalTableRVA = (USHORT*)(ED->AddressOfNameOrdinals + (ULONG)hModule); // ����� ������� ���������
		AddressTableRVA = (ULONG*)(ED->AddressOfFunctions + (ULONG)hModule); // ����� ������� �������

																			 //	  ��������� ���������� �������� - ���-�� �������
		if (ED->NumberOfNames > ED->NumberOfFunctions)
		{
			CNT_FUNC = ED->NumberOfNames;
		}
		else
		{
			CNT_FUNC = ED->NumberOfFunctions;
		}

		//��������� �� ���� ��������
		for (USHORT x = 0; x < CNT_FUNC; x++)
		{
			if (x < ED->NumberOfFunctions) // ���� ���� ��� � �������
			{
				name = (char*)(NamePointerRVA[x] + (ULONG)hModule); // �������� ���
				index = OrdinalTableRVA[x]; // �������� �������
			}
			else // ���� ����� ���
			{
				name = 0; // ����� ���
				index = x; // ������� = ������� �������
			}

			//��������� ����� ������� 
			addr = AddressTableRVA[index] + (ULONG)hModule;
			if ((hint == index + ED->Base) || // ���� ��� ��� �������
				(name && !str_cmp(name, lpProcName))) // ���� ���� ��� � ��� ����
			{
				ret = addr; // ����� �����
				break; // ��������� ����� ��������
			}
		}
	}

	 
	return (FARPROC)ret; // ������ ����� 
}

PVOID cHideClass::_GetLibraryProcAddress(const char* LibraryName, const char *ProcName)
{
	return this->_GetProcAddress(this->_GetModuleHandle(UTF8ToWstring(LibraryName).c_str()), ProcName);
}

#pragma region USER32
BOOL cHideClass::_SetRect(_Out_ LPRECT lprc, _In_ int xLeft, _In_ int yTop, _In_ int xRight, _In_ int yBottom)
{
	nSetRect nFunc;
	DWORD Address = (DWORD)this->_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(), Funcname[2].c_str());
	nFunc = (nSetRect)(Address);
	return nFunc(lprc, xLeft, yTop, xRight, yBottom);
}

int cHideClass::_MessageBox(HWND hWnd, LPCSTR MbString, LPCSTR lpCaption, UINT uType)
{
	nMessageBoxTimeoutA pFunc = (nMessageBoxTimeoutA)_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(),
		Funcname[3].c_str());
	return pFunc(hWnd, MbString, lpCaption, uType, 0, -1);
}

BOOL cHideClass::_GetCursorPos(LPPOINT lpPoint)
{
	nGetCursorPos nGetCursorPosA;
	DWORD Address = (DWORD)_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(), Funcname[4].c_str());
	nGetCursorPosA = (nGetCursorPos)(Address);
	return nGetCursorPosA(lpPoint);
}

BOOL cHideClass::_ScreenToClient(HWND hWnd, LPPOINT lpPoint)
{
	nScreenToClient nScreenToClientA;
	DWORD Address = (DWORD)_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(), Funcname[5].c_str());
	nScreenToClientA = (nScreenToClient)(Address);
	return nScreenToClientA(hWnd, lpPoint);
}

HWND cHideClass::_GetForegroundWindow()
{
	nGetForegroundWindow nGetForegroundWindowA;
	DWORD Address = (DWORD)_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(), Funcname[6].c_str());
	nGetForegroundWindowA = (nGetForegroundWindow)(Address);
	return nGetForegroundWindowA();
}

SHORT cHideClass::_GetKeyState(int nVirtKey)
{
	nGetKeyState nGetKeyStateA;
	DWORD Address = (DWORD)_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(), Funcname[7].c_str());
	nGetKeyStateA = (nGetKeyState)(Address);
	return nGetKeyStateA(nVirtKey);
}

SHORT cHideClass::_GetAsyncKeyState(int vKey)
{
	nGetAsyncKeyState nGetAsyncKeyStateA;
	DWORD Address = (DWORD)_GetLibraryProcAddress(ModName[ModName_text::USER32].c_str(), Funcname[8].c_str());
	nGetAsyncKeyStateA = (nGetAsyncKeyState)(Address);
	return nGetAsyncKeyStateA(vKey);
}

#pragma endregion

#pragma region D3DX9_43
HRESULT cHideClass::_D3DXCreateFont(LPDIRECT3DDEVICE9 pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCSTR pFaceName, LPD3DXFONT * ppFont)
{
	nD3DXCreateFont nFunc;
	LoadLibrary(/*__xor("D3DX9_43.dll")*/ModName[0].c_str());
	DWORD Address = (DWORD)this->_GetLibraryProcAddress(ModName[ModName_text::D3DX9_43].c_str(),
		Funcname[0].c_str());//D3DXCreateFontA
	nFunc = (nD3DXCreateFont)(Address);
	 
	return nFunc(pDevice, Height, Width, Weight, MipLevels, Italic, CharSet, OutputPrecision, Quality, PitchAndFamily, pFaceName, ppFont);
}

HRESULT cHideClass::_D3DXCreateLine(LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE* ppLine)
{
	nD3DXCreateLine nFunc;
	LoadLibrary(/*__xor("D3DX9_43.dll")*/ModName[0].c_str());
	DWORD Address = (DWORD)this->_GetLibraryProcAddress(ModName[ModName_text::D3DX9_43].c_str(),
		Funcname[1].c_str());//D3DXCreateFontA
	nFunc = (nD3DXCreateLine)(Address);
	 
	return nFunc(pDevice, ppLine);
}
#pragma endregion

HANDLE cHideClass::NtCreateThreadEx(void* InRemoteThreadStart, void* InRemoteCallback)
{
	NtCreateThreadEx_PROC* VistaCreateThread = (NtCreateThreadEx_PROC*)_GetLibraryProcAddress(ModName[ModName_text::ntdll].c_str(),
		Funcname[10].c_str());
	if (VistaCreateThread == NULL)return NULL;

	HANDLE hRemoteThread = NULL;
	HRESULT hRes = 0;

	if (!SUCCEEDED(hRes = VistaCreateThread(&hRemoteThread, 0x1FFFFF, 0, (HANDLE)-1, (LPTHREAD_START_ROUTINE)InRemoteThreadStart, InRemoteCallback, FALSE, 0, 0, 0, 0)))
		return NULL;

	return hRemoteThread;
}

void cHideClass::_ExitProcess(UINT uExitCode)
{
	nExitProcess nFunc;
	DWORD Address = (DWORD)_GetLibraryProcAddress(ModName[ModName_text::ntdll].c_str(), Funcname[9].c_str());
	nFunc = (nExitProcess)(Address);
	 
	return nFunc(uExitCode);
}

bool CreateThread_::HideThread(HANDLE hThread)
{
	typedef NTSTATUS(NTAPI *pNtSetInformationThread)
		(HANDLE, UINT, PVOID, ULONG);
	NTSTATUS Status;

	pNtSetInformationThread NtSIT = (pNtSetInformationThread)pHideMe._GetLibraryProcAddress(/*__xor("ntdll.dll")*/ModName[ModName_text::ntdll].c_str(), __xor("NtSetInformationThread"));

	if (NtSIT == NULL)
		return false;

	if (hThread == NULL)
		Status = NtSIT(GetCurrentThread(),
			0x11,
			0, 0);
	else
		Status = NtSIT(hThread, 0x11, 0, 0);

	if (Status != 0x00000000)
		return false;
	else
		return true;
}

CreateThread_::CreateThread_(void*func, HINSTANCE hInst)
{
	typedef BOOL(WINAPI* nCloseHandle)(HANDLE);
	nCloseHandle oCloseHandle = (nCloseHandle)pHideMe._GetLibraryProcAddress(/*__xor("Kernel32.dll")*/ModName[ModName_text::kernel32].c_str(), __xor("CloseHandle"));
	if ((hHandle = pHideMe.NtCreateThreadEx(func, hInst)))
	{
		if (!HideThread(hHandle))
		{
			TerminateThread(hHandle, 0);
			return;
		}
		oCloseHandle(hHandle);
		return;
	}
}




























































