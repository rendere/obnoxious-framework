#include "Utils.h"
#include "../../api/fastcall.h"
#include <vector>
#include <Psapi.h>
#include <cmath>
#include <cstdint>
#include <tuple>
#pragma comment(lib,"psapi")

static const DWORD dwModuleDelay = 100;
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace Utils
{
	/* Wait dwMsec Load Module */

	bool IsModuleLoad(PCHAR szModule, DWORD dwMsec)
	{
		HMODULE hModule = FastCall::G().t_GetModuleHandleA(szModule);
		if (!hModule)
		{
			DWORD dwMsecFind = 0;

			while (!hModule)
			{
				if (dwMsecFind == dwMsec)
					return false;

				hModule = FastCall::G().t_GetModuleHandleA(szModule);

				HANDLE hEvent = FastCall::G().t_CreateEventA(0, true, false, 0);

				if (!hEvent)
					return false;

				FastCall::G().t_WaitForSingleObject(hEvent, dwModuleDelay);
				FastCall::G().t_CloseHandle(hEvent);

				dwMsecFind += dwModuleDelay;
			}
		}

		return true;
	}

	/* Get Module File Path */

	string GetModuleFilePath(HMODULE hModule)
	{
		string ModuleName = "";
		char szFileName[MAX_PATH] = { 0 };

		if (FastCall::G().t_GetModuleFileNameA(hModule, szFileName, MAX_PATH))
			ModuleName = szFileName;
		 

		return ModuleName;
	}

	/* Get Module Dir */

	string GetModuleBaseDir(HMODULE hModule)
	{
		string ModulePath = GetModuleFilePath(hModule);
		return ModulePath.substr(0, ModulePath.find_last_of("\\/"));
	}

	/* IDA Style 00 FF ?? */

	DWORD PatternScan(std::string moduleName, std::string Mask)
	{
		const char* pat = Mask.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)FastCall::G().t_GetModuleHandleA(moduleName.c_str());
		MODULEINFO miModInfo; FastCall::G().t_GetModuleInformation(FastCall::G().t_GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;

		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2; //one ?
			}
			else
			{
				pat = Mask.c_str();
				firstMatch = 0;
			}
		}

		return NULL;
	}

	/* IDA Style \xE8????\x8B */

	std::uintptr_t FindPattern(const wchar_t* module, const char* pattern)
	{
		static auto id = 0;
		++id;

		if (HMODULE moduleHandle = FastCall::G().t_GetModuleHandleW(module))
		{
			MODULEINFO moduleInfo; FastCall::G().t_GetModuleInformation(FastCall::G().t_GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(moduleInfo));

			auto start = static_cast<const char*>(moduleInfo.lpBaseOfDll);
			const auto end = start + moduleInfo.SizeOfImage;

			auto first = start;
			auto second = pattern;

			while (first < end && *second) 
			{
				if (*first == *second || *second == '?')
				{
					++first;
					++second;
				}
				else 
				{
					first = ++start;
					second = pattern;
				}
			}

			if (!*second)
				return reinterpret_cast<std::uintptr_t>(start);
		}
		FastCall::G().t_MessageBoxA(NULL, (__xor("Failed to find pattern #") + std::to_string(id) + '!').c_str(), __xor("obnoxious"), MB_OK | MB_ICONWARNING);
		return 0;
	}
}



























































