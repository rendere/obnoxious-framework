#pragma once
#include "Tables.h"
#include "../Engine/EnginePrediction.h"

void __stdcall hkCreateMove(int sequence, float frametime, bool active, bool& bSendPacket)
{
    HookTables::pCreateMove->GetTrampoline()(sequence, frametime, active);

	CUserCmd* pCmd = I::Input()->GetUserCmd(sequence);
	CVerifiedUserCmd* pVerified = I::Input()->GetVerifiedCmd(sequence);

	if (!pCmd || !active)
		return;

	if (CGlobal::IsGameReady && pCmd->command_number != 0 && !CGlobal::FullUpdateCheck)
	{
		CGlobal::GViewAngle = pCmd->viewangles;
		CGlobal::UserCmd = pCmd;
		CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

	//	if (bReturn) // this is apparently unneeded when hooking chlclient::createmove
	//		I::Prediction()->SetLocalViewangles(Vector(pCmd->viewangles.x, pCmd->viewangles.y, pCmd->viewangles.z));

		if (GP_EntPlayers)
			GP_EntPlayers->Update();

		if (GP_Esp)
			if (GP_Esp->GranadePrediction)
				grenade_prediction::Get().Tick(pCmd->buttons);

		DWORD* FirstP;
		__asm mov FirstP, ebp;

		bool bSendPacket = true;

		if (CGlobal::IsGuiVisible)
			pCmd->buttons &= ~IN_ATTACK;
		else if (GP_Skins && !CGlobal::IsGuiVisible)
			GP_Skins->SelectedWeapon = CGlobal::GetWeaponId();

		if (GP_LegitAim)
		{
			GP_LegitAim->SetSelectedWeapon();

			if (GP_LegitAim->Enable)
				GP_LegitAim->CreateMove(sequence, frametime, active, bSendPacket);

			if (GP_LegitAim->TriggerEnable)
				GP_LegitAim->TriggerCreateMove(pCmd);
		}

		if (GP_Misc)
			GP_Misc->CreateMove(sequence, frametime, active, bSendPacket);

		EnginePrediction::Run(pCmd);
		{
			if (GP_Misc)
				GP_Misc->CreateMoveEP(sequence, frametime, active, bSendPacket);

			CGlobal::CorrectMouse(pCmd);
		}
		EnginePrediction::End();

		CGlobal::ClampAngles(pCmd->viewangles);
		CGlobal::AngleNormalize(pCmd->viewangles);

	}
	pVerified->m_cmd = *pCmd;
	pVerified->m_crc = pCmd->GetChecksum();
}

__declspec(naked) void __stdcall hkCreateMove_proxy(int sequence, float frametime, bool active)
{
	__asm {
		push ebx
		push esp
		push dword ptr[esp + 20]
		push dword ptr[esp + 0Ch + 8]
		push dword ptr[esp + 10h + 4]
		call hkCreateMove
		pop  ebx
		retn 0Ch
	}
}