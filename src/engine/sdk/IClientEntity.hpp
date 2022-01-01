#pragma once
#include "Definitions.hpp"

#include"IClientNetworkable.hpp"
#include"IClientRenderable.hpp"
#include"IClientUnknown.hpp"
#include"IClientThinkable.hpp"

namespace SDK
{
	struct SpatializationInfo_t;

	class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
	{
	public:
		virtual void             Release(void) = 0;
		virtual const Vector&    GetAbsOrigin(void) const = 0;
		virtual const QAngle&    GetAbsAngles(void) const = 0;
		virtual void*            GetMouth(void) = 0;
		virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
		virtual bool             IsBlurred(void) = 0;
		template <typename Fn = void*>
		Fn get_vfunc(void* class_base, const std::size_t index)
		{
			return (*reinterpret_cast<Fn**>(class_base))[index];
		}
		void SetModelIndex(const int index)
		{
			get_vfunc<void(__thiscall*)(IClientEntity*, int)>(this, 75)(this, index);
		}
		int& GetModelIndex();
	};

#pragma pack(push, 1)
	class CCSWeaponInfo
	{ //xSeeker
	public:

        char pad0[0x14];            // 0x0000
        int iMaxClip1;                    // 0x0014
        int iMaxClip2;                    // 0x0018
        int iDefaultClip1;                // 0x001C
        int iDefaultClip2;                // 0x0020
        int iPrimaryMaxReserveAmmo;        // 0x0024
        int iSecondaryMaxReserveAmmo;    // 0x0028
        const char* szWorldModel;        // 0x002C
        const char* szViewModel;        // 0x0030
        const char* szDroppedModel;        // 0x0034
        char pad1[0x50];            // 0x0038
        const char* szHudName;            // 0x0088
        const char* szWeaponName;        // 0x008C
        char pad2[0x2];            // 0x0090
        bool bIsMeleeWeapon;            // 0x0092
        char pad3[0x9];            // 0x0093
        float flWeaponWeight;            // 0x009C
        char pad4[0x4];            // 0x00A0
        int iSlot;                        // 0x00A4
        int iPosition;                    // 0x00A8
        char pad5[0x1C];            // 0x00AC
        int nWeaponType;                // 0x00C8
        char pad6[0x4];            // 0x00CC
        int iWeaponPrice;                // 0x00D0
        int iKillAward;                    // 0x00D4
        const char* szAnimationPrefix;    // 0x00D8
        float flCycleTime;                // 0x00DC
        float flCycleTimeAlt;            // 0x00E0
        char pad8[0x8];            // 0x00E4
        bool bFullAuto;                    // 0x00EC
        char pad9[0x3];            // 0x00ED
        int iDamage;                    // 0x00F0
        float flHeadShotMultiplier;        // 0x00F4
        float flArmorRatio;                // 0x00F8
        int iBullets;                    // 0x00FC
        float flPenetration;            // 0x0100
        char pad10[0x8];            // 0x0104
        float flRange;                    // 0x010C
        float flRangeModifier;            // 0x0110
        float flThrowVelocity;            // 0x0114
        char pad11[0xC];            // 0x0118
        bool bHasSilencer;                // 0x0124
        char pad12[0xF];            // 0x0125
        float flMaxSpeed;            // 0x0134
        float flMaxSpeedAlt;            // 0x013C
        float flSpread[2];                // 0x0140
        float flInaccuracyCrouch[2];    // 0x0148
        float flInaccuracyStand[2];        // 0x0150
        char pad14[0x8];            // 0x0158
        float flInaccuracyJump[2];        // 0x0160
        float flInaccuracyLand[2];        // 0x0168
        float flInaccuracyLadder[2];    // 0x0170
        float flInaccuracyFire[2];        // 0x0178
        float flInaccuracyMove[2];        // 0x0180
        float flInaccuracyReload;        // 0x0188
        int iRecoilSeed;                // 0x018C
        float flRecoilAngle[2];            // 0x0190
        float flRecoilAngleVariance[2];    // 0x0198
        float flRecoilMagnitude[2];        // 0x01A0
        float flRecoilMagnitudeVariance[2]; // 0x01A8
        int iSpreadSeed;                // 0x01B0
    };
#pragma pack(pop)

	class IWeaponSystem
	{
		virtual void unused0() = 0;
		virtual void unused1() = 0;
	public:
		virtual CCSWeaponInfo* GetWpnData(unsigned ItemDefinitionIndex) = 0;
	};
}