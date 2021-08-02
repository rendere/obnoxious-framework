#include "Setup.h"

CRender::IRender*	GP_Render = nullptr;
CSetup::ISetup*		GP_Setup = nullptr;
CEntityPlayers*		GP_EntPlayers = nullptr;
CEsp*				GP_Esp = nullptr;
CMisc*				GP_Misc = nullptr;
CAimbot*			GP_LegitAim = nullptr;
CSkins*				GP_Skins = nullptr;
#ifdef ENABLE_INVENTORY
CInventory*         GP_Inventory = nullptr;
#endif
CGHelper*			GP_GHelper = nullptr;
CMain*              GP_Main = nullptr;
