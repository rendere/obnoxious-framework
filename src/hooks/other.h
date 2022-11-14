#include "Tables.h"

//int __fastcall hkSendDatagram(INetChannelInfo* network, void* datagram)
//{
//    #define GetWeap(a) ((a < 0) ? 0 : (a >= (int)GP_LegitAim->Weapons.size() ? (int)GP_LegitAim->Weapons.size()-1 : a))
//
//    static auto original = pSendDatagram->GetTrampoline();
//    if (!GP_LegitAim->BacktrackFakeLatency || datagram || !CGlobal::IsGameReady)
//    {
//        return original(network, datagram);
//    }
//    int instate = network->m_nInReliableState;
//    int insequencenr = network->m_nInSequenceNr;
//    int faketimeLimit = GP_LegitAim->Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit;
//
//    if (faketimeLimit <= 200) 
//        faketimeLimit = 0;
//    else 
//        faketimeLimit -= 200;
//
//    float delta = max(0.f, clamp(faketimeLimit / 1000.f, 0.f, GP_LegitAim->cvars.maxUnlag->GetFloat()) - network->GetLatency(0));
//
//    Backtrack::AddLatencyToNetwork(network, delta);
//
//    int result = original(network, datagram);
//
//    network->m_nInReliableState = instate;
//    network->m_nInSequenceNr = insequencenr;
//
//    return result;
//}
void* __fastcall hkAllocKeyValuesMemory(CKeyValuesSystem* thisptr, int iSize)
{
	static auto ofunc = HookTables::pAllocKeyValues->GetTrampoline();

	static const std::uintptr_t uAllocKeyValuesEngine = Utils::RelativeToAbsolute(Utils::PatternScan(engineFactory, __xor("E8 ? ? ? ? 83 C4 08 84 C0 75 10 FF 75 0C")) + 1) + 0x4A;
	static const std::uintptr_t uAllocKeyValuesClient = Utils::RelativeToAbsolute(Utils::PatternScan(clientFactory, __xor("E8 ? ? ? ? 83 C4 08 84 C0 75 10")) + 1) + 0x3E;
	if (reinterpret_cast<std::uintptr_t>(_ReturnAddress()) == uAllocKeyValuesEngine || reinterpret_cast<std::uintptr_t>(_ReturnAddress()) == uAllocKeyValuesClient)
		return nullptr;

	ofunc(thisptr, iSize);
}
#ifdef ENABLE_INVENTORY
EGCResults __fastcall hkRetrieveMessage(void* ecx, void* edx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	EGCResults status = HookTables::pRetrieveMessage->GetTrampoline()(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);

	if (status != k_EGCResultOK)
		return status;

	uint32_t messageType = *punMsgType & 0x7FFFFFFF;

	GP_Inventory->RetrieveMessage(ecx, edx, punMsgType, pubDest, cubDest, pcubMsgSize);

	return status;
}
EGCResults __fastcall hkSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
{
	uint32_t messageType = unMsgType & 0x7FFFFFFF;
	void* pubDataMutable = const_cast<void*>(pubData);

	GP_Inventory->SSendMessage(ecx, edx, unMsgType, pubDataMutable, cubData);

	EGCResults status = HookTables::pSendMessage->GetTrampoline()(ecx, unMsgType, pubDataMutable, cubData);

	if (status != k_EGCResultOK)
		return status;

	return status;
}
#endif