#pragma once

#include "BaseTypes.h"
#include "Const.h"
#include "Definitions.hpp"
#include "CRC.hpp"
#include "IAppSystem.hpp"
#include "Vector.hpp"
#include "Vplane.h"
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include "QAngle.hpp"
#include "VMatrix.hpp"
#include "CHandle.hpp"
#include "CGlobalVarsBase.hpp"
#include "ClientClass.hpp"
#include "ClientState.hpp"
#include "Color.hpp"
#include "CUtlMemory.h"
#include "CUtlVector.h"
#include "IBaseClientDll.hpp"
#include "IClientEntity.hpp"
#include "IClientEntityList.hpp"
#include "IClientNetworkable.hpp"
#include "IClientRenderable.hpp"
#include "IClientThinkable.hpp"
#include "IClientUnknown.hpp"
#include "IVEngineClient.hpp"
#include "IEngineTrace.hpp"
#include "ILocalize.hpp"
#include "Recv.hpp"
#include "IClientMode.hpp"
#include "IVModelInfoClient.hpp"
#include "CInput.hpp"
#include "ICollideable.h"
#include "IEngineSound.h"
#include "IVModelRender.h"
#include "IVRenderView.h"
#include "IMaterialSystem.h"
#include "IMaterialVar.h"
#include "ISurface.h"
#include "IGameEvent.h"
#include "TextureGroupNames.h"
#include "Cvar.h"
#include "IPhysics.hpp"
#include "KeyValues.h"
#include "Math.hpp"
#include "IPredition.hpp"
#include "checksum_md5.hpp"
#include "IGameRules.h"
#include "CUserCmd.hpp"

#include <Windows.h>
#include <WinInet.h>

#include "../Utils/Utils.h"
#include "../../steam_sdk/steam_api.h"

#pragma comment(lib, "Wininet.lib")

#define engineFactory               __xor("engine.dll")
#define clientFactory               __xor("client.dll")
#define valveStdFactory             __xor("vstdlib.dll")
#define matSysFactory               __xor("materialsystem.dll")
#define vphysicsFactory             __xor("vphysics.dll")
#define inputSysFactory             __xor("inputsystem.dll")
#define localizeFactory             __xor("localize.dll")
#define steamApiFactory             __xor("steam_api.dll")
#define serverBrowserFactory        __xor("serverbrowser.dll")
#define vguiFactory                 __xor("vgui2.dll")
#define vguimatFactory	            __xor("vguimatsurface.dll")
#define d3d9Factory                 __xor("d3d9.dll")
#define shaderapidx9Factory         __xor("shaderapidx9.dll")
#define filesysFactory              __xor("filesystem_stdio.dll")
#define tierFactory                 __xor("tier0.dll")

namespace SDK
{
	class I
	{
	public:
		static IVEngineClient*		  Engine();
		static IBaseClientDLL*		  Client();
		static IClientEntityList*	  EntityList();
		static IGameEventManager2*    GameEvent();
		static CGlobalVarsBase*		  GlobalVars();
		static CInput*				  Input();
		static CClientState*		  ClientState();
		static IEngineTrace*		  EngineTrace();
		static IPanel*                Panel();
		static IClientMode*			  ClientMode();
		static IVModelInfo*	          ModelInfo();
		static IEngineSound*		  Sound();
		static IVModelRender*		  ModelRender();
		static IViewRender*		      RenderView();
		static IMaterialSystem*		  MaterialSystem();
		static ISurface*			  Surface();
		static IPhysicsSurfaceProps*  PhysSurface();
		static ConVar*                GetCvar();
		static ILocalize*             Localize();
		static ISteamGameCoordinator* SteamGameCoordinator();
		static ISteamUser*            SteamUser();
		static IPrediction*           Prediction();
		static IMoveHelper*			  MoveHelper();
		static IGameMovement*	      GameMovement();
		static IGameRules*			  GameRules();
		static IMemAlloc*             MemAlloc();
	private:
		static IVEngineClient*		  g_pEngine;
		static IBaseClientDLL*		  g_pClient;
		static IClientEntityList*     g_pEntityList;
		static CGlobalVarsBase*		  g_pGlobals;
		static CInput*				  g_pInput;
		static CClientState*		  g_pClientState;
		static IEngineTrace*		  g_pEngineTrace;
		static IClientMode*			  g_pClientMode;
		static IPanel*                g_pPanel;
		static IVModelInfo*	          g_pModelInfo;
		static IEngineSound*		  g_pSound;
		static IVModelRender*		  g_pModelRender;
		static IViewRender*		      g_pRenderView;
		static IMaterialSystem*		  g_pMaterialSystem;
		static ISurface*			  g_pSurface;
		static IPhysicsSurfaceProps*  g_PhysSurface;
		static IGameEventManager2*	  g_pGameEvent;
		static ConVar*                g_pCvar;
		static ILocalize*             g_pLocalize;
		static ISteamGameCoordinator* g_pSteamGameCoordinator;
		static ISteamUser*            g_pSteamUser;
		static IPrediction*			  g_pPrediction;
		static IMoveHelper*           g_pMoveHelper;
		static IGameMovement*         g_pGameMovement;
		static IGameRules*            g_pGameRules;
		static IMemAlloc*             g_pMemAlloc;
	};

	template <typename T>
	T CallVFunc(void *vTable, int iIndex) 
	{
		return (*(T**)vTable)[iIndex];
	}
}


inline void**& GetVTable( void* instance )
{
	return *reinterpret_cast<void***>( (size_t)instance );
}

inline const void** GetVTable( const void* instance )
{
	return *reinterpret_cast<const void***>( (size_t)instance );
}

template<typename T>
inline T GetMethod( const void* instance , size_t index )
{
	return reinterpret_cast<T> ( GetVTable( instance )[index] );
}        