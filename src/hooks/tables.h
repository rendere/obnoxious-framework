#pragma once
#include "../Hacks/Setup.h"
#include "../Engine/SDK/SDK.h"
#include "../Hooks/MinHook/hook.h"
using namespace SDK;

namespace HookTables
{
	using oEndScene = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*);
	using oPresent = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
	using oReset = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	typedef void* (__thiscall* AllocKeyValuesMemFn)(PVOID, std::uintptr_t, int);
	using CreateMoveFn = void(__stdcall*)(int,float,bool);
	using OverrideViewFn = bool(__stdcall*)(CViewSetup*);
	using GetViewModelFOVFn = float(__stdcall*)();
	using FrameStageNotifyFn = void(__thiscall*)(void*, ClientFrameStage_t);
	using FireEventClientSideThinkFn = bool(__thiscall*)(void*, IGameEvent*);
	using LockCursorFn = bool(__thiscall*)(void*);
	using PostDataUpdateFn = void(__stdcall*)(void*, int);
	using EmitSoundFn = void(__fastcall*)(IEngineSound*, int, IRecipientFilter&, int, int, const char*, 
		unsigned int, const char*, float, float, int, int, int, const Vector*, 
		const Vector*, CUtlVector<Vector>*, bool, int, int, SndInfo_t&);
	//using SendDatagramfn = int(__thiscall*)(INetChannelInfo*, void*);
#ifdef ENABLE_INVENTORY
	using RetrieveMessageFn = EGCResults(__thiscall*)(void*, uint32_t*, void*, uint32_t, uint32_t*);
	using SendMessageFn = EGCResults(__thiscall*)(void*, uint32_t, const void*, uint32_t);
#endif

	cDetour<oPresent>* pPresent;
	cDetour<oEndScene>* pEndScene;
	cDetour<oReset>* pReset;
	cDetour<AllocKeyValuesMemFn>* pAllocKeyValues;
	cDetour<RecvVarProxyFn>* fnSequenceProxyFn;
	cDetour<RecvVarProxyFn>* oRecvnModelIndex;

	cDetour<CreateMoveFn>* pCreateMove;
	cDetour<OverrideViewFn>* pOverrideView;
	cDetour<GetViewModelFOVFn>* pGetViewModelFOV;
	cDetour<FrameStageNotifyFn>* pFrameStageNotify;
	cDetour<FireEventClientSideThinkFn>* pFireEventClientSideThink;
	cDetour<LockCursorFn>* pLockCursor;
	cDetour<PostDataUpdateFn>* pPostDataUpdate;
	cDetour<EmitSoundFn>* pEmitSound;
	//cDetour<SendDatagramfn>* pSendDatagram;
#ifdef ENABLE_INVENTORY
	cDetour<RetrieveMessageFn>* pRetrieveMessage;
	cDetour<SendMessageFn>* pSendMessage;
#endif
	void Shutdown()
	{
		/*Render hook*/
		pEndScene->Remove();
		pPresent->Remove();
		pReset->Remove();
		/*===========*/

		/*Animation hook for knive*/
		fnSequenceProxyFn->Remove();
		oRecvnModelIndex->Remove();
		/*========================*/

		/*Function hook*/
		pCreateMove->Remove();
		pAllocKeyValues->Remove();
		pOverrideView->Remove();
		pGetViewModelFOV->Remove();
		pFrameStageNotify->Remove();
		pFireEventClientSideThink->Remove();
		pLockCursor->Remove();
		pPostDataUpdate->Remove();
		pEmitSound->Remove();
#ifdef ENABLE_INVENTORY
		pRetrieveMessage->Remove();
		pSendMessage->Remove();
#endif
		/*=============*/
	}
}