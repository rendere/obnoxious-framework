#pragma once
#include "CUserCmd.hpp"

#define MULTIPLAYER_BACKUP 150

namespace SDK
{
	class CInput
	{
	public:

		char	            pad0[0xC];            // 0x0
		bool                bTrackIRAvailable;        // 0xC
		bool                bMouseInitialized;        // 0xD
		bool                bMouseActive;            // 0xE
		char	            pad1[0x9A];            // 0xF
		bool                bCameraInThirdPerson;    // 0xA9
		char				pad2[0x2];            // 0xAA
		Vector              vecCameraOffset;        // 0xAC
		char	            pad3[0x38];            // 0xB8
		CUserCmd* m_pCommands;            // 0xF0
		CVerifiedUserCmd* m_pVerifiedCommands;    // 0xF4
		inline CUserCmd* GetUserCmd(int sequence_number);
		inline CUserCmd* GetUserCmd(int nSlot, int sequence_number);
		inline CVerifiedUserCmd* GetVerifiedCmd(int sequence_number);
	};

	CUserCmd* CInput::GetUserCmd(int sequence_number)
	{
		using OriginalFn = CUserCmd * (__thiscall*)(void*, int, int);
		return GetMethod<OriginalFn>(this, 8)(this, 0, sequence_number);
	}

	CUserCmd* CInput::GetUserCmd(int nSlot, int sequence_number)
	{
		typedef CUserCmd* (__thiscall* GetUserCmd_t)(void*, int, int);
		return GetMethod<GetUserCmd_t>(this, 8)(this, nSlot, sequence_number);
	}

	CVerifiedUserCmd* CInput::GetVerifiedCmd(int sequence_number)
	{
		return &(*(CVerifiedUserCmd**)((DWORD)this + 0x010C))[sequence_number % MULTIPLAYER_BACKUP];
	}

}