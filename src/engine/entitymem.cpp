#include "EntityMem.h"
#include "../Hacks/Setup.h"


void CEntityPlayers::Update()
{
	if (CGlobal::LocalPlayer)
	{
		for (int EntIndex = 0; EntIndex < I::Engine()->GetMaxClients(); EntIndex++)
		{
			CBaseEntity* pEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(EntIndex);

			if (!pEntity)
			{
				EntityPlayer[EntIndex].IsUpdated = false;
				continue;
			}

			if (!pEntity->IsPlayer())
			{
				EntityPlayer[EntIndex].IsUpdated = false;
				continue;
			}

			EntityPlayer[EntIndex].RenderOrigin = pEntity->GetRenderOrigin();
			if (EntityPlayer[EntIndex].RenderOrigin.IsZero())
			{
				EntityPlayer[EntIndex].IsUpdated = false;
				continue;
			}

			EntityPlayer[EntIndex].AbsOrigin = pEntity->GetAbsOrigin();
			if (EntityPlayer[EntIndex].AbsOrigin.IsZero())
			{
				EntityPlayer[EntIndex].IsUpdated = false;
				continue;
			}

			if (GP_Esp->Skeleton)
			{
				for (int i(0); i < 19; i++)
					EntityPlayer[EntIndex].HitBoxes[i] = pEntity->GetHitboxPosition(i);
			}
			else
				EntityPlayer[EntIndex].HitBoxes[HITBOX_HEAD] = pEntity->GetHitboxPosition(HITBOX_HEAD);

			EntityPlayer[EntIndex].EyeAngle = pEntity->GetEyeAngles();
			EntityPlayer[EntIndex].EyePosition = pEntity->GetEyePosition();
			EntityPlayer[EntIndex].BaseEntity = pEntity;
			EntityPlayer[EntIndex].IsPlayer = true;
			EntityPlayer[EntIndex].IsDead = pEntity->IsDead();
			EntityPlayer[EntIndex].IsDormant = pEntity->IsDormant();
			if (!EntityPlayer[EntIndex].HitBoxes[HITBOX_HEAD].IsZero())
			{
				EntityPlayer[EntIndex].Alpha = 255.f;
				EntityPlayer[EntIndex].HideEndTime = 0.f;
			}

			EntityPlayer[EntIndex].IsVisble = pEntity->IsVisible(CGlobal::LocalPlayer);
			EntityPlayer[EntIndex].Name = pEntity->GetPlayerName();
			EntityPlayer[EntIndex].Idx = EntIndex;
			EntityPlayer[EntIndex].IsLocal = pEntity == CGlobal::LocalPlayer;
			EntityPlayer[EntIndex].Team = (PLAYER_TEAM)pEntity->GetTeam();
			EntityPlayer[EntIndex].Distance = EntityPlayer[EntIndex].RenderOrigin.DistTo(CGlobal::LocalPlayer->GetRenderOrigin()) / 33;
			EntityPlayer[EntIndex].Money = pEntity->GetMoney();
			EntityPlayer[EntIndex].Health = pEntity->GetHealth();
			EntityPlayer[EntIndex].Armor = pEntity->GetArmor();
			EntityPlayer[EntIndex].IsFlashed = pEntity->IsFlashed();

			CBaseWeapon* pWeaponEntity = pEntity->GetBaseWeapon();

			if (pWeaponEntity && pWeaponEntity->GetName())
			{
				string WeaponStr = pWeaponEntity->GetName();
				WeaponStr = WeaponStr.erase(0, 13);
				EntityPlayer[EntIndex].WeaponName = WeaponStr;
				EntityPlayer[EntIndex].WeaponIdx = *pWeaponEntity->GeteAttributableItem()->GetItemDefinitionIndex();
				EntityPlayer[EntIndex].ZoomLevel = pWeaponEntity->GetZoomLevel();
				EntityPlayer[EntIndex].Weaponinfo = pWeaponEntity->GetWeaponInfo();

				if (pWeaponEntity->GetWeaponAmmo() > 0)
				{
					EntityPlayer[EntIndex].Ammo1 = pWeaponEntity->GetWeaponAmmo();
					EntityPlayer[EntIndex].Ammo2 = pWeaponEntity->GetWeaponAmmoClp2();
				}
				else
				{
					EntityPlayer[EntIndex].Ammo1 = 0;
					EntityPlayer[EntIndex].Ammo2 = 0;
				}
			}

			EntityPlayer[EntIndex].IsUpdated = true;

			if (EntityPlayer[EntIndex].IsLocal)
				EntityLocal = &EntityPlayer[EntIndex];
		}
	}
}

CEntityPlayer* CEntityPlayers::FindByIdx(int Idx)
{
	for (int i(0); i < I::Engine()->GetMaxClients(); i++)
		if (Idx == EntityPlayer[i].Idx)
			return &EntityPlayer[i];
	return nullptr;
}

CEntityPlayer* CEntityPlayers::GetByIdx(int Idx)
{
	if (Idx >= 0 && Idx < I::Engine()->GetMaxClients())
	{
		return &EntityPlayer[Idx];
	}

	return nullptr;
}

void CEntityPlayers::Clear()
{
	memset(EntityLocal, 0, sizeof(CEntityPlayer));
	memset(EntityPlayer, 0, sizeof(CEntityPlayer) * I::Engine()->GetMaxClients());
}





























































