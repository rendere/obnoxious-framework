#pragma once
#include "../Include/Def.h"
#include "../Hooks/Tables.h"
#include "../Engine/Utils/Utils.h"
#include "../Engine/SDK/SDK.h"
#include "../Engine/NetVar.h"
#include "../hooks/createmove.h"
#include "../Hooks/views.h"
#include  "../hooks/emitsound.h"
#include "../Hooks/fsn.h"
#include "../Hooks/dme.h"
#include "../Hooks/Other.h"
#include "../Hacks/Setup.h"
#include "Offsets.h"

using namespace SDK;
using namespace Engine;

class IIInit
{
public:
	virtual class IInit
	{
	public:
		virtual void InitHooks() = 0;
		virtual void InitOffsets() = 0;
		virtual bool Init() = 0;
	};
};

#define SendMessageIdx 0
#define RetrieveMessageIdx 2
#define EmitSoundIdx 5
#define OverrideViewIdx 18
#define DrawModelExecuteIdx 21
#define CreateMoveIdx 24
#define GetViewModelFOVIdx 35
#define FrameStageNotifyIdx 37
#define LockCursorIdx 67

using namespace HookTables;

class CInit : public IIInit
{
public:
	virtual class IInit
	{
	public:
		virtual void InitHooks()
		{
			auto LInitHooks = [&]() -> void
			{
				debug_log("init hooks/variables:\n");
				debug_log("2-1-11-0\n");
				auto& pContext = cContext::GetInstance();
				debug_log("2-1-11-1\n");
				PVOID* SoundTable = *reinterpret_cast<PVOID**>(I::Sound());
				PVOID* SurfaceTable = *reinterpret_cast<PVOID**>(I::Surface());
				PVOID* ClientModeTable = *reinterpret_cast<PVOID**>(I::ClientMode());
				PVOID* ClientTable = *reinterpret_cast<PVOID**>(I::Client());
				PVOID* ModelRenderTable = *reinterpret_cast<PVOID**>(I::ModelRender());
				PVOID* SteamTable = *reinterpret_cast<PVOID**>(I::SteamGameCoordinator());

				debug_log("2-1-11-2\n");
#ifndef ONLY_DRAW_HOOK
				debug_log("2-1-11-3\n");
				if (SoundTable)
				{
					pContext.ApplyDetour<EmitSoundFn>(static_cast<EmitSoundFn>(SoundTable[EmitSoundIdx]),
						reinterpret_cast<EmitSoundFn>
						(hkEmitSound),
						&pEmitSound);
					debug_log("Hook: Emit Sound\n");
				}
				debug_log("2-1-11-4\n");
				if (SurfaceTable)
				{
					pContext.ApplyDetour<LockCursorFn>(static_cast<LockCursorFn>(SurfaceTable[LockCursorIdx]),
						reinterpret_cast<LockCursorFn>
						(hkLockCursor),
						&pLockCursor);
					debug_log("Hook: Cursor\n");
				}
				debug_log("2-1-11-5\n");
				if (ClientModeTable)
				{
					pContext.ApplyDetour<CreateMoveFn>(static_cast<CreateMoveFn>(ClientModeTable[CreateMoveIdx]),
						reinterpret_cast<CreateMoveFn>
						(hkCreateMove),
						&pCreateMove);
					debug_log("Hook: CreateMove\n");

					pContext.ApplyDetour<OverrideViewFn>(static_cast<OverrideViewFn>(ClientModeTable[OverrideViewIdx]),
						reinterpret_cast<OverrideViewFn>
						(hkOverrideView),
						&pOverrideView);
					debug_log("Hook: OverrideView\n");

					pContext.ApplyDetour<GetViewModelFOVFn>(static_cast<GetViewModelFOVFn>(ClientModeTable[GetViewModelFOVIdx]),
						reinterpret_cast<GetViewModelFOVFn>
						(hkGetViewModelFOV),
						&pGetViewModelFOV);
					debug_log("Hook: GetViewModelFOV\n");
				}
				debug_log("2-1-11-6\n");
				if (ClientTable)
				{
					pContext.ApplyDetour<FrameStageNotifyFn>(static_cast<FrameStageNotifyFn>(ClientTable[FrameStageNotifyIdx]),
						reinterpret_cast<FrameStageNotifyFn>
						(hkFrameStageNotify),
						&pFrameStageNotify);
					debug_log("Hook: StageNotify\n");
				}
				debug_log("2-1-11-7\n");
				if (ModelRenderTable)
				{
					pContext.ApplyDetour<DrawModelExecuteFn>(static_cast<DrawModelExecuteFn>(ModelRenderTable[DrawModelExecuteIdx]),
						reinterpret_cast<DrawModelExecuteFn>
						(hkDrawModelExecute),
						&pDrawModelExecute);
					debug_log("Hook: DME\n");
				}
#ifdef ENABLE_INVENTORY
				if (SteamTable)
				{
					pContext.ApplyDetour<RetrieveMessageFn>(static_cast<RetrieveMessageFn>(SteamTable[RetrieveMessageIdx]),
						reinterpret_cast<RetrieveMessageFn>
						(hkRetrieveMessage),
						&pRetrieveMessage);
					debug_log("Hook: RetrieveMessage\n");

					pContext.ApplyDetour<SendMessageFn>(static_cast<SendMessageFn>(SteamTable[SendMessageIdx]),
						reinterpret_cast<SendMessageFn>
						(hkSendMessage),
						&pSendMessage);
					debug_log("Hook: SendMessage\n");
				}
#endif
#endif
				debug_log("2-1-11-8\n");

				CGlobal::OrigRightHand = I::GetCvar()->FindVar(__xor("cl_righthand"))->GetFloat();
				CGlobal::OrigViewModelX = I::GetCvar()->FindVar(__xor("viewmodel_offset_x"))->GetFloat();
				CGlobal::OrigViewModelY = I::GetCvar()->FindVar(__xor("viewmodel_offset_y"))->GetFloat();
				CGlobal::OrigViewModelZ = I::GetCvar()->FindVar(__xor("viewmodel_offset_z"))->GetFloat();
				CGlobal::OrigAspectRatio = I::GetCvar()->FindVar(__xor("r_aspectratio"))->GetFloat();

				GP_Setup = new CSetup::ISetup();
				GP_Setup->Setup();
				debug_log("2-1-11-9\n");
				debug_log("All Hooks sucessful\n");
			};
			LInitHooks();
			debug_log("2-1-11-10\n");

			 
		}
		virtual void InitOffsets()
		{
#define mGetOffset(table, prop) g_NetVar.GetOffset(__xor(table), __xor(prop))
			auto LInitOffsets = [&]() -> void
			{
				debug_log("2-1-9-0\n");
				debug_log("======================Init Offsets/Patterns:\n");

				offsets["m_hMyWeapons"] = mGetOffset("DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
				offsets["m_hMyWearables"] = mGetOffset("DT_BaseCombatCharacter", "m_hMyWearables");
				offsets["m_vecOrigin"] = mGetOffset("DT_BasePlayer", "m_vecOrigin");
				offsets["m_hViewModel"] = mGetOffset("DT_BasePlayer", "m_hViewModel[0]");
				offsets["m_nTickBase"] = mGetOffset("DT_BasePlayer", "m_nTickBase");
				offsets["m_iObserverMode"] = mGetOffset("DT_BasePlayer", "m_iObserverMode");
				offsets["m_hObserverTarget"] = mGetOffset("DT_BasePlayer", "m_hObserverTarget");
				offsets["deadflag"] = mGetOffset("DT_BasePlayer", "deadflag");
				offsets["m_bIsDefusing"] = mGetOffset("DT_CSPlayer", "m_bIsDefusing");
				offsets["m_iAccount"] = mGetOffset("DT_CSPlayer", "m_iAccount");
				offsets["m_lifeState"] = mGetOffset("DT_CSPlayer", "m_lifeState");
				offsets["m_flFlashDuration"] = mGetOffset("DT_CSPlayer", "m_flFlashDuration");
				offsets["m_hRagdoll"] = mGetOffset("DT_CSPlayer", "m_hRagdoll");
				offsets["m_flSpawnTime"] = mGetOffset("DT_CSPlayer", "m_flSpawnTime");
				offsets["m_flC4Blow"] = mGetOffset("DT_PlantedC4", "m_flC4Blow");
				offsets["m_flDefuseCountDown"] = mGetOffset("DT_PlantedC4", "m_flDefuseCountDown");
				offsets["m_hBombDefuser"] = mGetOffset("DT_PlantedC4", "m_hBombDefuser");
				offsets["m_bBombDefused"] = mGetOffset("DT_PlantedC4", "m_bBombDefused");
				offsets["m_nBombSite"] = mGetOffset("DT_PlantedC4", "m_nBombSite");
				offsets["m_bFreezePeriod"] = mGetOffset("DT_CSGameRulesProxy", "m_bFreezePeriod");
				offsets["m_bIsValveDS"] = mGetOffset("DT_CSGameRulesProxy", "m_bIsValveDS");
				offsets["m_bBombPlanted"] = mGetOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
				offsets["m_bBombDropped"] = mGetOffset("DT_CSGameRulesProxy", "m_bBombDropped");
				offsets["m_flFlashMaxAlpha"] = mGetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
				offsets["m_bHasHelmet"] = mGetOffset("DT_CSPlayer", "m_bHasHelmet");
				offsets["m_bHasDefuser"] = mGetOffset("DT_CSPlayer", "m_bHasDefuser");
				offsets["m_bIsScoped"] = mGetOffset("DT_CSPlayer", "m_bIsScoped");
				offsets["m_iGlowIndex"] = mGetOffset("DT_CSPlayer", "m_iGlowIndex");
				offsets["m_iFOVStart"] = mGetOffset("DT_CSPlayer", "m_iFOVStart");
				offsets["m_fFlags"] = mGetOffset("DT_CSPlayer", "m_fFlags");
				offsets["m_nRenderMode"] = mGetOffset("DT_BaseEntity", "m_nRenderMode");
				offsets["m_MoveType"] = offsets["m_nRenderMode"] + 1;
				offsets["m_hOwnerEntity"] = mGetOffset("DT_BaseEntity", "m_hOwnerEntity");
				offsets["m_iHealth"] = mGetOffset("DT_BasePlayer", "m_iHealth");
				offsets["m_ArmorValue"] = mGetOffset("DT_CSPlayer", "m_ArmorValue");
				offsets["m_iTeamNum"] = mGetOffset("DT_BasePlayer", "m_iTeamNum");
				offsets["m_iShotsFired"] = mGetOffset("DT_CSPlayer", "m_iShotsFired");
				offsets["m_aimPunchAngle"] = mGetOffset("DT_BasePlayer", "m_aimPunchAngle");
				offsets["m_viewPunchAngle"] = mGetOffset("DT_BasePlayer", "m_viewPunchAngle");
				offsets["m_vecVelocity"] = mGetOffset("DT_CSPlayer", "m_vecVelocity[0]");
				offsets["m_vecPunchAngles"] = mGetOffset("DT_BasePlayer", "m_aimPunchAngle");
				offsets["m_vecViewOffset"] = mGetOffset("DT_CSPlayer", "m_vecViewOffset[0]");
				offsets["m_angEyeAngles"] = mGetOffset("DT_CSPlayer", "m_angEyeAngles");
				offsets["m_hActiveWeapon"] = mGetOffset("DT_BasePlayer", "m_hActiveWeapon");
				offsets["m_iClip1"] = mGetOffset("DT_BaseCombatWeapon", "m_iClip1");
				offsets["m_iClip2"] = mGetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
				offsets["m_flNextPrimaryAttack"] = mGetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
				offsets["m_flLowerBodyYawTarget"] = mGetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
				offsets["m_bCanReload"] = offsets["m_flNextPrimaryAttack"] + 0x6D;
				offsets["m_bGunGameImmunity"] = mGetOffset("DT_CSPlayer", "m_bGunGameImmunity");
				offsets["m_bPinPulled"] = mGetOffset("DT_BaseCSGrenade", "m_bPinPulled");
				offsets["m_fThrowTime"] = mGetOffset("DT_BaseCSGrenade", "m_fThrowTime");
				offsets["m_iItemDefinitionIndex"] = mGetOffset("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
				offsets["m_bIsAutoaimTarget"] = mGetOffset("DT_BaseEntity", "m_bIsAutoaimTarget");
				offsets["m_iItemIDHigh"] = mGetOffset("DT_BaseAttributableItem", "m_iItemIDHigh");
				offsets["m_iAccountID"] = mGetOffset("DT_BaseAttributableItem", "m_iAccountID");
				offsets["m_iEntityQuality"] = mGetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
				offsets["m_OriginalOwnerXuidLow"] = mGetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
				offsets["m_OriginalOwnerXuidHigh"] = mGetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
				offsets["m_nFallbackPaintKit"] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
				offsets["m_flFallbackWear"] = mGetOffset("DT_BaseAttributableItem", "m_flFallbackWear");
				offsets["m_nFallbackSeed"] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackSeed");
				offsets["m_szCustomName"] = mGetOffset("DT_BaseAttributableItem", "m_szCustomName");
				offsets["m_nFallbackStatTrak"] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak");
				offsets["m_Item"] = mGetOffset("DT_BaseAttributableItem", "m_Item");
				offsets["m_nModelIndex"] = mGetOffset("DT_BaseViewModel", "m_nModelIndex");
				offsets["m_nSequence"] = mGetOffset("DT_BaseViewModel", "m_nSequence");
				offsets["m_iViewModelIndex"] = mGetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
				offsets["m_hOwner"] = mGetOffset("DT_PredictedViewModel", "m_hOwner");
				offsets["m_hWeapon"] = mGetOffset("DT_BaseViewModel", "m_hWeapon");
				offsets["m_bSpotted"] = mGetOffset("DT_BaseEntity", "m_bSpotted");
				offsets["m_zoomLevel"] = mGetOffset("DT_WeaponAWP", "m_zoomLevel");
				offsets["m_flSimulationTime"] = mGetOffset("DT_BaseEntity", "m_flSimulationTime");
				offsets["m_flDuckAmount"] = mGetOffset("DT_BaseEntity", "m_flDuckAmount");
				offsets["m_hWeaponWorldModel"] = mGetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
				offsets["m_iWorldModelIndex"] = mGetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
				offsets["m_nHitboxSet"] = mGetOffset("DT_BaseAnimating", "m_nHitboxSet");
				offsets["m_flPoseParameter"] = mGetOffset("DT_BaseAnimating", "m_flPoseParameter");

				offsets["PlayerAnimState"] = 0x3914;
				offsets["AnimOverlays"] = 0x2990;

				offsets["d3d9TablePtrPtr"] = (Utils::PatternScan(shaderapidx9Factory, __xor("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);
				offsets["Input"] = (Utils::PatternScan(clientFactory, __xor("B9 ? ? ? ? F3 0F 11 04 24 FF 50 10")) + 1);
				offsets["MoveHelper"] = (Utils::PatternScan(clientFactory, __xor("8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01")) + 2);
				offsets["ClientState"] = (Utils::PatternScan(engineFactory, __xor("A1 ? ? ? ? 8B 80 ? ? ? ? C3")) + 1);
				offsets["GameRules"] = (Utils::PatternScan(clientFactory, __xor("89 35 ? ? ? ? C7 46 ? ? ? ? ? 89 46 1C 5E")) + 2);
				offsets["PredictionSeed"] = (Utils::PatternScan(clientFactory, "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
				offsets["PredictionPlayer"] = (Utils::PatternScan(clientFactory, "89 35 ? ? ? ? F3 0F 10 48 20") + 2);
				offsets["SetLocalPlayerReady"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
				offsets["SmokeCount"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0")) + 8);
				offsets["SetClanTag"] = (Utils::PatternScan(engineFactory, __xor("53 56 57 8B DA 8B F9 FF 15")));
				offsets["ItemDefinitionByName"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 57 8B F9 80 BF ? ? ? ? ? 74 07")));
				offsets["ItemDefinitionMap"] = (Utils::PatternScan(clientFactory, __xor("8B 87 ? ? ? ? 83 7C 88 ? ? 7C 0A 8B 44 88 04 5F 5E 5D C2 04 00 8B 87 ? ? ? ?")) + 2);
				offsets["LineGoesThroughSmoke"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0")));
				offsets["ViewMatrix"] = (Utils::PatternScan(clientFactory, __xor("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9")));
				offsets["SequenceActivity"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 53 8B 5D 08 56 8B F1 83")));
				offsets["CurrentCommand"] = (Utils::PatternScan(clientFactory, __xor("89 BE ? ? ? ? E8 ? ? ? ? 85 FF")) + 2);
				offsets["InvalidateBoneCache"] = (Utils::PatternScan(clientFactory, __xor("80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81")));
				offsets["CreateAnimState"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 56 8B F1 B9 ? ? ? ? C7 46")));
				offsets["UpdateAnimState"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24")));
				offsets["ResetAnimState"] = (Utils::PatternScan(clientFactory, __xor("56 6A 01 68 ? ? ? ? 8B F1")));
				offsets["SetAbsAngles"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8")));
				offsets["SetAbsOrigin"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8")));
				offsets["FromString"] = (Utils::PatternScan(clientFactory, __xor("E8 ? ? ? ? 83 C4 04 89 45 D8")) + 1);
				offsets["FindKey"] = (Utils::PatternScan(clientFactory, __xor("E8 ? ? ? ? F7 45")) + 1);
				offsets["SetString"] = (Utils::PatternScan(clientFactory, __xor("E8 ? ? ? ? 89 77 38")) + 1);
				offsets["IsReloading"] = (Utils::PatternScan(clientFactory, __xor("C6 87 ? ? ? ? ? 8B 06 8B CE FF 90")));
				offsets["InitializeKits"] = (Utils::PatternScan(clientFactory, __xor("E8 ? ? ? ? FF 76 0C 8D 48 04 E8")));
				offsets["InitializeStickers"] = (Utils::PatternScan(clientFactory, __xor("53 8D 48 04 E8 ? ? ? ? 8B 4D 10")) + 4);
				offsets["MakeGlove"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8")));
				offsets["FindHudElementThis"] = (Utils::PatternScan(clientFactory, __xor("B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08")) + 1);
				offsets["FindHudElement"] = (Utils::PatternScan(clientFactory, __xor("55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28")));
				offsets["FullUpdate"] = (Utils::PatternScan(engineFactory, __xor("A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85")));
				debug_log("All Offsets/Patterns sucessful\n");
				debug_log("2-1-9-1\n");
	 		};
			LInitOffsets();
			debug_log("2-1-9-2\n");
		}	
		virtual bool Init()
		{
			auto LInit = [&]() -> bool
			{
#ifndef ONLY_DRAW_HOOK			
				debug_log("2-1-1\n");
				if (!Utils::IsModuleLoad(engineFactory, 5001))
					return false;
				if (!Utils::IsModuleLoad(vguiFactory, 5001))
					return false;
				if (!Utils::IsModuleLoad(vguimatFactory, 5001))
					return false;
				if (!Utils::IsModuleLoad(valveStdFactory, 5001))
					return false;
				if (!Utils::IsModuleLoad(steamApiFactory, 5001))
					return false;
				if (!Utils::IsModuleLoad(serverBrowserFactory, 40000))
					return false;

				FastCall::G().t_Sleep(1500);

				if (!Utils::IsModuleLoad(clientFactory, 5001))
					return false;

				debug_log("2-1-2\n");
				if (!g_NetVar.Init(I::Client()->GetAllClasses()))
				{
					debug_log("2-1-9-8-1\n");
					FastCall::G().t_MessageBoxA(0, __xor("AllClasses error"), __xor("Error!"), 0);
					return false;
				}
				debug_log("2-1-3\n");
				InitOffsets();
				debug_log("2-1-4\n");
#endif 
				InitHooks();
				return true;
			};
			return LInit();
			 
		}
	};
};