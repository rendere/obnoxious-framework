#include "SDK.h"
#include "../../Main.h"
template <typename T>
const auto relativeToAbsolute(int* address)
{
    return reinterpret_cast<T>(reinterpret_cast<char*>(address + 1) + *address);
}

namespace SDK

{
	KeyValues::KeyValues(std::string strKeyName, void* pUnknown1, HKeySymbol hCaseInsensitiveKeyName)
	{
		using KeyValuesConstructorFn = void(__thiscall*)(void*, const char*, void*, HKeySymbol);
		static KeyValuesConstructorFn oConstructor = reinterpret_cast<KeyValuesConstructorFn>(Utils::PatternScan("client.dll", "55 8B EC 56 8B F1 33 C0 8B 4D 0C 81")); // @xref: client.dll -> "OldParticleSystem_Destroy"
		oConstructor(this, strKeyName.c_str(), pUnknown1, hCaseInsensitiveKeyName);
	}

	KeyValues::~KeyValues()
	{
		using KeyValuesDestructorFn = void(__thiscall*)(void*, int);
		static KeyValuesDestructorFn oDestructor = reinterpret_cast<KeyValuesDestructorFn>(Utils::PatternScan("client.dll", "56 8B F1 E8 ? ? ? ? 8B 4E 14"));
		oDestructor(this, 1);
	}

	void* KeyValues::operator new(std::size_t nAllocSize)
	{
		// manually allocate memory, because game constructor doesn't call it automatically
		return I::KeyValuesSystem()->AllocKeyValuesMemory(nAllocSize);
	}

	void KeyValues::operator delete(void* pMemory)
	{
		// do nothing, because game destructor will automatically free memory
		// g_pInterfaces->m_pKeyValuesSystem->FreeKeyValuesMemory(pMemory);
		(void)pMemory;
	}

	const char* KeyValues::GetName()
	{
		return I::KeyValuesSystem()->GetStringForSymbol(this->uKeyNameCaseSensitive1 | (this->uKeyNameCaseSensitive2 << 8));
	}

	KeyValues* KeyValues::FromString(const char* szName, const char* szValue)
	{
		static auto oFromString = Utils::PatternScan("client.dll", "55 8B EC 81 EC ? ? ? ? 85 D2 53"); // @xref: "#empty#", "#int#"
		KeyValues* pKeyValues = nullptr;

		if (oFromString == 0U)
			return nullptr;

		__asm
		{
			push 0
			mov edx, szValue
			mov ecx, szName
			call oFromString
			add esp, 4
			mov pKeyValues, eax
		}

		return pKeyValues;
	}

	void KeyValues::LoadFromBuffer(char const* szResourceName, const char* szBuffer, void* pFileSystem, const char* szPathID, GetSymbolProcFn pfnEvaluateSymbolProc)
	{
		using LoadFromBufferFn = void(__thiscall*)(void*, const char*, const char*, void*, const char*, void*, void*);
		static auto oLoadFromBuffer = reinterpret_cast<LoadFromBufferFn>(Utils::PatternScan("client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89")); // @xref: "KeyValues::LoadFromBuffer(%s%s%s): Begin"
		assert(oLoadFromBuffer != nullptr);

		oLoadFromBuffer(this, szResourceName, szBuffer, pFileSystem, szPathID, pfnEvaluateSymbolProc, nullptr);
	}

	bool KeyValues::LoadFromFile(void* pFileSystem, const char* szResourceName, const char* szPathID, GetSymbolProcFn pfnEvaluateSymbolProc)
	{
		using LoadFromFileFn = bool(__thiscall*)(void*, void*, const char*, const char*, void*);
		static auto oLoadFromFile = reinterpret_cast<LoadFromFileFn>(Utils::PatternScan("client.dll", "55 8B EC 83 E4 F8 83 EC 14 53 56 8B 75 08 57 FF")); // @xref: "rb"
		assert(oLoadFromFile != nullptr);

		return oLoadFromFile(this, pFileSystem, szResourceName, szPathID, pfnEvaluateSymbolProc);
	}

	KeyValues* KeyValues::FindKey(const char* szKeyName, const bool bCreate)
	{
		using FindKeyFn = KeyValues * (__thiscall*)(void*, const char*, bool);
		static auto oFindKey = reinterpret_cast<FindKeyFn>(Utils::PatternScan("client.dll", "55 8B EC 83 EC 1C 53 8B D9 85 DB"));
		assert(oFindKey != nullptr);

		return oFindKey(this, szKeyName, bCreate);
	}

	int KeyValues::GetInt(const char* szKeyName, const int iDefaultValue)
	{
		KeyValues* pSubKey = this->FindKey(szKeyName, false);

		if (pSubKey == nullptr)
			return iDefaultValue;

		switch (pSubKey->iDataType)
		{
		case TYPE_STRING:
			return std::atoi(pSubKey->szValue);
		case TYPE_WSTRING:
			return _wtoi(pSubKey->wszValue);
		case TYPE_FLOAT:
			return static_cast<int>(pSubKey->flValue);
		case TYPE_UINT64:
			// can't convert, since it would lose data
			assert(false);
			return 0;
		default:
			break;
		}

		return pSubKey->iValue;
	}

	float KeyValues::GetFloat(const char* szKeyName, const float flDefaultValue)
	{
		KeyValues* pSubKey = this->FindKey(szKeyName, false);

		if (pSubKey == nullptr)
			return flDefaultValue;

		switch (pSubKey->iDataType)
		{
		case TYPE_STRING:
			return static_cast<float>(std::atof(pSubKey->szValue));
		case TYPE_WSTRING:
			return std::wcstof(pSubKey->wszValue, nullptr);
		case TYPE_FLOAT:
			return pSubKey->flValue;
		case TYPE_INT:
			return static_cast<float>(pSubKey->iValue);
		case TYPE_UINT64:
			return static_cast<float>(*reinterpret_cast<std::uint64_t*>(pSubKey->szValue));
		case TYPE_PTR:
		default:
			return 0.0f;
		}
	}

	const char* KeyValues::GetString(const char* szKeyName, const char* szDefaultValue)
	{
		using GetStringFn = const char* (__thiscall*)(void*, const char*, const char*);
		static auto oGetString = reinterpret_cast<GetStringFn>(Utils::PatternScan("client.dll", "55 8B EC 83 E4 C0 81 EC ? ? ? ? 53 8B 5D 08"));
		assert(oGetString != nullptr);

		return oGetString(this, szKeyName, szDefaultValue);
	}

	void KeyValues::SetString(const char* szKeyName, const char* szStringValue)
	{
		KeyValues* pSubKey = FindKey(szKeyName, true);

		if (pSubKey == nullptr)
			return;

		using SetStringFn = void(__thiscall*)(void*, const char*);
		static auto oSetString = reinterpret_cast<SetStringFn>(Utils::PatternScan("client.dll", "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01"));
		assert(oSetString != nullptr);

		oSetString(pSubKey, szStringValue);
	}

	void KeyValues::SetInt(const char* szKeyName, const int iValue)
	{
		KeyValues* pSubKey = FindKey(szKeyName, true);

		if (pSubKey == nullptr)
			return;

		pSubKey->iValue = iValue;
		pSubKey->iDataType = TYPE_INT;
	}

	void KeyValues::SetUint64(const char* szKeyName, const int nLowValue, const int nHighValue)
	{
		KeyValues* pSubKey = FindKey(szKeyName, true);

		if (pSubKey == nullptr)
			return;

		// delete the old value
		delete[] pSubKey->szValue;

		// make sure we're not storing the WSTRING - as we're converting over to STRING
		delete[] pSubKey->wszValue;
		pSubKey->wszValue = nullptr;

		pSubKey->szValue = new char[sizeof(std::uint64_t)];
		*reinterpret_cast<std::uint64_t*>(pSubKey->szValue) = static_cast<std::uint64_t>(nHighValue) << 32ULL | nLowValue;
		pSubKey->iDataType = TYPE_UINT64;
	}
}





























































