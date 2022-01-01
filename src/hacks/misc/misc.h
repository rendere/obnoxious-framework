#pragma once
#include "../../Engine/Engine.h"
#include "../../Render/DXOverlayManager.h"
#include "../Settings.h"
#include "../../Hooks/MinHook/hook.h"

namespace Engine
{
	class CBaseEntity;
	class CPlayer;
}

using namespace Engine;

class IMisc
{
protected:
	virtual void AutoAcceptEmit() = 0;
	virtual void Menu() = 0;
	virtual void Draw() = 0;
	virtual void CreateMove(bool &bSendPacket, float flInputSampleTime, CUserCmd* pCmd) = 0;
	virtual void CreateMoveEP(bool &bSendPacket, CUserCmd* pCmd) = 0;
	virtual void FrameStageNotify(ClientFrameStage_t Stage) = 0;
	virtual void OverrideView(CViewSetup* pSetup) = 0;
};

class CMisc : public IMisc
{
public:
	CConfig Config = CConfig(__xor("Misc"));

	struct HitImpact_t
	{
		Vector Pos;
		Vector MyHeadPos;
		float EndTime;
		float Alpha;
	};

	virtual void Menu();
	virtual void Draw();
	virtual void CreateMove(bool &bSendPacket, float flInputSampleTime, CUserCmd* pCmd);
	virtual void CreateMoveEP(bool &bSendPacket, CUserCmd* pCmd);
	virtual void FrameStageNotify(ClientFrameStage_t Stage);
	virtual void OverrideView(CViewSetup* pSetup);
	virtual void AutoAcceptEmit();

	/*NO SAVE*/
	CCSGOPlayerAnimState AnimState;
	float next_lby = 0.f;
	float side = 1.f;
	Vector real_angle;
	Vector fake_angle;
	Vector view_angle;
	/*=======*/

	bool Enable = true;
	bool BHop = false;
	bool JumpBugging = false;
	bool JumpBug = false;
	bool EdgeBugging = false;
	bool EdgeBug = false;
	bool SlowWalking = false;
	bool SlowWalk = false;
	CBind JumpBugBind = CBind(0, true);
	CBind SlowWalkBind = CBind(0, true);
	CBind EdgeBugBind = CBind(0, true);
	int BHopType = 0;
	int BHopChance = 0;
	int BHopLimit = 0;
	int BHopMaxHit = 0;
	bool AutoStrafe = false;
	int AutoStrafeSpeed = 0;
	bool EdgeJump = false;
	CBind EdgeJumpBind = CBind(0, true);

	bool LRHandKnife = false;
	bool InfiniteCrouch = false;

	bool Crosshair = false;
	int CrosshairStyle = 1;
	int CrosshairSize = 5;
	bool CrosshairRecoil = true;
	bool CrosshairOutline = true;
	bool SnipCrosshair = false;
	int SnipCrosshairStyle = 1;
	int SnipCrosshairSize = 5;
	bool SnipCrosshairRecoil = false;
	bool SnipCrosshairOutline = true;

	bool SpreadCircel = false;

	bool AutoAccept = false;
	bool ShowCompetitiveRank = false;
	bool KnifeBot = false;
	int KnifeBotDistance = 81;
	int KnifeBotFilter = 0;
	int KnifeBotMode = 0;
	CBind KnifeBotBind = CBind(0);

	Color CrosshairColor = Color(255, 0, 0, 255);
	Color SnipCrosshairColor = Color(255, 0, 0, 255);
	Color SpreadColor = Color(255, 255, 50, 255);
	Color HitMarkerColor = Color(255, 0, 0, 255);
	Color DamageInfoColor = Color(255, 100, 100, 255);

	vector<string> SoundList;

	CMisc()
	{
		RV(CrosshairColor, "CrosshairColor");
		RV(SnipCrosshairColor, "SnipCrosshairColor");
		RV(SpreadColor, "SpreadColor");
		RV(HitMarkerColor, "HitMarkerColor");
		RV(DamageInfoColor, "DamageInfoColor");

		RV(BHop, "BHop");
		RV(BHopType, "BHopType");
		RV(BHopChance, "BHopHitChance");
		RV(BHopLimit, "BHopLimit");
		RV(BHopMaxHit, "BHopMaxHit")
		RV(AutoStrafe, "AutoStrafe");
		RV(AutoStrafeSpeed, "AutoStrafeSpeed");
		RV(EdgeJump, "EdgeJump");
		RV(EdgeJumpBind, "EdgeJumpBind");
		RV(SlowWalkBind, "SlowWalk");
		RV(SlowWalkBind, "SlowWalkBind");
		RV(JumpBug, "JumpBug");
		RV(JumpBugBind, "JumpBugBind");
		RV(EdgeBug, "EdgeBug");
		RV(EdgeBugBind, "EdgeBugBind");
		RV(LRHandKnife, "LRHandKnife");
		RV(InfiniteCrouch, "InfiniteCrouch");
		RV(Crosshair, "Crosshair");
		RV(CrosshairStyle, "CrosshairStyle");
		RV(CrosshairSize, "CrosshairSize");
		RV(CrosshairRecoil, "CrosshairRecoil");
		RV(CrosshairOutline, "CrosshairOutline");
		RV(SnipCrosshair, "SnipCrosshair");
		RV(SnipCrosshairStyle, "SnipCrosshairStyle");
		RV(SnipCrosshairSize, "SnipCrosshairSize");
		RV(SnipCrosshairRecoil, "SnipCrosshairRecoil");
		RV(SnipCrosshairOutline, "SnipCrosshairOutline");
		RV(SpreadCircel, "SpreadCircel");
		RV(AutoAccept, "AutoAccept");
		RV(ShowCompetitiveRank, "ShowCompetitiveRank");
		RV(KnifeBot, "KnifeBot");
		RV(KnifeBotDistance, "KnifeBotDistance");
		RV(KnifeBotFilter, "KnifeBotFilter");
		RV(KnifeBotBind, "KnifeBotBind");
		RV(KnifeBotMode, "KnifeBotMode");
		

		debug_log("setup: CMisc successful\n");
	}
};