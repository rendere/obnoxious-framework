#pragma once
#include <math.h>
#include <chrono>
#include <map>
#include <deque>
#include <algorithm> 

#include "../../Main.h"
#include "../../Engine/Engine.h"
#include "../Settings.h"
#include "../../Hooks/MinHook/hook.h"

#define _180_PI 57.324840764331210191082802547771
#define PI 3.14159265 

namespace Engin
{
	class CBaseEntity;
	class CPlayer;
	class CBaseWeapon;
}
using namespace Engine;

extern int SelectedWeapon;

class IAimTimer
{
protected:
	virtual void Update(float _CurTime) = 0;
};

class CAimTimer : public IAimTimer
{
public:
	struct _STimer
	{
		bool Enable = false;
		bool Active = false;
		float EndTime = 0;
	}STimer;

	CAimTimer() {}
	CAimTimer(float Delay, bool _Active = false, bool _Enable = true)
	{
		STimer.Enable = _Enable;
		STimer.Active = _Active;
		STimer.EndTime = Delay;
	}
	virtual void Update(float _CurTime)
	{
		if (STimer.EndTime < _CurTime)
			STimer.Active = false;
	}
};

class ICustomSmooth
{
protected:
	virtual float GetCurLen(Vector viewangles, Vector target) = 0;
	virtual float GetCurAngle(float Len, Vector viewangles, Vector target) = 0;
	virtual Vector GetMaxDelta(float Len, float Angl, Vector viewangles, Vector target) = 0;
};

class CCustomSmooth : public ICustomSmooth
{
public:

	float StartLen = 0;

	virtual float GetCurLen(Vector viewangles, Vector target)
	{
		float SmeshX = target.y < 0 && viewangles.y > 0 ? (viewangles.y - target.y * -1.f) : (target.y - viewangles.y);
		float SmeshY = target.x < 0 && viewangles.x > 0 ? (viewangles.x - target.x * -1.f) : (target.x - viewangles.x);

		return sqrtf(powf(SmeshX, 2.f) + powf(SmeshY, 2.f));
	}

	virtual float GetCurAngle(float Len, Vector viewangles, Vector target)
	{

		float SmeshX = (target.y - viewangles.y) * -1.f;
		float SmeshY = (target.x - viewangles.x) * -1.f;
		return atanf(SmeshY / SmeshX) * _180_PI;
	}

	virtual Vector GetMaxDelta(float Len, float Angl, Vector viewangles, Vector target)
	{
		return Vector(
			target.x + ((Len * sin(Angl * PI / 180.f)) * (viewangles.y < target.y ? -1.f : 1.f)),
			target.y + ((Len * cos(Angl * PI / 180.f)) * (viewangles.y < target.y ? -1.f : 1.f)),
			0);
	}

};

class IAimbot
{
protected:

	virtual void SaveWeapons(nlohmann::json &j) = 0;
	virtual void LoadWeapons(nlohmann::json &j) = 0;
	virtual void InitConVar() = 0;
	virtual void TriggerCreateMove(CUserCmd* pCmd) = 0;
	virtual void TriggerGetBestTarget(Vector mAngle) = 0;
	virtual bool CheckOpportWork(CUserCmd* pCmd) = 0;
	virtual bool GetBestTarget() = 0;
	virtual bool GetBestHitBox() = 0;
	virtual void SetMainParams() = 0;
	virtual void CalcAutoPistol(CUserCmd* cmd, CBaseEntity * pLocal) = 0;
	virtual void StandeloneRCS(CUserCmd* pCmd) = 0;
	virtual void CalcFinalVecRcs() = 0;
	virtual void MakeVector(const Vector& vIn, Vector& vOut) = 0;
	virtual void CreateAssistMove(Vector TargetAng) = 0;
	virtual void VixViewAng(Vector &VE) = 0;

	virtual void Menu() = 0;
	virtual void SubsectionsMenu() = 0;
	virtual void Draw() = 0;
	virtual void CreateMove(int sequence, float frametime, bool active, bool& bSendPacket) = 0;
	virtual void SetSelectedWeapon(bool MenuCheck = true) = 0;
	virtual void TriggerRCS(int X, int Y, CUserCmd* pCmd, bool Enable) = 0;
	virtual bool __declspec(noinline) CanFire(Vector mAngle, CUserCmd* pCmd, CBaseEntity* BaseEnt, int BestInd, CBaseEntity* Local, bool AllHitGroup) = 0;
	virtual float CalcFOV(Vector& viewangles, const Vector& vSrc, const Vector& vEnd) = 0;
	virtual Vector Smooth(Vector& viewangles, Vector target, float factor) = 0;
	virtual Vector PlayerAnglToScreen(Vector Angl) = 0;
	virtual Vector CalculateAngle(const Vector& in, Vector out) = 0;
	virtual float Rad2Deg(float x) = 0;
	virtual float Deg2Rad(float x) = 0;
	virtual bool IsNonAimWeapon() = 0;
	virtual bool CanShoot() = 0;
	virtual bool IsEnableRCS() = 0;
};

class CAimbot : public IAimbot
{
public:

	CConfig Config = CConfig(__xor("LegitAim"));

	virtual void Menu();
	virtual void SubsectionsMenu();
	virtual void Draw();
	virtual void CreateMove(int sequence, float frametime, bool active, bool& bSendPacket);
	virtual void SetSelectedWeapon(bool MenuCheck = true);
	virtual void SaveWeapons(nlohmann::json &j);
	virtual void LoadWeapons(nlohmann::json &j);

	virtual void InitConVar();
	virtual void TriggerCreateMove(CUserCmd* pCmd);
	virtual void TriggerGetBestTarget(Vector mAngle);
	virtual void TriggerRCS(int X, int Y, CUserCmd* pCmd, bool Enable);
	virtual bool __declspec(noinline) CanFire(Vector mAngle, CUserCmd* pCmd, CBaseEntity* BaseEnt, int BestInd, CBaseEntity* Local, bool AllHitGroup);

	/*NO SAVE*/
	int TriggerBestIdx = -1;
	int WeaponCustomTypes = 0;
	bool ShowWeaponList = false;
	int SubTabAimSelected = 0;
	bool GDrawRcsFov = false;
	int iShotsFired = 0;
	bool CanRCSStandelone = false;
	bool CanRCS = false;
	int StandardSubSelected = 0;
	int SelectedSub = 0;
	int SelectedSubAlloc = 0;
	int SelectedSubUnAlloc = 0;
	bool CheckAimCust = false;
	bool AutoDisableAll = false;
	/*=======*/

	bool Deathmatch = false;
	bool FlashCheck = false;
	bool SmokeCheck = false;
	bool WallCheck = false;
	bool AutoFire = false;
	bool JumpCheck = false;
	bool JumpEnemyCheck = false;

	bool DrawFov = false;
	bool DrawSilentFov = false;
	Color FovColor = Color(255, 255, 0, 255);
	Color SilentFovColor = Color(0, 255, 255, 255);

	bool ShowSpot = false;

	bool FaceIt = false;
	bool EntityAim = false;
	//bool Debug = false;
	bool ShowEntitysName = false;
	string EntityTargetName = __xor("<default>");

	CBind AimBind = CBind(0);
	CBind TriggerBind = CBind(0);

	float MouseSense = 1.9f;

	bool TriggerEnable = false;
	bool TriggerDeathmatch = false;
	bool TriggerFlashCheck = false;
	bool TriggerSmokeCheck = false;
	bool TriggerJumpCheck = false;
	bool TriggerMoveCheck = false;
	bool TriggerJumpEnemyCheck = false;
	bool TriggerOnlyZoom = false;

	struct LegitAimConVar
	{
		ConVar* UpdateRate;
		ConVar* maxUpdateRate;
		ConVar* interp;
		ConVar* interpRatio;
		ConVar* minInterpRatio;
		ConVar* maxInterpRatio;
		ConVar* maxUnlag;
	};
	LegitAimConVar cvars;


	struct CustomSub
	{
		int Idx;
		string Name;
		vector<string> AllocatedWeapon;
	};

	struct WeaponSettings
	{
		string WeaponName = __xor("<Default>");

		bool IsCustomSub = false;

		int SmoothMethod = 0;
		int SmoothMoveFactor = 0;
		float StartAcceleration = 85;
		float EndAcceleration = 65;

		bool Active = true;

		int FovPos = 1;

		float Smooth = 90;
		float Fov = 30;
		int HitBox = 0;
		bool Nearest = false;

		bool FirstFireDelayEnable = false;
		bool FirstFireDelayAuto = false;
		bool FirstFireDelaySilentAuto = false;
		bool FirstFireDelayOneClick = false;
		float FirstFireDelay = 0;

		bool TargetSwitchDelayEnable = false;
		float TargetSwitchDelay = 0;

		bool KillStop = false;

		int EndBullet = -1;
		/*RCS*/
		float RcsX = 100;
		float RcsY = 100;
		float SmoothRcs = 0;
		float FovRcs = 0;
		bool HitBoxAfter1B = false;
		int HitBoxRcs = 0;
		bool NearestRcs = false;
		bool RcsStandelone = false;

		int RcsStartBullet = 0;
		int RcsEndBullet = 1;
		/*=======*/

		bool AutoPistol = false;
		bool FastZoom = false;
		bool OnlyZoom = false;

		bool TRIG_HITGROUP_HEAD = false;
		bool TRIG_HITGROUP_CHEST = false;
		bool TRIG_HITGROUP_STOMACH = false;
		bool TRIG_HITGROUP_LEFTARM = false;
		bool TRIG_HITGROUP_RIGHTARM = false;
		bool TRIG_HITGROUP_LEFTLEG = false;
		bool TRIG_HITGROUP_RIGHTLEG = false;

		bool TriggerAllHitboxes = false;

		int TriggerChanse = 100;

		int TriggerRcsX = 0;
		int TriggerRcsY = 0;
		float TriggerDelay = 0;

#define CHECK_VAR(l) if(l != src.##l) return false;
		bool operator==(const WeaponSettings& src) const
		{
			CHECK_VAR(IsCustomSub);
			CHECK_VAR(SmoothMethod);
			CHECK_VAR(StartAcceleration);
			CHECK_VAR(EndAcceleration);
			CHECK_VAR(Active);
			CHECK_VAR(FovPos);
			CHECK_VAR(Smooth);
			CHECK_VAR(Fov);
			CHECK_VAR(HitBox);
			CHECK_VAR(Nearest);
			CHECK_VAR(FirstFireDelayEnable);
			CHECK_VAR(FirstFireDelayAuto);
			CHECK_VAR(FirstFireDelaySilentAuto);
			CHECK_VAR(FirstFireDelayOneClick);
			CHECK_VAR(FirstFireDelay);
			CHECK_VAR(TargetSwitchDelayEnable);
			CHECK_VAR(TargetSwitchDelay);
			CHECK_VAR(KillStop);
			//CHECK_VAR(EndBullet, EndBullet);
			CHECK_VAR(RcsX);
			CHECK_VAR(RcsY);
			CHECK_VAR(SmoothRcs);
			CHECK_VAR(FovRcs);
			CHECK_VAR(HitBoxAfter1B);
			CHECK_VAR(HitBoxRcs);
			CHECK_VAR(NearestRcs);
			CHECK_VAR(RcsStandelone);
			CHECK_VAR(RcsStartBullet);
			CHECK_VAR(RcsEndBullet);
			CHECK_VAR(AutoPistol);
			CHECK_VAR(FastZoom);
			CHECK_VAR(OnlyZoom);
			CHECK_VAR(TRIG_HITGROUP_HEAD);
			CHECK_VAR(TRIG_HITGROUP_CHEST);
			CHECK_VAR(TRIG_HITGROUP_STOMACH);
			CHECK_VAR(TRIG_HITGROUP_LEFTARM);
			CHECK_VAR(TRIG_HITGROUP_RIGHTARM);
			CHECK_VAR(TRIG_HITGROUP_LEFTLEG);
			CHECK_VAR(TRIG_HITGROUP_RIGHTLEG);
			CHECK_VAR(TriggerAllHitboxes);
			CHECK_VAR(TriggerChanse);
			CHECK_VAR(TriggerRcsX);
			CHECK_VAR(TriggerDelay);
			CHECK_VAR(SmoothMoveFactor);

			return true;
		}
	};

	vector<WeaponSettings> Weapons;
	vector<CustomSub> CustomSubs;
	vector<string> UnallocatedWeapons;

	bool Enable = false;

	void ReinitWeapons()
	{
		WeaponSettings Buf;
		for (int i(0); i < sizeof(CGlobal::WeaponNames) / sizeof(*CGlobal::WeaponNames); i++)
		{
			Buf.WeaponName = CGlobal::WeaponNames[i];
			UnallocatedWeapons.push_back(Buf.WeaponName);
			Weapons.push_back(Buf);
		}
		Buf.WeaponName = __xor("Rifles");
		Weapons.push_back(Buf);
		Buf.WeaponName = __xor("Snipers");
		Weapons.push_back(Buf);
		Buf.WeaponName = __xor("Shotguns");
		Weapons.push_back(Buf);
		Buf.WeaponName = __xor("Pistols");
		Weapons.push_back(Buf);
		Buf.WeaponName = __xor("AllWeapon");
		Weapons.push_back(Buf);
	}

	CAimbot()
	{
		CCSmooth = new CCustomSmooth();

		ReinitWeapons();

		LpCmd = nullptr;
		CCSmooth = nullptr;
		pBestTarget = nullptr;
		pOldBestTarget = nullptr;
		pLocalPlayer = nullptr;
		pLocalWeapon = nullptr;


		RV(WeaponCustomTypes, "WeaponCustomTypes");
		RV(Enable, "Enable");
		RV(Deathmatch, "Deathmatch");
		RV(FlashCheck, "FlashCheck");
		RV(SmokeCheck, "SmokeCheck");
		RV(WallCheck, "WallCheck");
		RV(AutoFire, "AutoFire");
		RV(JumpCheck, "JumpCheck");
		RV(JumpEnemyCheck, "JumpEnemyCheck");
		RV(DrawFov, "DrawFov");
		RV(DrawSilentFov, "DrawSilentFov");
		RV(FovColor, "FovColor");
		RV(SilentFovColor, "SilentFovColor");
		RV(ShowSpot, "ShowSpot");
		RV(FaceIt, "FaceIt");
		RV(EntityAim, "EntityAim");
		RV(ShowEntitysName, "ShowEntitysName");
		RV(EntityTargetName, "EntityTargetName");
		RV(AimBind, "AimBind");
		RV(TriggerBind, "TriggerBind");
//		RV(Debug, "Debug");
		RV(MouseSense, "MouseSense");
		RV(TriggerEnable, "TriggerEnable");
		RV(TriggerDeathmatch, "TriggerDeathmatch");
		RV(TriggerFlashCheck, "TriggerFlashCheck");
		RV(TriggerSmokeCheck, "TriggerSmokeCheck");
		RV(TriggerJumpCheck, "TriggerJumpCheck");
		RV(TriggerJumpEnemyCheck, "TriggerJumpEnemyCheck");
		RV(TriggerOnlyZoom, "TriggerOnlyZoom");

		debug_log("Setup: CAimbot sucessful\n");
	}

	CBaseEntity *pTriggerBestTarget;
	CBaseEntity *pBestTarget;
	CBaseEntity *pOldBestTarget;
	CBaseEntity *pLocalPlayer;
	CBaseWeapon *pLocalWeapon;


	virtual float CalcFOV(Vector& viewangles, const Vector& vSrc, const Vector& vEnd);

private:

	CUserCmd* LpCmd;
	CCustomSmooth *CCSmooth = nullptr;

	Vector MyEyeAng = Vector(0, 0, 0);
	Vector BestHitBoxPos = Vector(0, 0, 0);
	Vector FinalVec = Vector(0, 0, 0);
	Vector PreVec = Vector(0, 0, 0);
	Vector SilentFinalVec = Vector(0, 0, 0);
	Vector SilentPreVec = Vector(0, 0, 0);
	Vector FovStartAng = Vector(0, 0, 0);
	Vector AimPunchAngle = Vector(0, 0, 0);
	virtual Vector Smooth(Vector& viewangles, Vector target, float factor);
	Vector AssistScreenPoint = Vector(0, 0, 0);
	Vector NewMouseOfstPos = Vector(0, 0, 0);
	Vector MousePos = Vector(0, 0, 0);
	Vector SmoothMaxDelta = Vector(0, 0, 0);
	Vector PlayerAnglToScreen(Vector Angl);
	virtual Vector CalculateAngle(const Vector& in, Vector out);

	Vector TempVec1 = Vector(0, 0, 0);
	Vector TempVec2 = Vector(0, 0, 0);
	Vector TempVec3 = Vector(0, 0, 0);

	CAimTimer FFDelay;
	CAimTimer TSDelay;

	int iBestTarget = 0;
	int iBestHitBox = 0;
	int FovPos = 0;
	int iBestBone = 0;
	int CurWeaponID = 0;
	int AimStartBullet = 0;
	int AimEndBullet = -1;
	int SilentHitBox = 0;
	int HitBox = 0;
	int RCS_X = 0;
	int RCS_Y = 0;
	int iLastBestHitBox = 0;
	int AimMethod = 0;
	int SmoothMethod = 0;
	int SmoothMF = 0;

	float GSilentFov = 0;
	float GSmooth = 0;
	float GFov = 0;
	float CurTime = 0;
	float TSDelayTime = 0;
	float FFDelayTime = 0;
	float StartAcceleration = 0;
	float EndAcceleration = 0;
	float ScreenCenterX = 0;
	float ScreenCenterY = 0;
	float SmoothCurLen = 0;
	float SmoothCurAngle = 0;
	float SmoothProgress = 0;
	float CurAcceleration = 10.f;
	virtual float Rad2Deg(float x);

	virtual float Deg2Rad(float x);

	bool AutoPistol = false;
	bool IsPistol = false;
	bool IsSniper = false;
	bool IsShotgun = false;
	bool FFAutoDelay = false;
	bool FFAutoDelayEnable = false;
	bool FFAutoDelayDisable = false;
	bool KillStop = false;
	bool KillStopEnable = false;
	bool FFDelayOneClickEnable = false;
	bool FFDelayOCActive = false;
	bool FFDelayOCDisable = false;
	bool FFDelayEnable = false;
	bool FFDelayDisable = false;
	bool TSDelayEnable = false;
	bool CanSilent = false;

	bool IsSilentNearest = false;
	bool IsNearest = false;

	bool AimWorking = false;
	virtual bool IsNonAimWeapon();
	virtual bool CanShoot();
	virtual bool IsEnableRCS();
	virtual bool CheckOpportWork(CUserCmd* pCmd);
	virtual bool GetBestTarget();
	virtual bool GetBestHitBox();

	bool SetSmoothStart = false;
	bool FaceItMode = false;
	bool FastZoom = false;
	bool OnlyZoom = false;
	bool IsZoomed = false;
	bool IsSniperClass = false;

	virtual void SetMainParams();
	virtual void CalcAutoPistol(CUserCmd* cmd, CBaseEntity * pLocal);
	virtual void StandeloneRCS(CUserCmd* pCmd);
	virtual void CalcFinalVecRcs();
	virtual void MakeVector(const Vector& vIn, Vector& vOut);
	virtual void CreateAssistMove(Vector TargetAng);
	virtual void VixViewAng(Vector &VE);
};
