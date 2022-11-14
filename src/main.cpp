#include "Main.h"
#include "Hooks/Initialize/Initialize.h"
#include "GUI/Gui.h"
#include "api/threadinmemory.h"

DWORD WINAPI SetupThread(_In_ LPVOID lpThreadParameter)
{
	auto LSetupThread = [&]() -> DWORD
	{
		debug_log("thread setup started\n");
		CInit::IInit* pInit = new CInit::IInit();
		pInit->Init();
		DELETE_PTR(pInit);
		debug_log("thread setup successful\n");
		return FALSE;
	};
	return LSetupThread();
	 
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_opt_ LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
#ifdef CONSOLE_LOGS
		AllocConsole();
		AttachConsole(FastCall::G().t_GetCurrentProcessId());
		freopen("CONOUT$", "w", stdout);

		debug_log("dll attached\n");
		debug_log("build time: %s | %s\n", __TIME__, __DATE__);
#endif
		debug_log("1\n");
		make_unique<CreateThread_>(&SetupThread, hinstDll);
		debug_log("2\n");
		return TRUE;
	case DLL_PROCESS_DETACH:
		GP_Setup->Shutdown();
		DELETE_PTR(GP_Setup);
		debug_log("dll detaching\n");
	default:
		return TRUE;
	}
}
