#include "aimbot.h"
#include "../setup.h"
#define GetWeap(a) ((a < 0) ? 0 : (a >= (int)GP_LegitAim->Weapons.size() ? (int)GP_LegitAim->Weapons.size()-1 : a))

int SelectedWeapon = 0;

void CAimbot::SetSelectedWeapon(bool MenuCheck)
{
	if (MenuCheck ? !CGlobal::IsGuiVisible : true)
	{
		SelectedWeapon = CGlobal::GetWeaponId();

		if (SelectedWeapon < 0)
			SelectedWeapon = 0;

		if (WeaponCustomTypes == 1) // Standard
		{
			switch (CGlobal::GWeaponType)
			{
			case WEAPON_TYPE_RIFLE: SelectedWeapon = 34; StandardSubSelected = 0; CheckAimCust = true; break;
			case WEAPON_TYPE_PISTOL: SelectedWeapon = 35; StandardSubSelected = 1; CheckAimCust = true;  break;
			case WEAPON_TYPE_SHOTGUN: SelectedWeapon = 36; StandardSubSelected = 2; CheckAimCust = true;  break;
			case WEAPON_TYPE_SNIPER: SelectedWeapon = 37; StandardSubSelected = 3; CheckAimCust = true;  break;
			default: SelectedWeapon = -1; CheckAimCust = false;  break;
			}
		}
		else if (WeaponCustomTypes == 2) // Custom
		{
			bool Finded = false;
			if (SelectedWeapon >= 0 && SelectedWeapon < 34)
			{
				for (size_t i(0); i < CustomSubs.size(); i++)
				{
					for (auto &saw : CustomSubs[i].AllocatedWeapon)
					{
						string wepstr = CGlobal::WeaponNames[SelectedWeapon];
						if (wepstr == saw)
						{
							SelectedWeapon = CustomSubs[i].Idx;
							SelectedSub = i;
							Finded = true;
							break;
						}
					}
					if (Finded)
						break;
				}
			}
			if (!Finded)
			{
				SelectedWeapon = 0;
				CheckAimCust = false;
			}
			else
				CheckAimCust = true;

		}
		else if (WeaponCustomTypes == 3) // All
		{
			SelectedWeapon = 38;
			CheckAimCust = true;
		}
		else
			CheckAimCust = true;
	}
}

float TestSF = 10;
float TestMouse = 0;

void CAimbot::Draw()
{
	//if (Debug)
	//{
	//	int VTabSz = 15;
	//	int VTab = 15;

	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iBestTarget: ") + to_string(iBestTarget)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iBestHitBox: ") + to_string(iBestHitBox)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iSilentBestTarget: ") + to_string(iSilentBestTarget)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iSilentBestHitBox: ") + to_string(iSilentBestHitBox)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iShotsFired: ") + to_string(iShotsFired)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iEndBullet: ") + to_string(AimEndBullet)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iSilentHitBox: ") + to_string(SilentHitBox)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iHitBox: ") + to_string(HitBox)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bNearest: ") + to_string(IsNearest)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bSilentNearest: ") + to_string(IsSilentNearest)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bSilentF: ") + to_string(CanSilent)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("iCurWeapon: ") + to_string(SelectedWeapon)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fGFov: ") + to_string(GFov)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fGSilentFov: ") + to_string(GSilentFov)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fGSmooth: ") + to_string(GSmooth)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bRCSStandelone: ") + to_string(CanRCSStandelone)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bRCS: ") + to_string(CanRCS)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("BestPos: X: ") + to_string((int)BestHitBoxPos.x) + __xor(", Y: ") + to_string((int)BestHitBoxPos.y) + __xor(", Z: ") + to_string((int)BestHitBoxPos.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("BestSilentPos: X: ") + to_string((int)SilentBestHitBoxPos.x) + __xor(", Y: ") + to_string((int)SilentBestHitBoxPos.y) + __xor(", Z: ") + to_string((int)SilentBestHitBoxPos.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("FSA: X: ") + to_string((int)FovStartAng.x) + __xor(", Y: ") + to_string((int)FovStartAng.y) + __xor(", Z: ") + to_string((int)FovStartAng.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("PunchAng: X: ") + to_string((int)AimPunchAngle.x) + __xor(", Y: ") + to_string((int)AimPunchAngle.y) + __xor(", Z: ") + to_string((int)AimPunchAngle.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("PreVec: X: ") + to_string((int)PreVec.x) + __xor(", Y: ") + to_string((int)PreVec.y) + __xor(", Z: ") + to_string((int)PreVec.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("SilentPreVec: X: ") + to_string((int)SilentPreVec.x) + __xor(", Y: ") + to_string((int)SilentPreVec.y) + __xor(", Z: ") + to_string((int)SilentPreVec.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("FinalVec: X: ") + to_string((int)FinalVec.x) + __xor(", Y: ") + to_string((int)FinalVec.y) + __xor(", Z: ") + to_string((int)FinalVec.z)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(), 
	//		(__xor("SilentFinalVec: X: ") + to_string((int)SilentFinalVec.x) + __xor(", Y: ") + to_string((int)SilentFinalVec.y) + __xor(", Z: ") + to_string((int)SilentFinalVec.z)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fCurtime: ") + to_string(CurTime)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fFFDelayEnd: ") + to_string(FFDelay.STimer.EndTime)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFDelayEnable: ") + to_string(FFDelay.STimer.Enable)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFDelayDisable: ") + to_string(FFDelayDisable)).c_str()); VTab += VTabSz;

	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFDelayActive: ") + to_string(FFDelay.STimer.Active)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFOneClickDelay: ") + to_string(FFDelayOneClickEnable)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFOCDelayActive: ") + to_string(FFDelayOCActive)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFOCDelayDisable: ") + to_string(FFDelayOCDisable)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fTSDelayEnd: ") + to_string(TSDelay.STimer.EndTime)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bTSDelayEnable: ") + to_string(TSDelay.STimer.Enable)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bTSDelayActive: ") + to_string(TSDelay.STimer.Active)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bKillStop: ") + to_string(KillStop)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bKillStopEnable: ") + to_string(KillStopEnable)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bpSilentAutoDelay: ") + to_string(pSilentAutoDelay)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bpSilentAutoDelayEnable: ") + to_string(pSilentAutoDelayEnable)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bpSilentAutoDelayDisable: ") + to_string(pSilentAutoDelayDisable)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;

	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFAutoDelay: ") + to_string(FFAutoDelay)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFAutoDelayEnable: ") + to_string(FFAutoDelayEnable)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFFAutoDelayDisable: ") + to_string(FFAutoDelayDisable)).c_str()); VTab += VTabSz;
	//	VTab += VTabSz;

	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bAutoPistol: ") + to_string(AutoPistol)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bIsPistol: ") + to_string(IsPistol)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bIsSniper & Type: ") + to_string(IsSniper) + (" : ") + to_string(IsSniperClass)).c_str()); VTab += VTabSz;
	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bIsShotgun: ") + to_string(IsShotgun)).c_str()); VTab += VTabSz;

	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("bFastZoom & bZoomed: ") + to_string(FastZoom) + (" : ") + to_string(IsZoomed)).c_str()); VTab += VTabSz;

	//	GP_Render->DrawString(15, Vec2(500, VTab), Color::Yellow(),  (__xor("fTest: ") + to_string(TestMouse)).c_str()); VTab += VTabSz;
	//}

	if (ShowEntitysName)
	{
		for (int EntIndex = 0; EntIndex < I::EntityList()->GetHighestEntityIndex(); EntIndex++)
		{
			CBaseEntity* pEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(EntIndex);

			if (!pEntity)
				continue;

			const model_t* pModel = pEntity->GetModel();

			if (!pModel)
				continue;

			const char* pModelName = I::ModelInfo()->GetModelName(pModel);

			if (!pModelName)
				continue;

			Vector EntityScreen;

			if (true)
			{
				if (CGlobal::WorldToScreen(pEntity->GetRenderOrigin(), EntityScreen))
				{
					GP_Render->DrawString(14, Vec2(EntityScreen.x, EntityScreen.y), Color::Yellow(), false, true, pModelName);
				}
			}
		}
	}

	if (CGlobal::FullUpdateCheck)
		return;

	if (AimWorking && Enable && CheckAimCust)
	{
		if (ShowSpot)
		{
			if (iBestHitBox != -1 && iBestTarget != -1)
			{
				Vector BestHitBoxScreen;

				if (CGlobal::WorldToScreen(BestHitBoxPos, BestHitBoxScreen))
				{
					float LineLen = 12.f;
					GP_Render->DrawLine(BestHitBoxScreen.x - (LineLen / 2.f), BestHitBoxScreen.y, BestHitBoxScreen.x + (LineLen / 2.f), BestHitBoxScreen.y, FovColor);
					GP_Render->DrawLine(BestHitBoxScreen.x, BestHitBoxScreen.y - (LineLen / 2.f), BestHitBoxScreen.x, BestHitBoxScreen.y + (LineLen / 2.f), FovColor);
				}
			}

			if (iSilentBestHitBox != -1 && iSilentBestTarget != -1)
			{
				Vector SilentBestHitBoxScreen;

				if (CGlobal::WorldToScreen(SilentBestHitBoxPos, SilentBestHitBoxScreen))
				{
					float LineLen = 12.f;
					GP_Render->DrawLine(SilentBestHitBoxScreen.x - (LineLen / 2.f), SilentBestHitBoxScreen.y,
						SilentBestHitBoxScreen.x + (LineLen / 2.f), SilentBestHitBoxScreen.y, SilentFovColor);
					GP_Render->DrawLine(SilentBestHitBoxScreen.x, SilentBestHitBoxScreen.y - (LineLen / 2.f),
						SilentBestHitBoxScreen.x, SilentBestHitBoxScreen.y + (LineLen / 2.f), SilentFovColor);
				}
			}
		}

		if ((DrawFov || DrawSilentFov) && pLocalPlayer && AimWorking && SelectedWeapon > -1)
		{
			CBaseEntity* pPlayer = pLocalPlayer;

			if (!pPlayer)
				return;

			float dy = CGlobal::iScreenHeight / CGlobal::GFovView;
			float dx = CGlobal::iScreenWidth / CGlobal::GFovView;

			bool _CanSilent = true;

			if (Weapons[GetWeap(SelectedWeapon)].SilentEndBullet > 0)
				if (iShotsFired >= Weapons[GetWeap(SelectedWeapon)].SilentEndBullet)
					_CanSilent = false;

			if (_CanSilent)
				if (Weapons[GetWeap(SelectedWeapon)].SilentStartBullet > 0)
					if (Weapons[GetWeap(SelectedWeapon)].SilentStartBullet - 1 > iShotsFired)
						_CanSilent = false;

			float x = CGlobal::iScreenWidth / 2.f;
			float y = CGlobal::iScreenHeight / 2.f;

			if (FovPos != 2)
			{
				if (pPlayer && pLocalWeapon && !pPlayer->IsDead())
				{
					if (FovPos == 0)
					{
						if (DrawFov)
							GP_Render->DrawRing(x, y, (dy * GFov / 3.f), 32, FovColor);

						if (DrawSilentFov && Weapons[GetWeap(SelectedWeapon)].Silent)
							if (_CanSilent)
								GP_Render->DrawRing(x, y, (dy * GSilentFov), 32, SilentFovColor);
					}
					else if (FovPos == 1)
					{
						Vector punchAngle = (pLocalPlayer->GetPunchAngles() * (Vector(100, 100, 0) / 100.f));

						Vector2D pos = Vector2D(
							x - (dx * (punchAngle.y)),
							y + (dy * (punchAngle.x)));

						if (DrawFov)
							GP_Render->DrawRing(pos.x, pos.y, (dy * GFov / 3.f), 32, FovColor);

						if (DrawSilentFov && Weapons[GetWeap(SelectedWeapon)].Silent)
							if (_CanSilent)
								GP_Render->DrawRing(pos.x, pos.y, (dy * GSilentFov), 32, SilentFovColor);
					}
				}
			}
			if (FovPos == 2 && pOldBestTarget)
			{
				if (DrawFov && iLastBestHitBox != -1 && pOldBestTarget->GetHealth() > 0)
				{
					float base_fov = pow((dx * GFov / 3.f) + 30, 2) * CGlobal::GFovView;
					float iFov = (base_fov / (pLocalPlayer->GetHitboxPosition(0).DistTo(BestHitBoxPos) * CGlobal::GFovView));

					Vector m_vAimBestHitboxScreen;

					if (CGlobal::WorldToScreen(BestHitBoxPos, m_vAimBestHitboxScreen))
						GP_Render->DrawRing(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y, iFov / int(1920 / CGlobal::iScreenWidth), 32, FovColor);
				}
				if (DrawSilentFov && iLastSilentBestHitBox != -1 && pOldBestTarget->GetHealth() > 0 && Weapons[GetWeap(SelectedWeapon)].Silent)
				{
					float base_fov = pow((dx * GSilentFov) + 30, 2) * CGlobal::GFovView;
					float iFov = (base_fov / (pLocalPlayer->GetHitboxPosition(0).DistTo(SilentBestHitBoxPos) * CGlobal::GFovView));

					Vector m_vAimBestHitboxScreen;

					if (CGlobal::WorldToScreen(SilentBestHitBoxPos, m_vAimBestHitboxScreen) && _CanSilent)
						GP_Render->DrawRing(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y, iFov / int(1920 / CGlobal::iScreenWidth), 32, SilentFovColor);
				}
			}
		}
	}
}

static float getLerp()
{
	auto ratio = clamp(GP_LegitAim->cvars.interpRatio->GetFloat(), GP_LegitAim->cvars.minInterpRatio->GetFloat(), GP_LegitAim->cvars.maxInterpRatio->GetFloat());

	return max(GP_LegitAim->cvars.interp->GetFloat(), (ratio / ((GP_LegitAim->cvars.maxUpdateRate) ? GP_LegitAim->cvars.maxUpdateRate->GetFloat() : GP_LegitAim->cvars.UpdateRate->GetFloat())));
};

static bool valid(float simtime)
{
	auto network = I::Engine()->GetNetChannelInfo();
	if (!network)
		return false;

	auto delta = clamp(network->GetLatency(FLOW_OUTGOING) + network->GetLatency(FLOW_INCOMING) + getLerp(), 0.f, GP_LegitAim->cvars.maxUnlag->GetFloat()) - (I::GlobalVars()->curtime - simtime);
	return std::fabsf(delta) <= 0.2f;
};

void CAimbot::DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	if (ShowBacktrack && Weapons[GetWeap(SelectedWeapon)].Backtrack && Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit)
	{
		static auto fnDME = HookTables::pDrawModelExecute->GetTrampoline();
		const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

		if (!ModelName)
			return;

		if (!strstr(ModelName, __xor("models/player")))
			return;

		CEntityPlayer* Entity = GP_EntPlayers->GetByIdx(pInfo.entity_index);
		CEntityPlayer* Local = GP_EntPlayers->EntityLocal;

		if (!Entity || !Local)
			return;

		if (!Entity->IsUpdated)
			return;

		if (Entity->IsDead || Entity->Health <= 0)
			return;

		if (Entity->IsDormant)
			return;

		if (!Local->IsDead)
		{
			auto& record = records.at(Entity->Idx);
			if (record.size() > 0 && valid(record.front().simtime))
			{
				switch (SBTick)
				{
				case 0:
					for (auto& data : record)
					{
						if (Entity->RenderOrigin.DistTo(data.origin) > 1.f)
						{
							GP_Esp->OverrideMaterial(!SBVisibleOnly, SBDouble, SBStyle, ShowBactrackColor);
							fnDME(thisptr, ctx, state, pInfo, data.matrix);
							I::ModelRender()->ForcedMaterialOverride(nullptr);
						}
					}
					break;
				case 1:
					if (Entity->RenderOrigin.DistTo(record.back().origin) > 1.f)
					{
						GP_Esp->OverrideMaterial(!SBVisibleOnly, SBDouble, SBStyle, ShowBactrackColor);
						fnDME(thisptr, ctx, state, pInfo, record.back().matrix);
						I::ModelRender()->ForcedMaterialOverride(nullptr);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

Vector OldStandRCS = Vector(0, 0, 0);
bool NextSimpleDisable = false;
bool DisableNewWeapn = false;
bool NextAutoShot = false;
float Start = 0;

void CAimbot::CreateMove(bool &bSendPacket, float flInputSampleTime, CUserCmd* pCmd)
{
	iBestTarget = -1;
	iBestHitBox = -1;
	iSilentBestTarget = -1;
	iSilentBestHitBox = -1;
	CanSilent = false;

	AimEndBullet = Weapons[GetWeap(SelectedWeapon)].EndBullet;

	if (!CheckOpportWork(pCmd))
	{
		FFDelayOCActive = false;
		return;
	}

	if (SelectedWeapon < 0)
		return;

	CurTime = I::GlobalVars()->curtime;

	FFDelay.Update(CurTime);
	TSDelay.Update(CurTime);

	if (!pLocalPlayer)
		return;	

	bool IsRevolver = CGlobal::GWeaponID == WEAPON_REVOLVER && (pCmd->buttons & IN_ATTACK2);

	IsPistol = CGlobal::GWeaponType == WEAPON_TYPE_PISTOL && CGlobal::GWeaponID != WEAPON_REVOLVER;
	IsSniper = (CGlobal::GWeaponID == WEAPON_AWP || CGlobal::GWeaponID == WEAPON_SSG08);
	IsShotgun = CGlobal::GWeaponType == WEAPON_TYPE_SHOTGUN;

	if (IsSniper || IsShotgun || IsPistol)
		Weapons[GetWeap(SelectedWeapon)].EndBullet = 1;
	else
		Weapons[GetWeap(SelectedWeapon)].EndBullet = -1;

	SetMainParams();
	LpCmd = pCmd;

	StandeloneRCS(pCmd);



	Vector StartAng = pCmd->viewangles;

	AimPunchAngle = pLocalPlayer->GetPunchAngles();
	FovStartAng = pCmd->viewangles + ((AimPunchAngle * (Vector(RCS_X, RCS_Y, 0) / 100.f)) * 2.f);

	if (CanSilent)
	{
		if (!GetBestTarget(true))
			CanSilent = false;

		if (CanSilent)
			if (!GetBestHitBox(true))
				CanSilent = false;

		if (!CanSilent && pSilentAutoDelayEnable && FFDelayEnable)
			pSilentAutoDelay = true;
		else
			pSilentAutoDelay = false;
	}
	else
		pSilentAutoDelay = false;

	GetBestTarget(false);
	if (iBestTarget != -1)
		GetBestHitBox(false);

	static WEAPON_ID OldWeapon = (WEAPON_ID)0;

	if (OldWeapon != CGlobal::GWeaponID)
	{
		DisableNewWeapn = true;
		Start = I::GlobalVars()->curtime;
	}

	if (DisableNewWeapn)
	{
		float end = I::GlobalVars()->curtime;
		float diff = end - Start;
		if (diff > 0.05f)
			DisableNewWeapn = false;
	}

	OldWeapon = CGlobal::GWeaponID;

	bool FindedTarg = (iBestTarget != -1 && iBestHitBox != -1) || (iSilentBestTarget != -1 && iSilentBestHitBox != -1);

	if (AutoFire && FindedTarg)
		IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;

	if (DisableNewWeapn)
		IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;

	if (IsSniperClass && FastZoom && !IsZoomed)
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			pCmd->buttons &= ~IN_ATTACK;
			pCmd->buttons |= IN_ZOOM;

			NextAutoShot = true;
		}
		else
			NextAutoShot = false;
	}
	else
		NextAutoShot = false;
	
	bool PistolPreFire = (IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK));

	if ((IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)))
		if ((AutoPistol || AutoFire) && IsPistol)
			CalcAutoPistol(pCmd, pLocalPlayer);

	//bool EnableAimBacktrack = AimPlusBacktrack && Weapons[GetWeap(SelectedWeapon)].Backtrack && !FindedTarg && iBackTrackbestTarget != -1 && iBackTrackBestSimTime != -1;
	//if (EnableAimBacktrack)
	//{
	//	GetBestHitBox(false, true);
	//	iBestTarget = iBackTrackbestTarget;
	//	FindedTarg = (iBestTarget != -1 && iBestHitBox != -1) || (iSilentBestTarget != -1 && iSilentBestHitBox != -1);
	//}

	bool AnyDelay = (FFDelay.STimer.Active || FFAutoDelay || pSilentAutoDelay);

	static bool FixAttack = false;

	if (FixAttack)
	{
		IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;
		FixAttack = false;
	}

	if (FFDelayOCActive && !AnyDelay && FindedTarg && !FFDelayOCDisable)
	{
		IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;
		FixAttack = true;
		FFDelayOCDisable = true;
	}

	bool IsAttack = (IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)) || (NextAutoShot && IsSniperClass && FastZoom);

	FFDelayOCActive = FindedTarg && AnyDelay && (IsAttack || FFDelayOCActive) && FFDelayOneClickEnable && !FFDelayOCDisable;

	static bool SetRevolvTime = false;
	static float RevolvStartFire = 0;
	static float RevolvNextFire = 0;

	if ((pCmd->buttons & IN_ATTACK) && !SetRevolvTime)
	{
		RevolvNextFire = I::GlobalVars()->curtime + 0.20f;
		SetRevolvTime = true;
	}

	if (!(pCmd->buttons & IN_ATTACK))
		SetRevolvTime = false;

	if ((((IsAttack || (AutoPistol && IsPistol && PistolPreFire)) && FindedTarg) || FFDelayOCActive) && true)
	{
		if (FFAutoDelayEnable && FFDelayEnable && !FFDelayDisable)
		{
			if (!CanFire(FovStartAng, pCmd, pBestTarget, 1, pLocalPlayer, true))
				FFAutoDelay = true;
			else
			{
				FFAutoDelay = false;
				FFAutoDelayDisable = true;
			}
		}
		else
			FFAutoDelay = false;

		if (!KillStopEnable)
		{
			if (TSDelayEnable && TSDelayTime > 0 && pOldBestTarget)
				if (pOldBestTarget->GetHealth() == 0)
					TSDelay = CAimTimer(CurTime + TSDelayTime, true);
		}
		else
			if (pOldBestTarget && pOldBestTarget->GetHealth() == 0)
				KillStop = true;

		if (FFAutoDelay && !FFAutoDelayDisable)
			IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;

		if (FFDelayEnable && FFDelayTime > 0 && !FFDelayDisable)
			if (!FFDelay.STimer.Enable)
				FFDelay = CAimTimer(CurTime + FFDelayTime, true);

		if (FFDelay.STimer.Active)
			IsRevolver ? pCmd->buttons |= IN_ATTACK2 : pCmd->buttons |= IN_ATTACK;

		CalcFinalVecRcs(false);
		if (CanSilent)
			CalcFinalVecRcs(true);

		if (FFDelay.STimer.Active)
			IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;

		if (pSilentAutoDelay && !pSilentAutoDelayDisable && !CanFire(FovStartAng, pCmd, pBestTarget, 1, pLocalPlayer, true))
			IsRevolver ? pCmd->buttons &= ~IN_ATTACK2 : pCmd->buttons &= ~IN_ATTACK;
		else
			pSilentAutoDelayDisable = true;

		if ((IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)))
			FFDelayOCDisable = true;

		if (!TSDelay.STimer.Active && !KillStop)
		{
			Vector FinalVec_Temp = Smooth(StartAng, FinalVec, GSmooth, false);
			Vector SilentFinalVec_Temp = Smooth(StartAng, SilentFinalVec, 0, true);

			if (CanSilent)
				CanSilent = (Weapons[GetWeap(SelectedWeapon)].SilentHitchance == 100 ?
					true : ((1 + (rand() % 101)) <= Weapons[GetWeap(SelectedWeapon)].SilentHitchance));

			if (!CanSilent)
				if (iBestTarget != -1 && iBestHitBox != -1)
					CreateAssistMove(FinalVec_Temp);

			if (CGlobal::GWeaponID == WEAPON_REVOLVER)
			{
				bool FinalEnableSilent = CanSilent;

				if ((CGlobal::GWeaponID == WEAPON_REVOLVER) && (pCmd->buttons & IN_ATTACK))
				{
					debug_log("%f\n", RevolvNextFire - I::GlobalVars()->curtime);

					bool TimeDDD = RevolvNextFire - I::GlobalVars()->curtime > ((iShotsFired == 0) ? 0.16f : 0.18f);

					if (TimeDDD)
						FinalEnableSilent = false;
					else
						SetRevolvTime = false;
				}

				if (FinalEnableSilent)
				{
					pCmd->viewangles = SilentFinalVec_Temp;
					if (iBestTarget != -1 && iBestHitBox != -1)
						CreateAssistMove(FinalVec_Temp, true);

					bSendPacket = false;
				}
				else
				{
					if (CanSilent)
						if (iBestTarget != -1 && iBestHitBox != -1)
							CreateAssistMove(FinalVec_Temp);
				}
			}
			else
			{
				if (CanSilent)
				{
					pCmd->viewangles = SilentFinalVec_Temp;
					if (iBestTarget != -1 && iBestHitBox != -1)
						CreateAssistMove(FinalVec_Temp, true);

					bSendPacket = false;
				}
			}
		}
	}
	else
	{
		FFDelay.STimer.Enable = false;
		TSDelay.STimer.Enable = false;
		KillStop = false;
		pSilentAutoDelayDisable = false;
		FFAutoDelay = false;
		FFAutoDelayDisable = false;
		SetSmoothStart = false;
		FFDelayOCDisable = false;
	}

	if (!(IsRevolver ? (pCmd->buttons & IN_ATTACK2) : (pCmd->buttons & IN_ATTACK)))
		FFDelayDisable = false;
	else
		FFDelayDisable = true;


	if (pBestTarget)
		pOldBestTarget = pBestTarget;
}

void CAimbot::SetMainParams()
{
	/*========================================== Rcs switch =============================================================*/
	bool _CanRCS = true;

	if (Weapons[GetWeap(SelectedWeapon)].RcsEndBullet > 0)
		if (iShotsFired >= Weapons[GetWeap(SelectedWeapon)].RcsEndBullet)
			_CanRCS = false;

	if (_CanRCS)
		if (Weapons[GetWeap(SelectedWeapon)].RcsStartBullet > 0)
			if (Weapons[GetWeap(SelectedWeapon)].RcsStartBullet - 1 > iShotsFired)
				_CanRCS = false;

	/*========================================== Delay & Smooth =============================================================*/
	SmoothMethod = Weapons[GetWeap(SelectedWeapon)].SmoothMethod;
	StartAcceleration = Weapons[GetWeap(SelectedWeapon)].StartAcceleration;
	EndAcceleration = Weapons[GetWeap(SelectedWeapon)].EndAcceleration;

	KillStopEnable = Weapons[GetWeap(SelectedWeapon)].KillStop;

	FFDelayOneClickEnable = Weapons[GetWeap(SelectedWeapon)].FirstFireDelayOneClick;

	FFDelayEnable = Weapons[GetWeap(SelectedWeapon)].FirstFireDelayEnable;
	FFDelayTime = Weapons[GetWeap(SelectedWeapon)].FirstFireDelay;

	TSDelayEnable = Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelayEnable;
	TSDelayTime = Weapons[GetWeap(SelectedWeapon)].TargetSwitchDelay;

	pSilentAutoDelayEnable = Weapons[GetWeap(SelectedWeapon)].FirstFireDelaySilentAuto;
	FFAutoDelayEnable = Weapons[GetWeap(SelectedWeapon)].FirstFireDelayAuto && !EntityAim;

	AutoPistol = Weapons[GetWeap(SelectedWeapon)].AutoPistol;
	FastZoom = Weapons[GetWeap(SelectedWeapon)].FastZoom;
	OnlyZoom = Weapons[GetWeap(SelectedWeapon)].OnlyZoom;

	/*========================================== All =============================================================*/
	CanSilent = IsEnableSilent();
	CanRCS = IsEnableRCS();
	FovPos = Weapons[GetWeap(SelectedWeapon)].FovPos;
	SmoothMF = Weapons[GetWeap(SelectedWeapon)].SmoothMoveFactor;

	/*========================================== Silent ==========================================================*/
	IsSilentNearest = Weapons[GetWeap(SelectedWeapon)].SilentNearest;
	SilentHitBox = Weapons[GetWeap(SelectedWeapon)].SilentHitBox;
	GSilentFov = Weapons[GetWeap(SelectedWeapon)].SilentFov;

	/*========================================== Standard ========================================================*/
	IsNearest = Weapons[GetWeap(SelectedWeapon)].HitBoxAfter1B && _CanRCS ?
		Weapons[GetWeap(SelectedWeapon)].NearestRcs : Weapons[GetWeap(SelectedWeapon)].Nearest;

	HitBox = Weapons[GetWeap(SelectedWeapon)].HitBoxAfter1B && _CanRCS ?
		Weapons[GetWeap(SelectedWeapon)].HitBoxRcs : Weapons[GetWeap(SelectedWeapon)].HitBox;

	GFov = Weapons[GetWeap(SelectedWeapon)].FovRcs != 0 && _CanRCS ?
		Weapons[GetWeap(SelectedWeapon)].FovRcs : Weapons[GetWeap(SelectedWeapon)].Fov;

	GSmooth = Weapons[GetWeap(SelectedWeapon)].SmoothRcs != 0 && _CanRCS ?
		Weapons[GetWeap(SelectedWeapon)].SmoothRcs : Weapons[GetWeap(SelectedWeapon)].Smooth;

	/*==========================================================================================================*/
	CanRCSStandelone = Weapons[GetWeap(SelectedWeapon)].RcsStandelone;

	FaceItMode = FaceIt;
}

bool CAimbot::CheckOpportWork(CUserCmd* pCmd)
{
	AimWorking = false;
	static bool DisableIfPK = false;

	if (IsNonAimWeapon())
	{
		if ((pCmd->buttons & IN_ATTACK))
			DisableIfPK = true;

		Start = I::GlobalVars()->curtime;
		DisableNewWeapn = true;
		return false;
	}

	if (DisableIfPK && (pCmd->buttons & IN_ATTACK) && AimEndBullet == 1)
		return false;
	else
		DisableIfPK = false;

	if (!AimBind.Check())
		return false;

	pLocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

	if (!pLocalPlayer)
		return false;

	if (pLocalPlayer->IsDead())
		return false;

	pLocalWeapon = pLocalPlayer->GetBaseWeapon();
	if (!pLocalWeapon)
		return false;

	if (!(pLocalPlayer->GetFlags() & FL_ONGROUND) && JumpCheck)
		return false;

	if ((CGlobal::GWeaponType == WEAPON_TYPE_SNIPER) && OnlyZoom && !pLocalPlayer->GetIsScoped())
		return false;

	if (pLocalPlayer->IsFlashed() && FlashCheck)
		return false;

	pLocalWeapon = pLocalPlayer->GetBaseWeapon();

	if (!pLocalWeapon)
		return false;

	if (pLocalWeapon->GetWeaponAmmo() == 0)
		return false;

	if (pLocalWeapon->GetWeaponReload())
		return false;

	iShotsFired = pLocalPlayer->GetShotsFired();

	if (NextAutoShot && iShotsFired != 0)
	{
		NextAutoShot = false;
	}

	if (AimEndBullet != -1 && iShotsFired >= AimEndBullet && !AutoPistol)
		return false;

	if (CGlobal::GWeaponType == WEAPON_TYPE_SNIPER)
		IsSniperClass = true;
	else
		IsSniperClass = false;

	if (IsSniperClass)
		if (pLocalWeapon->GetZoomLevel() == 1 || pLocalWeapon->GetZoomLevel() == 2)
			IsZoomed = true;
		else
			IsZoomed = false;
	else
		IsZoomed = false;


	AimWorking = true;

	POINT pt;
	FastCall::G().t_GetCursorPos(&pt);
	MousePos = Vector(pt.x, pt.y, 0);

	ScreenCenterX = CGlobal::iScreenWidth / 2;
	ScreenCenterY = CGlobal::iScreenHeight / 2;

	return true;
}

float To360(float in)
{
	return (in > 0 ? in : 180 + (180 + in));
}

void CAimbot::CreateAssistMove(Vector TargetAng, bool IsSilent)
{
	if (!FaceItMode)
	{
		if (IsSilent)
			I::Engine()->SetViewAngles(TargetAng);
		else
		{
			if (LpCmd)
				LpCmd->viewangles = TargetAng;
			I::Engine()->SetViewAngles(TargetAng);
		}
	}
	else if (FaceItMode && !CGlobal::IsGuiVisible)
	{
		if (IsSilent)
			I::Engine()->SetViewAngles(TargetAng);
		else
		{
			Vector ScreenTargPoint;
			if (LpCmd)
			{

				float diff_x = TargetAng.y - LpCmd->viewangles.y;

				if (LpCmd->viewangles.y > 90 && TargetAng.y < -90)
					diff_x = To360(TargetAng.y) - To360(LpCmd->viewangles.y);

				ScreenTargPoint.x = (ScreenCenterX + ((((ScreenCenterX / CGlobal::GFovView) * diff_x)) * -1.f));
				ScreenTargPoint.y = (ScreenCenterY + (((ScreenCenterX / CGlobal::GFovView) * (TargetAng.x - LpCmd->viewangles.x))));

				AssistScreenPoint = ScreenTargPoint;
				NewMouseOfstPos = Vector(ScreenTargPoint.x - MousePos.x, ScreenTargPoint.y - MousePos.y, 0);

				if (fabs(NewMouseOfstPos.x) < 1.f)
				{
					if (fabs(NewMouseOfstPos.x) > 0.01f)
					{
						if (NewMouseOfstPos.x > 0.f)
							NewMouseOfstPos.x = 1.f;
						else
							NewMouseOfstPos.x = -1.f;
					}
					else
						NewMouseOfstPos.x = 0.f;
				}

				if (fabs(NewMouseOfstPos.y) < 1.f)
				{
					if (fabs(NewMouseOfstPos.y) > 0.01f)
					{
						if (NewMouseOfstPos.y > 0.f)
							NewMouseOfstPos.y = 1.f;
						else
							NewMouseOfstPos.y = -1.f;
					}
					else
						NewMouseOfstPos.y = 0.f;
				}
				FastCall::G().t_mouse_event(MOUSEEVENTF_MOVE, (DWORD)NewMouseOfstPos.x, (DWORD)NewMouseOfstPos.y, NULL, NULL);
			}
		}
	}
}

void CAimbot::CalcAutoPistol(CUserCmd* cmd, CBaseEntity * pLocal)
{
	float NextAttack = pLocal->GetBaseWeapon()->GetNextPrimaryAttack();
	float Tick = pLocal->GetTickBase() * I::GlobalVars()->interval_per_tick;

	if (NextAttack < Tick)
		return;

	if ((WEAPON_ID)*pLocal->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
		cmd->buttons &= ~IN_ATTACK2;
	else
		cmd->buttons &= ~IN_ATTACK;
}

static void Normalize(Vector& angle) 
{
	while (angle.x > 89.0f) {
		angle.x -= 180.f;
	}
	while (angle.x < -89.0f) {
		angle.x += 180.f;
	}
	while (angle.y > 180.f) {
		angle.y -= 360.f;
	}
	while (angle.y < -180.f) {
		angle.y += 360.f;
	}
}

Vector CAimbot::Smooth(Vector& viewangles, Vector target, float factor, bool silent)
{
	factor /= 100.f;
	Vector delta = target - viewangles;

	if (CCSmooth && factor > 0)
	{
		Vector OldViewAng = viewangles;
		Vector OldTargAng = target;

		TempVec3 = target;

		if (target.x >= 180)
			target.x = (180.f - (180.f - (360.f - target.x))) * -1.f;

		if (target.y >= 180)
			target.y = (180.f - (180.f - (360.f - target.y))) * -1.f;

		TempVec1 = viewangles;
		TempVec2 = target;

		SmoothCurLen = CCSmooth->GetCurLen(viewangles, target);

		if (!SetSmoothStart)
		{
			CCSmooth->StartLen = GFov / 3.f;
			SetSmoothStart = true;
		}

		SmoothCurAngle = CCSmooth->GetCurAngle(SmoothCurLen, viewangles, target);
		SmoothMaxDelta = CCSmooth->GetMaxDelta(CCSmooth->StartLen, SmoothCurAngle, viewangles, target);

		SmoothProgress = (SmoothCurLen / (CCSmooth->StartLen / 100.f));

		viewangles = OldViewAng;
		target = OldTargAng;
	}

	CGlobal::ClampAngles(delta);

	bool isCurve = SmoothMethod == 1 && !CanSilent;

	if (!isCurve)
	{
		Vector toChange = Vector(0, 0, 0);
		if (silent)
		{
			CGlobal::ClampAngles(target);
			return target;
		}

		if (SmoothMF == 0)
		{
			float smooth = powf(factor, 0.27f);

			smooth = min(0.9999999f, smooth);

			toChange = delta - delta * smooth;
		}
		else if (SmoothMF == 1)
		{
			if (factor <= 0)
			{
				CGlobal::ClampAngles(target);
				return target;
			}

			float smooth = powf(factor, 0.4f);
			smooth = min(0.9999999f, smooth);

			float coeff = fabsf(smooth - 1.f) / delta.Length() * 4.f;
			coeff = min(1.f, coeff);
			toChange = (delta * coeff);
		}

		Vector End = viewangles + toChange;

		CGlobal::ClampAngles(End);

		return End;
	}

	if (isCurve)
	{
		float AccelDelta = StartAcceleration - EndAcceleration;
		float DeltaAngle = atanf(AccelDelta / 100.f) * _180_PI;
		CurAcceleration = SmoothProgress * tan(DeltaAngle * PI / 180);

		if (CurAcceleration < 0)
			CurAcceleration = (AccelDelta * -1.f) - (CurAcceleration * -1.f);

		CurAcceleration = min(StartAcceleration, EndAcceleration) + CurAcceleration;

		factor = CurAcceleration / 100.f;

		Vector toChange = Vector(0, 0, 0);

		if (SmoothMF == 0)
		{
			float smooth = powf(factor, 0.4f);

			smooth = min(0.9999999f, smooth);

			toChange = delta - delta * smooth;

		}
		else if (SmoothMF == 1)
		{
			float smooth = powf(factor, 0.4f);
			smooth = min(0.9999999f, smooth);

			float coeff = fabsf(smooth - 1.f) / delta.Length() * 4.f;
			coeff = min(1.f, coeff);
			toChange = (delta * coeff);
		}

		float Factor_10 = 100.f;
		float Factor_50 = -100.f;
		float Factor_75 = 100.f;

		float CurFactor = 0;

		if (SmoothProgress <= 10.f)
			CurFactor = Factor_10;

		if (SmoothProgress > 10.f && SmoothProgress < 50.f)
			CurFactor = Factor_50;

		if (SmoothProgress >= 50.f)
			CurFactor = Factor_75;


		toChange.x += (CurFactor / 200.f) * toChange.y;
		toChange.y += (CurFactor / 200.f) * toChange.x;


		return viewangles + toChange;
	}
	return viewangles;
}

void CAimbot::VixViewAng(Vector &VE)
{
	if (VE.y <= -90 && VE.y >= -179)
		VE.y = (90 - ((90 + VE.y) * -1));

	if (VE.x <= -90 && VE.x >= -179)
		VE.x = (90 - ((90 + VE.x) * -1));
}

Vector CAimbot::PlayerAnglToScreen(Vector Angl)
{
	if (LpCmd)
	{
		Vector viewangles = LpCmd->viewangles;

		float FovFal = CGlobal::GFovView;
		return Vector(
			(ScreenCenterX + ((((ScreenCenterX / FovFal) * (Angl.y - viewangles.y))) * -1.f)),
			(ScreenCenterY + (((ScreenCenterX / FovFal) * (Angl.x - viewangles.x)))),
			0);
	}
	else
		return Vector(0, 0, 0);
}

bool CAimbot::IsNonAimWeapon()
{
	if (CGlobal::GWeaponType == WEAPON_TYPE_GRENADE ||
		CGlobal::GWeaponType == WEAPON_TYPE_KNIFE ||
		CGlobal::GWeaponType == WEAPON_TYPE_C4 ||
		CGlobal::GWeaponType == WEAPON_TYPE_UNKNOWN)
		return true;

	return false;
}

bool CAimbot::CanShoot()
{
	if (pLocalWeapon->GetWeaponAmmo() < 1)
		return false;

	float server_time = pLocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick;
	float next_shot = pLocalWeapon->GetNextPrimaryAttack() - server_time;

	if (next_shot > 0)
		return false;

	return true;
}

bool CAimbot::IsEnableSilent()
{
	if (FaceIt)
		return false;

	bool ret = false;
	if (Weapons[GetWeap(SelectedWeapon)].Silent && Weapons[GetWeap(SelectedWeapon)].SilentFov > 0)
	{
		ret = true;
		if (Weapons[GetWeap(SelectedWeapon)].SilentHitchance == 0)
			ret = false;
		else
		{
			if (Weapons[GetWeap(SelectedWeapon)].SilentStartBullet > 0)
				if (Weapons[GetWeap(SelectedWeapon)].SilentStartBullet - 1 > iShotsFired)
					ret = false;

			if (Weapons[GetWeap(SelectedWeapon)].SilentEndBullet > 0 && ret)
				if (iShotsFired >= Weapons[GetWeap(SelectedWeapon)].SilentEndBullet)
					ret = false;
		}
	}

	if (ret)
		ret = CanShoot();

	return ret;
}

bool CAimbot::IsEnableRCS()
{
	bool Ret = false;

	bool CheckPistol = CGlobal::GWeaponType == WEAPON_TYPE_PISTOL ? true : iShotsFired > 1;

	RCS_X = Weapons[GetWeap(SelectedWeapon)].RcsX;
	RCS_Y = Weapons[GetWeap(SelectedWeapon)].RcsY;

	if ((RCS_X > 0 || RCS_Y > 0) && CheckPistol)
	{
		Ret = true;
		if (Weapons[GetWeap(SelectedWeapon)].RcsStartBullet > 0)
			if (Weapons[GetWeap(SelectedWeapon)].RcsStartBullet - 1 > iShotsFired)
				Ret = false;

		if (Weapons[GetWeap(SelectedWeapon)].RcsEndBullet > 0 && Ret)
			if (iShotsFired >= Weapons[GetWeap(SelectedWeapon)].RcsEndBullet)
				Ret = false;
	}
	else
		Ret = false;

	if (Ret)
		Ret = CanShoot();

	return Ret;
}

bool CAimbot::GetBestTarget(bool _CheckSilent)
{
	float BestFov = _CheckSilent ? GSilentFov : GFov / 3.f;
	int _iBestTarget = -1;

	if (BestFov > 0.1f)
	{
		if (FovPos == 2)
			BestFov = FLT_MAX;

		MyEyeAng = pLocalPlayer->GetEyePosition();

		if (!EntityAim)
		{
			for (int i = 0; i < I::Engine()->GetMaxClients(); i++)
			{
				CBaseEntity* CheckEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(i);

				if (!CheckEntity)
					continue;

				if (!CheckEntity->IsValid())
					continue;

				if (CheckEntity == pLocalPlayer)
					continue;

				if (!Deathmatch && CheckEntity->GetTeam() == pLocalPlayer->GetTeam())
					continue;

				if (!(CheckEntity->GetFlags() & FL_ONGROUND) && JumpEnemyCheck)
					continue;

				if (_CheckSilent ? IsSilentNearest : IsNearest)
				{
					for (int j = 0; j < 19/*17*/; j++)
					{
						Vector vecHitBox = CheckEntity->GetHitboxPosition(j);

						if (!CheckEntity->IsVisibleHitBox(pLocalPlayer, MyEyeAng, vecHitBox, SmokeCheck, FlashCheck) && WallCheck)
							continue;

						float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

						if (_Fov < BestFov)
						{
							BestFov = _Fov;
							_iBestTarget = i; 
							pBestTarget = CheckEntity;
							break;
						}
					}
				}
				else
				{
					int _HitBox = _CheckSilent ? SilentHitBox : HitBox;
						
					if (_HitBox == 2)
						_HitBox = 6;

					Vector vecHitBox = CheckEntity->GetHitboxPosition(_HitBox);

					if (!CheckEntity->IsVisibleHitBox(pLocalPlayer, MyEyeAng, vecHitBox, SmokeCheck, FlashCheck) && WallCheck)
						continue;

					float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);
					if (_Fov < BestFov)
					{
						BestFov = _Fov;
						_iBestTarget = i;
						pBestTarget = CheckEntity;
					}
				}
			}
		}
		else
		{
			for (int EntIndex = 0; EntIndex < I::EntityList()->GetHighestEntityIndex(); EntIndex++)
			{
				CBaseEntity* pEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(EntIndex);

				if (!pEntity || pEntity->IsPlayer())
					continue;

				const model_t* pModel = pEntity->GetModel();

				if (pModel)
				{
					const char* pModelName = I::ModelInfo()->GetModelName(pModel);

					if (pModelName)
					{

						string md = pModelName;

						if (md == EntityTargetName)
						{
							Vector vSrc = pLocalPlayer->GetEyePosition();
							Vector vEnd = pEntity->GetEyePosition();

							float fov = CalcFOV(FovStartAng, MyEyeAng, vEnd);
							if (fov < BestFov)
							{
								BestFov = fov;
								_iBestTarget = EntIndex;
								pBestTarget = pEntity;
							}
						}
					}
				}

			}
		}
	}

	if (_CheckSilent)
	{
		iSilentBestTarget = _iBestTarget;
		if (iSilentBestTarget == -1)
			return false;
		else
			return true;
	}
	else
	{
		iBestTarget = _iBestTarget;
		if (iBestTarget == -1)
			return false;
		else
			return true;
	}
	return true;
}

bool CAimbot::GetBestHitBox(bool _CheckSilent, bool CheckBackTrack)
{
	if (!CheckBackTrack)
		if (!pBestTarget)
			return false;

	float BestFov = _CheckSilent ? GSilentFov : GFov / 3.f;
	int HiddenHitBoxs = 0;
	int _BestHitBox = -1;
	Vector _BestHitBoxPos = Vector(0, 0, 0);

	if (BestFov > 0.1f)
	{
		if (FovPos == 2)
			BestFov = FLT_MAX;

		MyEyeAng = pLocalPlayer->GetEyePosition();
		Vector vecHitBox = Vector(0, 0, 0);

		if (!EntityAim)
		{
			if (_CheckSilent ? IsSilentNearest : IsNearest)
			{
				for (int i = 0; i < 7; i++)
				{
					if (!CheckBackTrack)
					{
						vecHitBox = pBestTarget->GetHitboxPosition(i);

						if (!pBestTarget->IsVisibleHitBox(pLocalPlayer, MyEyeAng, vecHitBox, SmokeCheck, FlashCheck) && WallCheck)
						{
							HiddenHitBoxs++;
							continue;
						}
					}
					float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

					if (_Fov < BestFov)
					{
						BestFov = _Fov;
						_BestHitBox = i;
						_BestHitBoxPos = vecHitBox;
					}
				}
				if (HiddenHitBoxs > 6)
				{
					for (int i = 7; i < 19/*17*/; i++)
					{
						if (!CheckBackTrack)
						{
							vecHitBox = pBestTarget->GetHitboxPosition(i);

							if (!pBestTarget->IsVisibleHitBox(pLocalPlayer, MyEyeAng, vecHitBox, SmokeCheck, FlashCheck) && WallCheck)
								continue;
						}

						float _Fov = CalcFOV(FovStartAng, MyEyeAng, vecHitBox);

						if (_Fov < BestFov)
						{
							BestFov = _Fov;
							_BestHitBox = i;
							_BestHitBoxPos = vecHitBox;
						}
					}
				}
			}
			else
			{
				int _HitBox = _CheckSilent ? SilentHitBox : HitBox;;

				if (_HitBox == 2)
					_HitBox = 6;

				_BestHitBox = _HitBox;

				if (!CheckBackTrack)
					_BestHitBoxPos = pBestTarget->GetHitboxPosition(_HitBox);
			}
		}
		else
		{
			for (int EntIndex = 0; EntIndex < I::EntityList()->GetHighestEntityIndex(); EntIndex++)
			{
				CBaseEntity* pEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(EntIndex);

				if (!pEntity || pEntity->IsPlayer())
					continue;

				const model_t* pModel = pEntity->GetModel();

				if (pModel)
				{
					const char* pModelName = I::ModelInfo()->GetModelName(pModel);

					if (pModelName)
					{
						string md = pModelName;

						if (md == EntityTargetName)
						{
							Vector vSrc = pLocalPlayer->GetEyePosition();
							Vector vEnd = pEntity->GetEyePosition();

							float fov = CalcFOV(FovStartAng, MyEyeAng, vEnd);
							if (fov < BestFov)
							{
								BestFov = fov;
								_BestHitBox = 1;
								_BestHitBoxPos = vEnd;
							}
						}
					}
				}

			}
		}

		if (_CheckSilent)
			iLastBestHitBox = _BestHitBox;
		else
			iLastSilentBestHitBox = _BestHitBox;

		if (FovPos == 2)
		{
			float dy = CGlobal::iScreenHeight / CGlobal::GFovView;
			float dx = CGlobal::iScreenWidth / CGlobal::GFovView;

			float iFovVal = 0;
			if (_CheckSilent)
				iFovVal = dx * GSilentFov;
			else
				iFovVal = dx * (GFov / 3.f);

			float base_fov = pow(iFovVal + 30, 2) * CGlobal::GFovView;
			BestFov = (base_fov / (pLocalPlayer->GetHitboxPosition(0).DistTo(_BestHitBoxPos) * CGlobal::GFovView));
			float fov = CalcFOV(FovStartAng, MyEyeAng, _BestHitBoxPos);
			fov += fov / 8.f;

			TestSF = fov;

			if (fov > (BestFov / 10.f))
				_BestHitBox = -1;
		}
	}
	if (_CheckSilent)
	{
		iSilentBestHitBox = _BestHitBox;
		SilentBestHitBoxPos = _BestHitBoxPos;

		SilentPreVec = CalculateAngle(MyEyeAng, SilentBestHitBoxPos);

		if (iSilentBestHitBox == -1)
			return false;
		else
			return true;
	}
	else
	{
		iBestHitBox = _BestHitBox;
		BestHitBoxPos = _BestHitBoxPos;

		PreVec = CalculateAngle(MyEyeAng, BestHitBoxPos);

		if (iBestHitBox == -1)
			return false;
		else
			return true;
	}
}

void CAimbot::CalcFinalVecRcs(bool _CheckSilent)
{
	if (_CheckSilent)
		SilentFinalVec = SilentPreVec - ((AimPunchAngle * (Vector(100.f, 100.f, 0) / 100.f)) * 2.f);
	else
		FinalVec = PreVec - (AimPunchAngle * Vector(RCS_X / 50.f, RCS_Y / 50.f, 0));
}

float CAimbot::CalcFOV(Vector& viewangles, const Vector& vSrc, const Vector& vEnd)
{
	Vector vAng, vAim;

	vAng = CalculateAngle(vSrc, vEnd);
	MakeVector(viewangles, vAim);
	MakeVector(vAng, vAng);

	return Rad2Deg(acos(vAim.Dot(vAng)) / vAim.LengthSqr());
}

void CAimbot::MakeVector(const Vector& vIn, Vector& vOut)
{
	float pitch = Deg2Rad(vIn.x);
	float yaw = Deg2Rad(vIn.y);
	float temp = cos(pitch);

	vOut.x = -temp * -cos(yaw);
	vOut.y = sin(yaw) * temp;
	vOut.z = -sin(pitch);
}

void CAimbot::StandeloneRCS(CUserCmd* pCmd)
{
	if ((pCmd->buttons & IN_ATTACK) && CanRCSStandelone)
	{
		Vector AimPunch = (AimPunchAngle * (Vector(Weapons[GetWeap(SelectedWeapon)].RcsX, Weapons[GetWeap(SelectedWeapon)].RcsY, 0) / 100.f)) * 2.f;
		Vector StartPunch = pCmd->viewangles;
		Vector EndPunch = OldStandRCS - AimPunch;
		Vector BufPunch = StartPunch + EndPunch;

		//Vector delta = BufPunch - pCmd->viewangles;
		//float smooth = powf(0.55f, 0.4f);
		//float coeff = fabsf(smooth - 1.f) / delta.Length() * 4.f;
		//coeff = min(1.f, coeff);
		//BufPunch = pCmd->viewangles + (delta * coeff);

		Vector delta = BufPunch - pCmd->viewangles;
		BufPunch = pCmd->viewangles + (delta * (min(1.f, (fabsf(powf(0.6f, 0.4f) - 1.f) / delta.Length() * 4.f))));

		CGlobal::ClampAngles(BufPunch);

		if (FaceItMode)
		{
			Vector ScreenTargPoint;
			if (LpCmd)
			{
				ScreenTargPoint.x = (ScreenCenterX + ((((ScreenCenterX / CGlobal::GFovView) * (BufPunch.y - LpCmd->viewangles.y))) * -1.f));
				ScreenTargPoint.y = (ScreenCenterY + (((ScreenCenterX / CGlobal::GFovView) * (BufPunch.x - LpCmd->viewangles.x))));

				AssistScreenPoint = ScreenTargPoint;
				NewMouseOfstPos = Vector(ScreenTargPoint.x - MousePos.x, ScreenTargPoint.y - MousePos.y, 0);

				NewMouseOfstPos *= MouseSense;

				if (fabs(NewMouseOfstPos.x) < 1.f)
				{
					if (fabs(NewMouseOfstPos.x) > 0.01f)
					{
						if (NewMouseOfstPos.x > 0.f)
							NewMouseOfstPos.x = 1.f;
						else
							NewMouseOfstPos.x = -1.f;
					}
					else
						NewMouseOfstPos.x = 0.f;
				}

				if (fabs(NewMouseOfstPos.y) < 1.f)
				{
					if (fabs(NewMouseOfstPos.y) > 0.01f)
					{
						if (NewMouseOfstPos.y > 0.f)
							NewMouseOfstPos.y = 1.f;
						else
							NewMouseOfstPos.y = -1.f;
					}
					else
						NewMouseOfstPos.y = 0.f;
				}

				if (fabs(NewMouseOfstPos.x) > 110.f)
					NewMouseOfstPos.x = 0;

				if (fabs(NewMouseOfstPos.y) > 110.f)
					NewMouseOfstPos.y = 0;

				FastCall::G().t_mouse_event(MOUSEEVENTF_MOVE, (DWORD)NewMouseOfstPos.x, (DWORD)NewMouseOfstPos.y, NULL, NULL);
			}
		}
		else
			pCmd->viewangles = BufPunch;

		OldStandRCS = AimPunch;
	}
	else
		OldStandRCS = (AimPunchAngle * (Vector(RCS_X, RCS_Y, 0) / 100.f)) * 2.f;
}

Vector CAimbot::CalculateAngle(const Vector& in, Vector out)
{
	Vector ret = Vector();
	Vector delta = in - out;
	double hyp = delta.Length2D();
	ret.y = (atan(delta.y / delta.x) * 57.295779513082f);
	ret.x = (atan(delta.z / hyp) * 57.295779513082f);
	ret[2] = 0.00;

	if (delta.x >= 0.0)
		ret.y += 180.0f;
	return ret;
}

float CAimbot::Rad2Deg(float x)
{
	return (x * (180.0f / M_PI));
}

float CAimbot::Deg2Rad(float x)
{
	return (x * (M_PI / 180.0f));
}

bool LastShoot = false;
float FireDelay = 0;

void CAimbot::TriggerCreateMove(CUserCmd* pCmd)
{
	if (!TriggerBind.Check())
		return;

	if (IsNonAimWeapon())
		return;

	pLocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

	if (!pLocalPlayer)
		return;

	if (pLocalPlayer->IsDead())
		return;

	pLocalWeapon = pLocalPlayer->GetBaseWeapon();

	if (!pLocalWeapon)
		return;

	if (pLocalWeapon->GetWeaponAmmo() == 0)
		return;

	if (pLocalWeapon->GetWeaponReload())
		return;

	if (pLocalPlayer->IsFlashed() && TriggerFlashCheck)
		return;

	if (!(pLocalPlayer->GetFlags() & FL_ONGROUND) && TriggerJumpCheck)
		return;

	if ((CGlobal::GWeaponType == WEAPON_TYPE_SNIPER) && TriggerOnlyZoom && !pLocalPlayer->GetIsScoped())
		return;

	Vector MyAngle = pCmd->viewangles + pLocalPlayer->GetPunchAngles();

	TriggerGetBestTarget(MyAngle);

	bool EnableRcs = false;
	bool CanFireChanse = false;

	bool CanFireDelay = I::GlobalVars()->curtime <= FireDelay;
	bool delay = false;

	if (CanFire(MyAngle, pCmd, pTriggerBestTarget, TriggerBestIdx, pLocalPlayer, Weapons[GetWeap(SelectedWeapon)].TriggerAllHitboxes))
	{
		CanFireChanse = (1 + (rand() % 101)) <= Weapons[GetWeap(SelectedWeapon)].TriggerChanse;
		if (CanFireChanse)
		{
			if (Weapons[GetWeap(SelectedWeapon)].TriggerDelay > 0 && !CanFireDelay)
			{
				if (!LastShoot)
					FireDelay = I::GlobalVars()->curtime + Weapons[GetWeap(SelectedWeapon)].TriggerDelay;

				LastShoot = true;
				CanFireDelay = I::GlobalVars()->curtime <= FireDelay;
			}

			if (CanFireDelay && LastShoot)
				delay = true;

			if (!delay)
			{
				EnableRcs = true;
				if (!(pCmd->buttons & IN_ATTACK))
				{
					pCmd->buttons |= IN_ATTACK;
				}
			}
		}
	}
	else
	{
		LastShoot = false;
	}	

	TriggerRCS(Weapons[GetWeap(SelectedWeapon)].TriggerRcsX, Weapons[GetWeap(SelectedWeapon)].TriggerRcsY, pCmd, EnableRcs);
}

bool __declspec(noinline) CAimbot::CanFire(Vector mAngle, CUserCmd* pCmd, CBaseEntity* BaseEnt, int BestInd, CBaseEntity* local, bool AllHitGroup)
{
	if (BestInd != -1 && BaseEnt)
	{
		trace_t Trace;
		Ray_t Ray;
		CTraceFilter Filter;

		Vector vecS = pLocalPlayer->GetRenderOrigin() + pLocalPlayer->GetViewOffset();
		Vector vecForvard;
		Vector vAngle = Vector(pCmd->viewangles.x + (pLocalPlayer->GetAimPunchAngle().x * 2),
			pCmd->viewangles.y + (pLocalPlayer->GetAimPunchAngle().y * 2), 0);

		AngleVectors(vAngle, vecForvard);
		vecForvard *= 8000.0f;

		Ray.Init(vecS, vecS + vecForvard);

		Filter.pSkip = pLocalPlayer;
		I::EngineTrace()->TraceRay(Ray, PlayerVisibleMask, &Filter, &Trace);

		auto CheckEnableHBox = [&](int HBox) -> bool
		{
			switch (HBox)
			{
			case 1: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_HEAD;
			case 2: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_CHEST;
			case 3: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_STOMACH;
			case 4: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTARM;
			case 5: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTARM;
			case 6: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_LEFTLEG;
			case 7: return Weapons[GetWeap(SelectedWeapon)].TRIG_HITGROUP_RIGHTLEG;
			default: return false;
			}
		};

		if (string(Trace.surface.name).find(__xor("glass")) != string::npos ||
			string(Trace.surface.name).find(__xor("GLASS")) != string::npos ||
			string(Trace.surface.name).find(__xor("Glass")) != string::npos)
		{

			trace_t New_Trace;
			Ray_t New_Ray;
			CTraceFilter New_Filter;

			New_Ray.Init(Trace.endpos, vecS + vecForvard);

			New_Filter.pSkip = Trace.hit_entity;
			I::EngineTrace()->TraceRay(New_Ray, PlayerVisibleMask, &New_Filter, &New_Trace);

			if (New_Trace.hit_entity == BaseEnt && (AllHitGroup ? true && New_Trace.hitgroup != 0 : CheckEnableHBox((New_Trace.hitgroup))))
				return true;
		}
		else
			if (Trace.hit_entity == BaseEnt && (AllHitGroup ? true && Trace.hitgroup != 0 : CheckEnableHBox((Trace.hitgroup))))
				return true;

		return false;
	}
	return false;

}

void  CAimbot::TriggerGetBestTarget(Vector mAngle)
{
	float bestFov = FLT_MAX;

	for (int i = 0; i < I::Engine()->GetMaxClients(); i++)
	{
		CBaseEntity* pBaseEntity = (CBaseEntity*)I::EntityList()->GetClientEntity(i);

		if (!pBaseEntity)
			continue;

		if (!pBaseEntity->IsValid())
			continue;

		if (pBaseEntity == pLocalPlayer)
			continue;

		if (!TriggerDeathmatch && pBaseEntity->GetTeam() == pLocalPlayer->GetTeam())
			continue;

		if (!(pBaseEntity->GetFlags() & FL_ONGROUND) && TriggerJumpEnemyCheck)
			continue;

		Vector vSrc = pLocalPlayer->GetEyePosition();

		Vector vEnd = pBaseEntity->GetHitboxPosition(0);

		if (!pBaseEntity->IsVisibleHitBox(pLocalPlayer, vSrc, vEnd, TriggerSmokeCheck, FlashCheck))
			continue;

		float fov = CalcFOV(mAngle, vSrc, vEnd);
		if (fov < bestFov)
		{
			bestFov = fov;
			TriggerBestIdx = i;
			pTriggerBestTarget = pBaseEntity;
		}
	}
}
Vector _OldAimPunch = Vector(0, 0, 0);
void CAimbot::TriggerRCS(int X, int Y, CUserCmd* pCmd, bool Enable)
{
	if (pLocalPlayer)
	{
		if (Enable)
		{
			Vector AimPunch = (pLocalPlayer->GetPunchAngles()*(Vector(X, Y, 0) / 100.f)) * 2.f;

			Vector StartPunch = pCmd->viewangles;

			Vector EndPunch = _OldAimPunch - AimPunch;

			Vector BufPunch = StartPunch + EndPunch;

			CGlobal::ClampAngles(BufPunch);

			pCmd->viewangles = BufPunch;
			_OldAimPunch = AimPunch;
		}
		else
			_OldAimPunch = (pLocalPlayer->GetPunchAngles()*(Vector(X, Y, 0) / 100.f)) * 2.f;
	}
}

void CAimbot::InitConVar()
{
	records.clear();
	cvars.UpdateRate = I::GetCvar()->FindVar(__xor("cl_updaterate"));
	cvars.maxUpdateRate = I::GetCvar()->FindVar(__xor("sv_maxupdaterate"));
	cvars.interp = I::GetCvar()->FindVar(__xor("cl_interp"));
	cvars.interpRatio = I::GetCvar()->FindVar(__xor("cl_interp_ratio"));
	cvars.minInterpRatio = I::GetCvar()->FindVar(__xor("sv_client_min_interp_ratio"));
	cvars.maxInterpRatio = I::GetCvar()->FindVar(__xor("sv_client_max_interp_ratio"));
	cvars.maxUnlag = I::GetCvar()->FindVar(__xor("sv_maxunlag"));
}

void CAimbot::BacktrackCreateMoveEP(CUserCmd* pCmd)
{
	auto AngleVector = [&](QAngle meme)
	{
		auto sy = sin(meme.y / 180.f * static_cast<float>(3.141592654f));
		auto cy = cos(meme.y / 180.f * static_cast<float>(3.141592654f));

		auto sp = sin(meme.x / 180.f * static_cast<float>(3.141592654f));
		auto cp = cos(meme.x / 180.f * static_cast<float>(3.141592654f));

		return Vector(cp * cy, cp * sy, -sp);
	};

	auto DistancePointToLine = [&](Vector Point, Vector LineOrigin, Vector Dir)
	{
		auto PointDir = Point - LineOrigin;

		auto TempOffset = PointDir.Dot(Dir) / (Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z);
		if (TempOffset < 0.000001f)
			return FLT_MAX;

		auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

		return (Point - PerpendicularPoint).Length();
	};

	iBackTrackbestTarget = -1;

	pLocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

	if (!pLocalPlayer || pLocalPlayer->IsDead())
	    return;

	if (SelectedWeapon < 0)
		return;

	if (Weapons[GetWeap(SelectedWeapon)].Backtrack && !FaceIt && Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit)
	{
		//if (BacktrackFakeLatency && (Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit < 200))
		//	Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit += 200;
		//else if (!(BacktrackFakeLatency) && Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit > 200)
		//	Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit -= 200;

		PlayerInfo info;
		float bestFov = FLT_MAX;
		for (int i = 0; i <= I::Engine()->GetMaxClients(); i++)
		{
			CBaseEntity* entity = (CBaseEntity*)I::EntityList()->GetClientEntity(i);

			if (!entity || !pLocalPlayer)
			{ records[i].clear(); continue; }

			if (entity == pLocalPlayer)
			{ records[i].clear(); continue; }

			if (!I::Engine()->GetPlayerInfo(i, &info))
			{ records[i].clear(); continue; }

			if (entity->IsDormant())
			{ records[i].clear(); continue; }

			if (pLocalPlayer->GetTeam() == entity->GetTeam())
			{ records[i].clear(); continue; }

			if (!records[i].empty() && (records[i].front().simtime == entity->GetSimTime()))
				continue;

			BacktrackData record;
			record.origin = entity->GetAbsOrigin();
			record.simtime = entity->GetSimTime();
			record.hitboxPos = entity->GetHitboxPosition(0 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 16 & 17 & 18 & 19 & 10 & 11);

			entity->InvalidateBoneCache();
			entity->SetupBones(record.matrix, 256, 0x7FF00, I::GlobalVars()->curtime);

			Vector ViewDir = AngleVector(pCmd->viewangles + (pLocalPlayer->GetAimPunchAngle() * 2.f));
			float FOVDistance = DistancePointToLine(record.hitboxPos, pLocalPlayer->GetEyePosition(), ViewDir);

			if (FOVDistance < bestFov)
			{
				bestFov = FOVDistance;
				iBackTrackbestTarget = i;
				pBestBacktrackTarget = entity;
			}

			records[i].push_front(record);

			while (records[i].size() > 3 && records[i].size() > static_cast<size_t>(TIME_TO_TICKS(static_cast<float>(Weapons[GetWeap(SelectedWeapon)].BacktrackTimeLimit) / 1000.f)))
				records[i].pop_back();

			auto invalid = std::find_if(std::cbegin(records[i]), std::cend(records[i]), [](const BacktrackData& rec) { return !valid(rec.simtime); });
			if (invalid != std::cend(records[i]))
				records[i].erase(invalid, std::cend(records[i]));
		}

		float bestTargetSimTime = 0;
		if (iBackTrackbestTarget != -1)
		{
			float tempFloat = FLT_MAX;
			for (auto& node : records)
			{
				auto& cur_data = node.second;
				if (cur_data.empty())
					continue;

				for (auto& bd : cur_data)
				{
					if (cur_data.size() <= 3 || (!Weapons[GetWeap(SelectedWeapon)].BacktrackIgnoreSmoke && CGlobal::LineGoesThroughSmoke(pLocalPlayer->GetEyePosition(), bd.origin)))
						return;

					if (!valid(bd.simtime))
						continue;

					Vector ViewDir = AngleVector(pCmd->viewangles + (pLocalPlayer->GetAimPunchAngle() * 2.f));
					float tempFOVDistance = DistancePointToLine(bd.hitboxPos, pLocalPlayer->GetEyePosition(), ViewDir);

					if (tempFOVDistance < tempFloat)
					{
						tempFloat = tempFOVDistance;
						bestTargetSimTime = TIME_TO_TICKS(bd.simtime + getLerp());
						iBackTrackBestSimTime = bestTargetSimTime;
					}
				}
			}
		}

		if (pCmd->buttons & IN_ATTACK && iBackTrackbestTarget != -1)
		{
			auto& record = records.at(iBackTrackbestTarget);
			if (record.size() > 0)
				for (auto& data : record)
					pBestBacktrackTarget->SetAbsOrigin(data.origin);

			pCmd->tick_count = bestTargetSimTime;
		}
	}
}

void CAimbot::SaveWeapons(nlohmann::json &j)
{
#define SV(a,b) j[__xor("LegitAim")][__xor("AimWeapons")][v.WeaponName][__xor(a)] = b;


	for (int i(0); i < (int)CustomSubs.size(); i++)
	{
		j[__xor("LegitAim")][__xor("Subsections")][__xor("SubsNames")].push_back(CustomSubs[i].Name);
		for (int g(0); g < (int)CustomSubs[i].AllocatedWeapon.size(); g++)
			j[__xor("LegitAim")][__xor("Subsections")][CustomSubs[i].Name].push_back(CustomSubs[i].AllocatedWeapon[g]);
	}

	WeaponSettings emptyEntry;

	for (auto &v : Weapons)
	{
		if (emptyEntry == v)
		{
			SV("Emp", true);
			continue;
		}

		SV("IsCustomSub", v.IsCustomSub);
		SV("Silent", v.Silent);
		SV("SilentFov", v.SilentFov);
		SV("SilentHitBox", v.SilentHitBox);
		SV("SilentNearest", v.SilentNearest);
		SV("SilentHitchance", v.SilentHitchance);
		SV("SilentStartBullet", v.SilentStartBullet);
		SV("SilentEndBullet", v.SilentEndBullet);
		SV("FovPos", v.FovPos);
		SV("Smooth", v.Smooth);
		SV("Fov", v.Fov);
		SV("HitBox", v.HitBox);
		SV("Nearest", v.Nearest);
		SV("FirstFireDelayEnable", v.FirstFireDelayEnable);
		SV("FirstFireDelayAuto", v.FirstFireDelayAuto);
		SV("FirstFireDelaySilentAuto", v.FirstFireDelaySilentAuto);
		SV("FirstFireDelayOneClick", v.FirstFireDelayOneClick);
		SV("FirstFireDelay", v.FirstFireDelay);
		SV("TargetSwitchDelayEnable", v.TargetSwitchDelayEnable);
		SV("TargetSwitchDelay", v.TargetSwitchDelay);
		SV("KillStop", v.KillStop);
		SV("EndBullet", v.EndBullet);
		SV("RcsX", v.RcsX);
		SV("RcsY", v.RcsY);
		SV("SmoothRcs", v.SmoothRcs);
		SV("FovRcs", v.FovRcs);
		SV("HitBoxAfter1B", v.HitBoxAfter1B);
		SV("HitBoxRcs", v.HitBoxRcs);
		SV("NearestRcs", v.NearestRcs);
		SV("RcsStandelone", v.RcsStandelone);
		SV("RcsStartBullet", v.RcsStartBullet);
		SV("RcsEndBullet", v.RcsEndBullet);
		SV("AutoPistol", v.AutoPistol);
		SV("FastZoom", v.FastZoom);
		SV("OnlyZoom", v.OnlyZoom);
		SV("TRIG_HITGROUP_HEAD", v.TRIG_HITGROUP_HEAD);
		SV("TRIG_HITGROUP_CHEST", v.TRIG_HITGROUP_CHEST);
		SV("TRIG_HITGROUP_STOMACH", v.TRIG_HITGROUP_STOMACH);
		SV("TRIG_HITGROUP_LEFTARM", v.TRIG_HITGROUP_LEFTARM);
		SV("TRIG_HITGROUP_RIGHTARM", v.TRIG_HITGROUP_RIGHTARM);
    	SV("TRIG_HITGROUP_LEFTLEG", v.TRIG_HITGROUP_LEFTLEG);
		SV("TRIG_HITGROUP_RIGHTLEG", v.TRIG_HITGROUP_RIGHTLEG);
		SV("TriggerAllHitboxes", v.TriggerAllHitboxes);
		SV("TriggerChanse", v.TriggerChanse);
		SV("TriggerRcsX", v.TriggerRcsX);
		SV("TriggerRcsY", v.TriggerRcsY);
		SV("TriggerDelay", v.TriggerDelay);
		SV("Backtrack", v.Backtrack);
		SV("BacktrackIgnoreSmoke", v.BacktrackIgnoreSmoke);
		SV("BacktrackTimeLimit", v.BacktrackTimeLimit);
		SV("SmoothMoveFactor", v.SmoothMoveFactor);
	}
}

void CAimbot::LoadWeapons(nlohmann::json &j)
{
#define LV(a,b) if(!j[__xor("LegitAim")][__xor("AimWeapons")][v.WeaponName][__xor(a)].is_null()){ b = j[__xor("LegitAim")][__xor("AimWeapons")][v.WeaponName][__xor(a)];}

	if (!CustomSubs.empty())
		CustomSubs.clear();

	Weapons.clear();

	ReinitWeapons();

	if (!j[__xor("LegitAim")].is_null())
	{
		if (!j[__xor("LegitAim")][__xor("AimWeapons")].is_null())
		{
			if (!j[__xor("LegitAim")][__xor("Subsections")].is_null())
			{
				if (!j[__xor("LegitAim")][__xor("Subsections")][__xor("SubsNames")].is_null())
				{
					for (size_t i(0); i < j[__xor("LegitAim")][__xor("Subsections")][__xor("SubsNames")].size(); i++)
					{
						CustomSub SubEntry;
						if (!j[__xor("LegitAim")][__xor("Subsections")][__xor("SubsNames")].at(i).is_null())
						{
							SubEntry.Name = j[__xor("LegitAim")][__xor("Subsections")][__xor("SubsNames")].at(i).get<string>();
							SubEntry.Idx = Weapons.size();

							for (size_t g(0); g < j[__xor("LegitAim")][__xor("Subsections")][SubEntry.Name].size(); g++)
								if (!j[__xor("LegitAim")][__xor("Subsections")][SubEntry.Name].at(g).is_null())
									SubEntry.AllocatedWeapon.push_back(j[__xor("LegitAim")][__xor("Subsections")][SubEntry.Name].at(g).get<string>());

							WeaponSettings WeaponEntry;
							WeaponEntry.WeaponName = SubEntry.Name;

							CustomSubs.push_back(SubEntry);
							Weapons.push_back(WeaponEntry);
						}
					}

					if (!UnallocatedWeapons.empty())
						UnallocatedWeapons.clear();

					for (int i(0); i < 34; i++)
					{
						// Weapon names
						bool Finded = false;
						for (size_t j(0); j < CustomSubs.size(); j++)
						{
							for (size_t l(0); l < CustomSubs[j].AllocatedWeapon.size(); l++)
							{
								if (CustomSubs[j].AllocatedWeapon[l] == CGlobal::WeaponNames[i])
								{
									Finded = true;
									break;
								}
							}
						}
						if (!Finded)
							UnallocatedWeapons.push_back(CGlobal::WeaponNames[i]);
					}
				}
			}
			WeaponSettings emptyEntry;
			for (auto &v : Weapons)
			{

				bool IsEmpty = false;
				LV("Emp", IsEmpty);

				if (IsEmpty)
				{
					string nn = v.WeaponName;
					v = emptyEntry;
					v.WeaponName = nn;
					continue;
				}

				LV("IsCustomSub", v.IsCustomSub);
				LV("Silent", v.Silent);
				LV("SilentFov", v.SilentFov);
				LV("SilentHitBox", v.SilentHitBox);
				LV("SilentNearest", v.SilentNearest);
				LV("SilentHitchance", v.SilentHitchance);
				LV("SilentStartBullet", v.SilentStartBullet);
				LV("SilentEndBullet", v.SilentEndBullet);
				LV("FovPos", v.FovPos);
				LV("Smooth", v.Smooth);
				LV("Fov", v.Fov);
				LV("HitBox", v.HitBox);
				LV("Nearest", v.Nearest);
				LV("FirstFireDelayEnable", v.FirstFireDelayEnable);
				LV("FirstFireDelayAuto", v.FirstFireDelayAuto);
				LV("FirstFireDelaySilentAuto", v.FirstFireDelaySilentAuto);
				LV("FirstFireDelayOneClick", v.FirstFireDelayOneClick);
				LV("FirstFireDelay", v.FirstFireDelay);
				LV("TargetSwitchDelayEnable", v.TargetSwitchDelayEnable);
				LV("TargetSwitchDelay", v.TargetSwitchDelay);
				LV("KillStop", v.KillStop);
				LV("EndBullet", v.EndBullet);
				LV("RcsX", v.RcsX);
				LV("RcsY", v.RcsY);
				LV("SmoothRcs", v.SmoothRcs);
				LV("FovRcs", v.FovRcs);
				LV("HitBoxAfter1B", v.HitBoxAfter1B);
				LV("HitBoxRcs", v.HitBoxRcs);
				LV("NearestRcs", v.NearestRcs);
				LV("RcsStandelone", v.RcsStandelone);
				LV("RcsStartBullet", v.RcsStartBullet);
				LV("RcsEndBullet", v.RcsEndBullet);
				LV("AutoPistol", v.AutoPistol);
				LV("OnlyZoom", v.OnlyZoom);
				LV("TRIG_HITGROUP_HEAD", v.TRIG_HITGROUP_HEAD);
				LV("TRIG_HITGROUP_CHEST", v.TRIG_HITGROUP_CHEST);
				LV("TRIG_HITGROUP_STOMACH", v.TRIG_HITGROUP_STOMACH);
				LV("TRIG_HITGROUP_LEFTARM", v.TRIG_HITGROUP_LEFTARM);
				LV("TRIG_HITGROUP_RIGHTARM", v.TRIG_HITGROUP_RIGHTARM);
				LV("TRIG_HITGROUP_LEFTLEG", v.TRIG_HITGROUP_LEFTLEG);
				LV("TRIG_HITGROUP_RIGHTLEG", v.TRIG_HITGROUP_RIGHTLEG);
				LV("TriggerAllHitboxes", v.TriggerAllHitboxes);
				LV("TriggerChanse", v.TriggerChanse);
				LV("TriggerRcsX", v.TriggerRcsX);
				LV("TriggerRcsY", v.TriggerRcsY);
				LV("TriggerDelay", v.TriggerDelay);
				LV("Backtrack", v.Backtrack);
				LV("BacktrackIgnoreSmoke", v.BacktrackIgnoreSmoke);
				LV("BacktrackTimeLimit", v.BacktrackTimeLimit);
				LV("SmoothMoveFactor", v.SmoothMoveFactor);
			}
		}
	}
}



























































