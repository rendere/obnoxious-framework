#pragma once
#include "CUserCmd.hpp"

#define MULTIPLAYER_BACKUP 150

namespace SDK
{
	class CInput
	{
	public:


		byte			    m_pad0[0xC];				// 0x00
		bool				m_bTrackIRAvailable;		// 0x0C
		bool				m_bMouseInitialized;		// 0x0D
		bool				m_bMouseActive;				// 0x0E
		byte			    m_pad1[0x9A];				// 0x0F
		bool				m_bCameraInThirdPerson;		// 0xA9
		byte			    m_pad2[0x2];				// 0xAA
		Vector				m_vecCameraOffset;			// 0xAC
		byte			    m_pad3[0x38];				// 0xB8
		CUserCmd*           m_pCommands;				// 0xF0
		CVerifiedUserCmd*   m_pVerifiedCommands;		// 0xF4
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
		auto verifiedCommands = *(CVerifiedUserCmd**)(reinterpret_cast<uint32_t>(this) + 0xF8);
		return &verifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
	}

}